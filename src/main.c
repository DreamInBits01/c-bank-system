#include "main.h"
int main()
{
    int keep_running = true;
    char option;
    char name[USERNAME_BUFFER];
    char password[PASSWORD_BUFFER];
    bool is_user_logged_in = false;
    printf("Welcome to the bank system\n");
    while (keep_running)
    {
        sleep(1);
        print_options();
        scanf(" %c", &option);
        switch (option)
        {
        case 'L':
            printf("----Login was selected----\n");
            flush_stdin();
            if (user_logged_in(name))
            {
                PRINT_ERROR(USER_LOGGED_IN_ERROR);
                continue;
            }
            write_field_prompt(name, "name", USERNAME_BUFFER, 5);
            write_field_prompt(password, "password", PASSWORD_BUFFER, 9);
            AuthResult login_result = login(name, password);
            if (login_result.is_valid)
            {
                PRINT_SUCCESS(USER_LOGGED_IN, name, password);
                is_user_logged_in = true;
            }
            else
            {
                PRINT_ERROR(LOGIN_ERROR, name, password);
            }
            break;
        case 'G':
            logout(name, password, is_user_logged_in);
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
                PRINT_ERROR(REGISTER_ERROR);
            };
            break;
        case 'V':
            view_balance(name);
            break;
        case 'T':
            transfer(name);
            break;
        case 'Q':
            keep_running = false;
            exit(0);
        default:
            PRINT_ERROR(INVALID_OPTION);
            break;
        }
    }
}
void print_line(const char *line)
{
    printf("%s", line);
    fflush(stdout);
    usleep(100000); // 100ms
}
void print_options()
{
    print_line(CYAN BOLD "+-----------------+----------------------+\n");
    print_line("|     Option      |       Action         |\n");
    print_line("+-----------------+----------------------+\n" RESET);
    print_line("| " YELLOW "L" RESET "               | " GREEN "Login" RESET "                |\n");
    print_line("| " YELLOW "G" RESET "               | " GREEN "Logout" RESET "                |\n");
    print_line("| " YELLOW "R" RESET "               | " GREEN "Register" RESET "             |\n");
    print_line("| " YELLOW "D" RESET "               | " GREEN "Deposit" RESET "              |\n");
    print_line("| " YELLOW "V" RESET "               | " GREEN "View Balance" RESET "         |\n");
    print_line("| " YELLOW "T" RESET "               | " GREEN "Transfer" RESET "             |\n");
    print_line("| " YELLOW "W" RESET "               | " GREEN "Withdraw" RESET "             |\n");
    print_line("| " RED "Q" RESET "               | " RED "Quit" RESET "                 |\n");
    print_line(CYAN BOLD "+-----------------+----------------------+\n" RESET);
}