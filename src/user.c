#include "utils.h"
#include "user.h"

bool does_user_exist(const char username[USERNAME_BUFFER])
{
    bool found = false;
    Person person = get_user_info(username);
    if (strcmp(person.name, username) == 0)
    {
        found = true;
    };
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
    fscanf_result = fscanf(file, READ_USER_FROM_FILE, person.name, person.password, &person.age, &person.amount);
    while (fscanf_result == 4)
    {
        if (strcmp(person.name, username) == 0)
        {
            break;
        };
        fscanf_result = fscanf(file, READ_USER_FROM_FILE, person.name, person.password, &person.age, &person.amount);
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
    fprintf(file, WRITE_USER_INTO_FILE, person->name, person->password, person->age, 0);
    printf("User is saved successfuly\n");
    fclose(file);
};

bool transfer(const char from[USERNAME_BUFFER])
{
    FILE *users = fopen("db/users.txt", "r");
    FILE *temp = fopen("db/temp.txt", "w");
    if (users == NULL || temp == NULL)
    {
        printf("Error while opening files");
    };
    flush_stdin();
    char transfer_to[USERNAME_BUFFER];
    int amount;

    char line_buffer[256];
    // char *current_line = fgets(line_buffer, sizeof(line_buffer), users);
    write_field_prompt(transfer_to, "Name To Transfer to", USERNAME_BUFFER, 20);
    printf("Enter amount");
    scanf("%d", &amount);
    while (fgets(line_buffer, sizeof(line_buffer), users))
    {
        printf("line: %s", line_buffer);
    }
    // printf("line %s\n", current_line);
    printf("User to send to %s, amount %d\n", transfer_to, amount);
    fclose(users);
    fclose(temp);

    return true;
}