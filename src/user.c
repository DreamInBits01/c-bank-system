#include "utils.h"
#include "user.h"
#include "error_messages.h"
#include "success_messages.h"
#include "printf_macros.h"
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
        PRINT_ERROR(FILE_NOT_FOUND);
        return person;
    };
    bool found = false;
    char line_buffer[256];
    while (fgets(line_buffer, sizeof(line_buffer), users))
    {
        int fields_read = sscanf(
            line_buffer,
            READ_USER,
            person.name,
            person.password,
            &person.age,
            &person.amount);
        if (USER_FIELDS_NUMBER == fields_read && strcmp(person.name, username) == 0)
        {
            found = true;
            break;
        }
    };
    if (!found)
    {
        memset(&person, 0, sizeof(person));
    }
    fclose(users);
    return person;
};
bool transfer(const char from[USERNAME_BUFFER])
{
    // change to use a struct and return an error message
    bool success = false;
    // person how'll get poorer
    Person whom_transfering = get_user_info(from);
    if (whom_transfering.amount == 0)
    {
        PRINT_ERROR(TRANSACTION_AMOUNT_ZERO);
        fflush(stdout);
        success = false;
        return success;
    }
    flush_stdin();
    char transfer_to[USERNAME_BUFFER];
    int amount;
    char line_buffer[256];
    write_field_prompt(transfer_to, "Name To Transfer to", USERNAME_BUFFER, 20);
    if (strcmp(whom_transfering.name, transfer_to) == 0)
    {
        PRINT_ERROR(SELF_TRANSFER_ERROR);
        fflush(stdout);
        success = false;
        return success;
    }
    printf("Enter an amount\n");
    int amount_enter_result = scanf("%d", &amount);
    if (amount_enter_result != 1 || amount <= 0)
    {
        PRINT_ERROR(INVALID_AMOUNT);
        success = false;
        return success;
    }
    if (whom_transfering.amount < amount)
    {
        PRINT_ERROR(AMOUNT_TOO_HIGH);
        fflush(stdout);
        success = false;
        return success;
    }
    FILE *users = fopen("db/users.txt", "r");
    FILE *temp = fopen("db/users_temp.txt", "w");
    if (users == NULL || temp == NULL)
    {
        if (users)
            fclose(users);
        if (temp)
            fclose(temp);
        PRINT_ERROR(FILE_NOT_FOUND);
        success = false;
        return success;
    };
    // person how'll get rich
    Person current_user = {0};
    while (fgets(line_buffer, sizeof(line_buffer), users))
    {
        int fields_read = sscanf(
            line_buffer,
            READ_USER,
            current_user.name,
            current_user.password,
            &current_user.age,
            &current_user.amount);
        if (fields_read == USER_FIELDS_NUMBER && strcmp(current_user.name, transfer_to) == 0)
        {
            int current_user_new_amount = current_user.amount + amount;
            fprintf(
                temp,
                WRITE_USER,
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
                WRITE_USER,
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
        PRINT_ERROR(USER_NOT_FOUND);
        fflush(stdout);
    }
    else
    {
        FILE *transactions = fopen("db/transactions.txt", "a");
        if (transactions == NULL)
        {
            printf(FILE_NOT_FOUND);
            fflush(stdout);
            success = false;
            return success;
        }
        time_t now = time(NULL);
        struct tm *local_time = localtime(&now);
        char transaction_date_buffer[64];
        strftime(transaction_date_buffer, sizeof(transaction_date_buffer), "%Y-%m-%d %H:%M:%S", local_time);
        fprintf(transactions, WRITE_TRANSACTION, from, transfer_to, amount, transaction_date_buffer);
        PRINT_SUCCESS(USER_TRANSFERRED, amount, transfer_to);
        fflush(stdout);
        fclose(transactions);
    }
    fclose(users);
    fclose(temp);
    remove("db/users.txt");
    rename("db/users_temp.txt", "db/users.txt");

    return success;
}
void view_balance(char username[USERNAME_BUFFER])
{
    Person user = get_user_info(username);
    if (!user.name[0])
    {
        PRINT_ERROR(USER_NOT_FOUND);
        fflush(stdout);
    }
    else
    {
        PRINT_SUCCESS(VIEW_BALANCE, user.amount);
        fflush(stdout);
    };
}
