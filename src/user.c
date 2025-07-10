#include "utils.h"
#include "user.h"

bool does_user_exist(const char username[USERNAME_BUFFER])
{
    bool success = false;
    Person person = get_user_info(username);
    if (strcmp(person.name, username) == 0)
    {
        success = true;
    };
    return success;
}
Person get_user_info(const char username[USERNAME_BUFFER])
{
    FILE *users = fopen("db/users.txt", "r");
    Person person = {0};
    if (users == NULL)
    {
        printf("Error while opening user's file (get_user_info)");
        return person;
    };
    char line_buffer[256];
    while (fgets(line_buffer, sizeof(line_buffer), users))
    {
        int fields_read = sscanf(
            line_buffer,
            READ_USER_FROM_FILE,
            person.name,
            person.password,
            &person.age,
            &person.amount);
        if (USER_FIELDS_NUMBER == fields_read && strcmp(person.name, username) == 0)
        {
            break;
        };
    };
    fclose(users);
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
    // change to use a struct and return an error message
    bool success = false;
    // person how'll get poor
    Person whom_transfering = get_user_info(from);
    if (whom_transfering.amount == 0)
    {
        printf("Your amount is zero! \\:\n");
        fflush(stdout);
        success = false;
        return success;
    }
    FILE *users = fopen("db/users.txt", "r");
    FILE *temp = fopen("db/users_temp.txt", "w");
    if (users == NULL || temp == NULL)
    {
        printf("Error while opening files");
    };
    flush_stdin();
    char transfer_to[USERNAME_BUFFER];
    int amount;
    char line_buffer[256];
    write_field_prompt(transfer_to, "Name To Transfer to", USERNAME_BUFFER, 20);
    if (strcmp(whom_transfering.name, transfer_to) == 0)
    {
        printf("You can't transfer to yourself \\:\n");
        fflush(stdout);
        // cleanup_transfer(users, temp);
        success = false;
        return success;
    }
    printf("Enter an amount\n");
    scanf("%d", &amount);
    if (whom_transfering.amount < amount)
    {
        printf("The amount choosen is bigger than your amount \\:\n");
        fflush(stdout);
        // cleanup_transfer(users, temp);
        success = false;
        return success;
    }
    // person how'll get rich
    Person current_user = {0};
    while (fgets(line_buffer, sizeof(line_buffer), users))
    {
        int fields_read = sscanf(
            line_buffer,
            READ_USER_FROM_FILE,
            current_user.name,
            current_user.password,
            &current_user.age,
            &current_user.amount);
        if (fields_read == USER_FIELDS_NUMBER && strcmp(current_user.name, transfer_to) == 0)
        {
            int current_user_new_amount = current_user.amount + amount;
            fprintf(
                temp,
                WRITE_USER_INTO_FILE,
                current_user.name,
                current_user.password,
                current_user.age,
                current_user_new_amount);
            success = true;
        }
        else if (fields_read == USER_FIELDS_NUMBER && strcmp(current_user.name, whom_transfering.name) == 0)
        {
            int current_user_new_amount = current_user.amount - amount;
            fprintf(
                temp,
                WRITE_USER_INTO_FILE,
                current_user.name,
                current_user.password,
                current_user.age,
                current_user_new_amount);
        }
        else
        {
            fputs(line_buffer, temp);
        }
    }
    if (!success)
    {
        printf("User not found \\:\n");
        fflush(stdout);
    }
    else
    {
        printf("Success! Amount:%d was transfered to:%s\n", amount, transfer_to);
        fflush(stdout);
    }
    fclose(users);
    fclose(temp);
    remove("db/users.txt");
    rename("db/users_temp.txt", "db/users.txt");

    return true;
}
void view_balance(char username[USERNAME_BUFFER])
{
    if (username[0] == '\0')
    {
        printf("Please enter a username!\n");
        fflush(stdout);
        return;
    }
    Person user = get_user_info(username);
    if (user.name[0] == '\0')
    {
        printf("User was not found!\n");
        fflush(stdout);
    }
    else
    {
        printf("Your balance is %d\n", user.amount);
        fflush(stdout);
    };
}