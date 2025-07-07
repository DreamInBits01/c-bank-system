#include "auth.h"
#include <stdlib.h>
int main()
{
    int keep_running = true;
    char option;
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    printf("Welcome to the bank system\n");
    while (keep_running)
    {
        printf("----OPTIONS----\n");
        printf("----L for Login----\n");
        printf("----R for Register----\n");
        printf("----D for Deposit----\n");
        printf("----T for Transfer----\n");
        printf("----D for Withdraw----\n");
        printf("----Q for Quit----\n");
        scanf(" %c", &option);

        switch (option)
        {
        case 'L':
            printf("----Login was selected----\n");
            flush_stdin();
            write_field_prompt(name, "name", USERNAME_BUFFER, 5);
            write_field_prompt(password, "password", PASSWORD_BUFFER, 9);
            AuthResult login_result = login(name, password);
            if (login_result.is_valid)
            {
                printf("Logged in successfuly with the credentials (name:%s, password:%s)\n", name, password);
            }
            else
            {
                printf("Error while logging in, please check your credentials (name:%s, password:%s)\n", name, password);
            }
            break;
        case 'R':
            printf("----Register was selected----\n");
            AuthResult create_user_result = create_user();
            if (create_user_result.is_valid)
            {
                save_user(&create_user_result.person);
            }
            else
            {
                printf("Error while creating a user!\n");
            };
            break;
        case 'Q':
            keep_running = false;
            exit(0);
        default:
            printf("Please select a valid option\n");
            break;
        }
    }
}
