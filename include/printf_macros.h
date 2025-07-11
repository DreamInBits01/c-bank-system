#ifndef PRINT_MCAROS_H
#define PRINT_MCAROS
#include <stdio.h>
#include "printf_colors.h"
#define PRINT_SUCCESS(text, ...) printf(GREEN BOLD text RESET, ##__VA_ARGS__)
#define PRINT_ERROR(text, ...) printf(RED BOLD text RESET, ##__VA_ARGS__)
#define PRINT_WARRNING(text, ...) printf(YELLOW BOLD text RESET, ##__VA_ARGS__)
#endif