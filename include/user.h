#ifndef USER_H
#define USER_H
#include "utils.h"
typedef struct
{
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    int age;
} Person;
Person get_user_info(const char username[USERNAME_BUFFER]);
void save_user(const Person const *person);

#endif