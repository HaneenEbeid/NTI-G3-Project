#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* =========================================================================
 *                          Unsigned Data Types
 * ========================================================================= */
typedef unsigned char         uint8_t;   /* 8-bit unsigned integer  (0 to 255)         */
//typedef unsigned short        uint16_t;  /* 16-bit unsigned integer (0 to 65535)       */
typedef unsigned long         uint32_t;  /* 32-bit unsigned integer (0 to 4294967295)  */
typedef unsigned long long    uint64_t;  /* 64-bit unsigned integer                     */

/* =========================================================================
 *                          Signed Data Types
 * ========================================================================= */
typedef signed char           sint8_t;   /* 8-bit signed integer   (-128 to 127)       */
typedef signed short          sint16_t;  /* 16-bit signed integer  (-32768 to 32767)    */
typedef signed long           sint32_t;  /* 32-bit signed integer  (-2147483648 to ...) */
typedef signed long long      sint64_t;  /* 64-bit signed integer                    */

/* =========================================================================
 *                          Floating Point Types
 * ========================================================================= */
typedef float                 float32_t; /* 32-bit single precision floating point   */
typedef double                float64_t; /* 64-bit double precision floating point   */

/* =========================================================================
 *                          Boolean & Common Defines
 * ========================================================================= */
typedef uint8_t               bool_t;    /* Boolean data type                        */

#ifndef TRUE
#define TRUE                  ((bool_t)1)
#endif

#ifndef FALSE
#define FALSE                 ((bool_t)0)
#endif

#ifndef NULL
#define NULL                  ((void*)0)
#endif
#ifndef LOGIC_HIGH
#define LOGIC_HIGH  1
#endif

#ifndef LOGIC_LOW
#define LOGIC_LOW   0
#endif
#endif /* STD_TYPES_H_ */