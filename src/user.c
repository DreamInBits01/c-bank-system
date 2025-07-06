#include "include/utils.h"
#include "include/user.h"

Person get_user_info(const char username[USERNAME_BUFFER])
{
    FILE *file = fopen("users.txt", "r");
    Person person;
    if (file == NULL)
    {
        printf("Error while opening the file (get_user_info)");
        return person;
    };
    int fscanf_result;
    fscanf_result = fscanf(file, READ_USER_FROM_FILE, person.name, person.password, &person.age);
    while (fscanf_result == 3)
    {
        if (strcmp(person.name, username) == 0)
        {
            break;
        };
        fscanf_result = fscanf(file, READ_USER_FROM_FILE, person.name, person.password, &person.age);
    };
    fclose(file);
    return person;
};
void save_user(const Person const *person)
{
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("Error while saving the user...\n");
        return;
    };
    int does_user_exist_result = does_user_exist(person->name);
    if (does_user_exist_result)
    {
        printf("Username is already taken\n");
        return;
    }
    fprintf(file, WRITE_USER_INTO_FILE, person->name, person->password, person->age);
    printf("User is saved successfuly\n");
    fclose(file);
};