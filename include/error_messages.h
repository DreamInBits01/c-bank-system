#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H
// AUTHENTICATION ERRORS
#define LOGIN_ERROR "Error while logging in, please check your credentials (name:%s, password:%s)\n"
#define REGISTER_ERROR "Error while creating a user!\n"
#define USERNAME_TAKEN "Username is already taken\n"
#define USER_NOT_LOGGED_IN "Please enter a username!\n"
#define USER_NOT_FOUND "User was not found!\n"
#define USER_NOT_LOGGED_IN_ERROR "Please login first!\n"
#define USER_LOGGED_IN_ERROR "You are already logged in!\n"
#define USER_NOT_FOUND_ERROR "User not found \\:\n"
#define SAVE_USER_ERROR "Error while saving the user...\n"
// TRANSACTION ERRORS
#define TRANSACTION_AMOUNT_ZERO "Amount cannot be zero!\n"
#define SELF_TRANSFER_ERROR "You cannot transfer to yourself \\:\n"
#define AMOUNT_TOO_HIGH "The amount chosen is bigger than your balance \\:\n"
// options errors
#define INVALID_OPTION "Please select a valid option\n"

// FILE ERRORS
#define FILE_NOT_FOUND "File not found or could not be opened\n"
#endif