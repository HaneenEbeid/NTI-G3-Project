/* Standard Libraries (MCL) */
#include "../MCL/STD_TYPES.h"
#include "../MCL/BIT_MATH.h"
#include <util/delay.h>

/* MCAL Drivers */
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/PWM/PWM_interface.h"
#include "../MCAL/EX0/EXT0_interface.h"
#include "../MCAL/EX1/EXT1_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include "../MCAL/Timer0/Timer0_interface.h"
#include "../MCAL/MCU_PIN_Headers.h"

/* HAL Drivers */
#include "../HAL/KEYPAD/KPD_interface.h"
#include "../HAL/LCD/LCD_interface.h"
/**
 * @file    main.c
 * @brief   Core Application Logic for Smart Home Automation (ATmega32A)
 * @details Implements procedural logic (if/else), Output Arbitration, and Environmental Rules.
 *          Uses Timer0 to generate a non-blocking system tick.
 */

/* --- System Tick (Updated by Timer0 ISR) --- */
volatile u32 g_SystemTick = 0;

/* --- Output Arbitration Model Definitions --- */
typedef enum {
	OUT_FAN = 0,
	OUT_KITCHEN_LAMP,
	OUT_LIVING_LAMP,
	OUT_DOOR_LOCK,
	OUT_SIREN,
	OUT_HALLWAY,
	OUT_AWAY,
	OUT_BEDROOM,
	NUM_OUTPUTS
} OutputID_t;

typedef enum {
	SRC_DEFAULT = 0, /* Lowest Priority: Base state */
	SRC_RULE,        /* Automation based on sensors */
	SRC_SCENE,       /* Home/Away mode settings */
	SRC_MANUAL,      /* Direct user command (Keypad) */
	SRC_SAFETY,      /* Highest Priority: Alarms */
	NUM_SOURCES
} SourcePriority_t;

/* Arbitration Tables: Stores the requested value (u16 for PWM) and expiration tick */
u16 g_ArbValues[NUM_OUTPUTS][NUM_SOURCES] = {{0}};
u32 g_ArbTimeouts[NUM_OUTPUTS][NUM_SOURCES] = {{0}};

/* --- System Constants & Macros --- */
#define PIN_LENGTH              4
#define MAX_PIN_ATTEMPTS        3
/* Assuming Timer0 tick happens every 1ms for calculation purposes */
#define TICK_MS                 1
#define SEC_TO_TICKS(sec)       ((sec * 1000UL) / TICK_MS)
#define MIN_TO_TICKS(min)       ((min * 60000UL) / TICK_MS)

#define GAS_THRESHOLD           600
#define TEMP_LOW                28
#define TEMP_HIGH               35
#define FAN_MAX_SPEED           10000
#define FAN_SPEED_STEP          2000
#define LDR_DARK_TH             25
#define LDR_BRIGHT_TH           40
#define HUMIDITY_HIGH_TH        70

/* --- Global Variables --- */
const u8 g_CorrectPIN[PIN_LENGTH] = {'1', '2', '3', '4'};
u8  g_EnteredPIN[PIN_LENGTH];
u8  g_PINIndex = 0;
u8  g_FailedAttempts = 0;

/* Lockout and Alarm Timers/Flags */
u32 g_LockoutEndTick = 0;
u32 g_GasHighStartTick = 0;
u8  g_GasTimerActive = 0;
u8  g_GasAlarmActive = 0;
u8 g_DoorUnlocked=0;
/* Motion Flags updated by EXTI ISRs */
volatile u8 g_MotionDetectedLiving = 0;
volatile u8 g_MotionDetectedHallway = 0;

/* --- Function Prototypes --- */
void Arb_voidRequestOutput(OutputID_t Output, SourcePriority_t Source, u16 Value, u32 DurationTicks);
void Arb_voidApplyOutputs(void);
void ENV_voidEvaluateRules(u16 Gas, u8 Temp, u8 LDR, u8 Hum);
void EXTI0_func(void);
void EXTI1_func(void);
void TIMER0_Tick_ISR(void);
void App_voidInitPins(void);

