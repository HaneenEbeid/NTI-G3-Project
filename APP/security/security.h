#ifndef SECURITY_H_
#define SECURITY_H_

#include <stdint.h>
#include <stdbool.h>

#define PASSCODE_LENGTH 4
#define MAX_ATTEMPTS    3

void SECURITY_init(void);
bool SECURITY_verifyPasscode(const char *enteredPasscode);
bool SECURITY_changePasscode(const char *oldPasscode, const char *newPasscode);
bool SECURITY_isLocked(void);
void SECURITY_resetAttempts(void);

#endif