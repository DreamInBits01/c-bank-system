#ifndef AUTH_H
#define AUTH_H
#include "utils.h"
#include "user.h"
typedef struct
{
    Person person;
    bool is_valid;
} AuthResult;
AuthResult login(char username[USERNAME_BUFFER], char password[PASSWORD_BUFFER]);
AuthResult create_user();
#endif