int main(void) {
	/* ------------------------------------------------------------------ */
	/* 1. INITIALIZATION SETUP                                            */
	/* ------------------------------------------------------------------ */
	u16 LDR = 0; u16 Gas = 0; u16 Hum = 0; u16 Temp = 0;

	KPD_voidInit();
	LCD_voidInit();
	PWM_voidInit();
	ADC_voidInit();
	EXTI0_voidInit();
	EXTI1_voidInit();

	/* Timer0 Initialization for System Tick */
	TIMER0_voidInit();
	TIMER0_voidSetCompareValue(250);
	TIMER0_voidSetCallBack(TIMER0_Tick_ISR);


	/* Set PWM Top Value to 10000 for the new Fan limits */
	PWM_voidSetTopValue(FAN_MAX_SPEED);
	u16 Local_u16FanSpeed = 0;


	/* ==================================================================== */
	/* 1. CONFIGURING LEDS / LAMPS (OUTPUTS)                                */
	/* ==================================================================== */
	/* Kitchen Lamp */
	DIO_voidSetPinDirection(Kitchen_Led_Port, Kitchen_Led_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Kitchen_Led_Port, Kitchen_Led_Pin, DIO_u8LOW);

	/* Living Lamp */
	DIO_voidSetPinDirection(Living_Led_Port, Living_Led_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Living_Led_Port, Living_Led_Pin, DIO_u8LOW);

	/* Hallway Lamp */
	DIO_voidSetPinDirection(Hallway_Led_Port, Hallway_Led_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Hallway_Led_Port, Hallway_Led_Pin, DIO_u8LOW);

	/* Bedroom Lamp */
	DIO_voidSetPinDirection(Bedroom_Led_Port, Bedroom_Led_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Bedroom_Led_Port, Bedroom_Led_Pin, DIO_u8LOW);

	/* Bathroom Lamp */
	DIO_voidSetPinDirection(Bathroom_Led_Port, Bathroom_Led_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Bathroom_Led_Port, Bathroom_Led_Pin, DIO_u8LOW);

	/* Away Indicator LED */
	DIO_voidSetPinDirection(Away_Led_Port, Away_Led_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Away_Led_Port, Away_Led_Pin, DIO_u8LOW);

	/* Door Lock Actuator */
	DIO_voidSetPinDirection(Door_Lock_Port, Door_Lock_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Door_Lock_Port, Door_Lock_Pin, DIO_u8LOW);


	/* ==================================================================== */
	/* 2. CONFIGURING BUZZER / SIREN (OUTPUT)                               */
	/* ==================================================================== */
	DIO_voidSetPinDirection(Buzzer_Port, Buzzer_Pin, DIO_u8OUTPUT);
	DIO_voidSetPinValue(Buzzer_Port, Buzzer_Pin, DIO_u8LOW);


	/* ==================================================================== */
	/* 3. CONFIGURING MOTOR PWM PIN (OUTPUT)                                */
	/* ==================================================================== */
	/* Timer1 OC1A (PD5) is used for Motor PWM */
	DIO_voidSetPinDirection(Motor_Port, Motor_Pin, DIO_u8OUTPUT);


	/* ==================================================================== */
	/* 4. CONFIGURING ADC SENSOR PINS (INPUTS)                              */
	/* ==================================================================== */
	DIO_voidSetPinDirection(LDR_Port, LDR_Pin, DIO_u8INPUT);               /* ADC Ch 0 */
	DIO_voidSetPinDirection(Temperature_Port, Temperature_Pin, DIO_u8INPUT);/* ADC Ch 1 */
	DIO_voidSetPinDirection(Gas_Port, Gas_Pin, DIO_u8INPUT);               /* ADC Ch 2 */
	DIO_voidSetPinDirection(Humidity_Port, Humidity_Pin, DIO_u8INPUT);     /* ADC Ch 3 */


	/* ==================================================================== */
	/* 5. CONFIGURING EXTERNAL INTERRUPTS / PIR (INPUTS WITH PULL-UP)       */
	/* ==================================================================== */
	/* EXTI0 - PIR Hallway (PD2) */
	DIO_voidSetPinDirection(PIR_Hallway_Port, PIR_Hallway_Pin, DIO_u8INPUT);
	DIO_voidSetPinValue(PIR_Hallway_Port, PIR_Hallway_Pin, DIO_u8HIGH);   /* Enable Internal Pull-Up */

	/* EXTI1 - PIR Living Room (PD3) */
	DIO_voidSetPinDirection(PIR_Living_Port, PIR_Living_Pin, DIO_u8INPUT);
	DIO_voidSetPinValue(PIR_Living_Port, PIR_Living_Pin, DIO_u8HIGH);     /* Enable Internal Pull-Up */

	DIO_voidSetPinDirection(Door_Sense_Port, Door_Sense_Pin, DIO_u8INPUT);
	DIO_voidSetPinValue(Door_Sense_Port, Door_Sense_Pin, DIO_u8HIGH);     /* Enable Internal Pull-Up */

	/* Set Callbacks for both External Interrupts */
	EXTI0_voidSetCallBack(EXTI0_func);
	EXTI1_voidSetCallBack(EXTI1_func);

	u8 Local_u8PressedKey = NOT_PRESSED;     // NOT_PRESSED
	LCD_voidSendString((u8*)"System Ready");
	_delay_ms(1000);
	LCD_voidClear();


	/* ------------------------------------------------------------------ */

	/* Set Base States (SRC_DEFAULT) to OFF forever */
	for (u8 i = 0; i < NUM_OUTPUTS; i++) {
		Arb_voidRequestOutput(i, SRC_DEFAULT, 0, 0xFFFFFFFF);
	}

	PWM_voidSetCompareValue(0, Local_u16FanSpeed);
	EXTI0_voidEnable();
	EXTI1_voidEnable();
	GIE_voidEnable();
	/* --- Main Super-Loop --- */
	while (1) {
		/* 1. Poll Sensors */
		Gas  = ADC_u16GetGas();
		Temp = ADC_u8GetTemperature();
		LDR  = ADC_u8GetLDR();
		Hum  = ADC_u8GetHumidity();

		/* 2. Poll Keypad & Handle Access (Traditional if/else logic) */
		Local_u8PressedKey = KPD_u8GetPressedKey();

		if (!g_DoorUnlocked)
		{
			/* Check if system is locked out */
			if (g_LockoutEndTick > 0 && g_SystemTick < g_LockoutEndTick) {
				/* Keypad is ignored during lockout */
			} else {
				/* Lockout over, reset flag */
				if (g_LockoutEndTick != 0) {
					g_LockoutEndTick = 0;
					LCD_voidClear();
					LCD_voidSendString((u8*)"System Ready");
				}

				if (Local_u8PressedKey != NOT_PRESSED) {
					if (g_PINIndex == 0) {
						LCD_voidClear();
						LCD_voidSendString((u8*)"Enter PIN:");
					}

					g_EnteredPIN[g_PINIndex] = Local_u8PressedKey;
					g_PINIndex++;

					if (g_PINIndex >= PIN_LENGTH) {
						/* Verify PIN */
						u8 isCorrect = 1;
						for (u8 i = 0; i < PIN_LENGTH; i++) {
							if (g_EnteredPIN[i] != g_CorrectPIN[i]) isCorrect = 0;
						}

						if (isCorrect) {
							LCD_voidClear();

							LCD_voidSendString((u8*)"Door Unlocked");
							g_DoorUnlocked =1;
							g_FailedAttempts = 0;
							/* Unlock door for 10 seconds */
							Arb_voidRequestOutput(OUT_DOOR_LOCK, SRC_MANUAL, 1, SEC_TO_TICKS(10));

						} else {
							g_FailedAttempts++;
							LCD_voidClear();
							LCD_voidSendString((u8*)"Wrong PIN!");

							if (g_FailedAttempts >= MAX_PIN_ATTEMPTS) {
								g_LockoutEndTick = g_SystemTick + SEC_TO_TICKS(60);
								LCD_voidClear();
								LCD_voidSendString((u8*)"LOCKED OUT!");
								g_FailedAttempts = 0;
							}
						}
						g_PINIndex = 0; /* Reset for next entry */
					}
				}
			}
		}
		else if (g_DoorUnlocked)
		{
			DIO_voidSetPinValue(Bedroom_Led_Port,Bedroom_Led_Pin,DIO_u8HIGH);
			switch (Local_u8PressedKey) {

			case '1':
//				Arb_voidRequestOutput(OUT_BEDROOM, SRC_MANUAL, 1, 10);
				DIO_voidSetPinValue(Bedroom_Led_Port,Bedroom_Led_Pin,DIO_u8HIGH);
				break;
			case '2':
				Arb_voidRequestOutput(OUT_LIVING_LAMP, SRC_MANUAL, 1, SEC_TO_TICKS(1800));
				break;

			case '3':
				Arb_voidRequestOutput(OUT_HALLWAY, SRC_MANUAL, 1, SEC_TO_TICKS(1800));
				break;

			case 'A':   /* Away mode */
				Arb_voidRequestOutput(OUT_AWAY, SRC_MANUAL, 1, 0xFFFFFFFF);
				break;

			case 'D':   /* ALL OFF */
				Arb_voidRequestOutput(OUT_KITCHEN_LAMP, SRC_MANUAL, 0, SEC_TO_TICKS(1800));
				Arb_voidRequestOutput(OUT_LIVING_LAMP,  SRC_MANUAL, 0, SEC_TO_TICKS(1800));
				Arb_voidRequestOutput(OUT_HALLWAY,      SRC_MANUAL, 0, SEC_TO_TICKS(1800));
				break;

			case '*':
				g_DoorUnlocked = 0;
				g_PINIndex = 0;
				LCD_voidClear();
				LCD_voidSendString((u8*)"Locked - Enter PIN");
				Arb_voidRequestOutput(OUT_DOOR_LOCK, SRC_MANUAL, 0, 0xFFFFFFFF);
				break;
			default:
				break;
			}
		}

		/* 3. Evaluate Environmental Automation Rules */
		ENV_voidEvaluateRules(Gas, Temp, LDR, Hum);

		/* 4. Resolve Output Priorities and Drive Hardware */
		Arb_voidApplyOutputs();
	}

	return 0;
}

