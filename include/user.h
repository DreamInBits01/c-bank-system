#ifndef USER_H
#define USER_H
#include "utils.h"
typedef struct
{
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    int age;
    int amount;
} Person;
bool does_user_exist(const char username[USERNAME_BUFFER]);
Person get_user_info(const char username[USERNAME_BUFFER]);
void save_user(const Person *person);
bool transfer(const char from[USERNAME_BUFFER]);
#endif