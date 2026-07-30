#include "security.h"
#include <string.h>

static char g_storedPasscode[PASSCODE_LENGTH + 1] = "1234";
static uint8_t g_failedAttempts = 0;
static bool g_isLocked = false;

void SECURITY_init(void)
{
    g_failedAttempts = 0;
    g_isLocked = false;
}

bool SECURITY_verifyPasscode(const char *enteredPasscode)
{
    if (g_isLocked)
    {
        return false;
    }

    if (strncmp(enteredPasscode, g_storedPasscode, PASSCODE_LENGTH) == 0)
    {
        g_failedAttempts = 0;
        return true;
    }
    else
    {
        g_failedAttempts++;
        if (g_failedAttempts >= MAX_ATTEMPTS)
        {
            g_isLocked = true;
        }
        return false;
    }
}

bool SECURITY_changePasscode(const char *oldPasscode, const char *newPasscode)
{
    if (SECURITY_verifyPasscode(oldPasscode))
    {
        strncpy(g_storedPasscode, newPasscode, PASSCODE_LENGTH);
        g_storedPasscode[PASSCODE_LENGTH] = '\0';
        return true;
    }
    return false;
}

bool SECURITY_isLocked(void)
{
    return g_isLocked;
}

void SECURITY_resetAttempts(void)
{
    g_failedAttempts = 0;
    g_isLocked = false;
}