/* ========================================================================== */
/*                      ENVIRONMENTAL RULES EVALUATION                        */
/* ========================================================================== */
void ENV_voidEvaluateRules(u16 Gas, u8 Temp, u8 LDR, u8 Hum) {
	/* 1. Safety Rule: Gas Alarm */
	if (Gas >= GAS_THRESHOLD) {
		if (!g_GasTimerActive) {
			g_GasHighStartTick = g_SystemTick;
			g_GasTimerActive = 1;
		} else if ((g_SystemTick - g_GasHighStartTick) >= SEC_TO_TICKS(2)) {
			g_GasAlarmActive = 1;
		}
	} else {
		g_GasTimerActive = 0;
		g_GasAlarmActive = 0;
	}

	/* Emergency Override applies if Gas Alarm is active */
	if (g_GasAlarmActive) {
		Arb_voidRequestOutput(OUT_SIREN, SRC_SAFETY, 1, 1);
		Arb_voidRequestOutput(OUT_DOOR_LOCK, SRC_SAFETY, 1, 1);       /* Unlock to escape */
		Arb_voidRequestOutput(OUT_FAN, SRC_SAFETY, FAN_MAX_SPEED, 1); /* Max ventilation */
		return; /* Skip other rules during emergency */
	}

	/* 2. Temperature & Humidity Rule: Fan Speed Mapping */
	u16 targetFanSpeed = 0;

	if (Temp < TEMP_LOW) {
		targetFanSpeed = 0;
	} else if (Temp >= TEMP_HIGH) {
		targetFanSpeed = FAN_MAX_SPEED;
	} else {
		/* Map temperature to PWM Steps (e.g., 28C -> 2000, 29C -> 4000, etc.) */
		targetFanSpeed = (Temp - (TEMP_LOW - 1)) * FAN_SPEED_STEP;

		/* Clamp to max speed just in case */
		if (targetFanSpeed > FAN_MAX_SPEED) {
			targetFanSpeed = FAN_MAX_SPEED;
		}
	}

	/* Humidity Rule: Turn fan on low if humidity is too high, even if cool */
	if (Hum > HUMIDITY_HIGH_TH && targetFanSpeed == 0) {
		targetFanSpeed = FAN_SPEED_STEP; /* Start fan at lowest step (2000) to vent moisture */
	}

	Arb_voidRequestOutput(OUT_FAN, SRC_RULE, targetFanSpeed, 1);

	/* 3. Light & Motion Rule */
	u8 isDark = (LDR < LDR_DARK_TH) ? 1 : 0;
	u8 isBright = (LDR > LDR_BRIGHT_TH) ? 1 : 0;

	u8 isAway = DIO_u8GetPinValue(Door_Sense_Port, Door_Sense_Pin);

	/* Motion Extends Lamp On-Time by 120 seconds */
	if (g_MotionDetectedLiving) {
		g_MotionDetectedLiving = 0; // Clear flag
		Arb_voidRequestOutput(OUT_LIVING_LAMP, SRC_RULE, 1, SEC_TO_TICKS(5));
	}
	if (g_MotionDetectedHallway) {
		g_MotionDetectedHallway = 0; // Clear flag
		Arb_voidRequestOutput(OUT_HALLWAY, SRC_RULE, 1, SEC_TO_TICKS(6));
	}

	if(isAway == 0)
	{
		Arb_voidRequestOutput(OUT_AWAY, SRC_RULE, 1, 4);
	}
	else if(isAway == 1)
	{
		Arb_voidRequestOutput(OUT_AWAY, SRC_RULE, 0, 4);
	}

	if (isDark) {
		Arb_voidRequestOutput(OUT_KITCHEN_LAMP, SRC_RULE, 1, 1);
	} else if (isBright) {
		Arb_voidRequestOutput(OUT_KITCHEN_LAMP, SRC_RULE, 0, 1);
	}
}

