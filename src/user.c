#include "utils.h"
#include "user.h"

bool does_user_exist(const char username[USERNAME_BUFFER])
{
    FILE *file = fopen("db/users.txt", "r");
    if (file == NULL)
    {
        printf("Error While opening the file...\n");
        return 0;
    }
    bool found = false;
    Person person = get_user_info(username);
    if (strcmp(person.name, username) == 0)
    {
        found = true;
    };
    fclose(file);
    return found;
}
Person get_user_info(const char username[USERNAME_BUFFER])
{
    FILE *file = fopen("db/users.txt", "r");
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
void save_user(const Person *person)
{
    FILE *file = fopen("db/users.txt", "a");
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