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
void save_user(const Person *person);
bool logout(char *username, char *password, bool is_user_logged_in);
#endif