/* ========================================================================== */
/*                      OUTPUT ARBITRATION MODEL                              */
/* ========================================================================== */
/**
 * @brief Submits a request to change a hardware state.
 * @param Value Accepts 1/0 for digital, or 0-10000 for Fan PWM.
 */
void Arb_voidRequestOutput(OutputID_t Output, SourcePriority_t Source, u16 Value, u32 DurationTicks) {
	if (Output < NUM_OUTPUTS && Source < NUM_SOURCES) {
		g_ArbValues[Output][Source] = Value;
		if (DurationTicks == 0xFFFFFFFF) {
			g_ArbTimeouts[Output][Source] = 0xFFFFFFFF; // Infinite
		} else {
			g_ArbTimeouts[Output][Source] = g_SystemTick + DurationTicks;
		}
	}
}

void Arb_voidApplyOutputs(void) {
	for (u8 outIdx = 0; outIdx < NUM_OUTPUTS; outIdx++) {

		u16 winningValue = 0;

		for (int srcIdx = (NUM_SOURCES - 1); srcIdx >= 0; srcIdx--) {
			if (g_ArbTimeouts[outIdx][srcIdx] == 0xFFFFFFFF || g_SystemTick <= g_ArbTimeouts[outIdx][srcIdx]) {
				winningValue = g_ArbValues[outIdx][srcIdx];
				break;
			}
		}

		/* Write Winning Value to Hardware */
		switch ((OutputID_t)outIdx) {
		case OUT_FAN:
			/* Send raw 0-10000 value to PWM driver directly */
			PWM_voidSetCompareValue(winningValue,0 );
			break;
		case OUT_KITCHEN_LAMP:
			DIO_voidSetPinValue(Kitchen_Led_Port, Kitchen_Led_Pin, (winningValue ? 1 : 0));
			break;
		case OUT_LIVING_LAMP:
			DIO_voidSetPinValue(Living_Led_Port, Living_Led_Pin, (winningValue ? 1 : 0));
			break;
		case OUT_DOOR_LOCK:
			DIO_voidSetPinValue(Door_Lock_Port, Door_Lock_Pin, (winningValue ? 1 : 0));
			break;
		case OUT_SIREN:
			DIO_voidSetPinValue(Buzzer_Port, Buzzer_Pin, (winningValue ? 1 : 0));
			break;
		case OUT_HALLWAY:
			DIO_voidSetPinValue(Hallway_Led_Port, Hallway_Led_Pin, (winningValue ? 1 : 0));
			break;
		case OUT_AWAY:
			DIO_voidSetPinValue(Away_Led_Port, Away_Led_Pin, (winningValue ? 1 : 0));
			break;
		case OUT_BEDROOM:
			DIO_voidSetPinValue(Bedroom_Led_Port, Bedroom_Led_Pin, (winningValue ? 1 : 0));
			break;
		default: break;
		}
	}
}

void App_voidInitPins(void)
{

}


/* ========================================================================== */
/*                              INTERRUPT SERVICE ROUTINES                    */
/* ========================================================================== */
void EXTI0_func(void) {
	/* Triggered by PIR Sensor */
	g_MotionDetectedHallway = 1;

}

void EXTI1_func(void) {
	/* Triggered by Hallway PIR */
	g_MotionDetectedLiving = 1;
}

void TIMER0_Tick_ISR(void) {
	/* Triggered by Timer0 Compare Match (System Tick) */
	g_SystemTick++;
}
