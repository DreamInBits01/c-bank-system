#ifndef USER_H
#define USER_H
#include "utils.h"
#include <time.h>

typedef struct
{
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    int age;
    int amount;
} Person;
bool does_user_exist(const char username[USERNAME_BUFFER]);
Person get_user_info(const char username[USERNAME_BUFFER]);
bool transfer(const char from[USERNAME_BUFFER]);
void view_balance(char username[USERNAME_BUFFER]);
bool deposit(char username[USERNAME_BUFFER], bool is_user_logged_in);
#endif