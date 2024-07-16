#include "uefi-data-types.h"



void int_to_string(UINTN value, CHAR16 *str) {
    // Temporary buffer to hold the reverse string
    CHAR16 tempBuffer[20]; // Assuming UINTN will not exceed 19 digits + null terminator
    int i = 0;
    int j = 0;

    // Handle 0 explicitly
    if (value == 0) {
        str[0] = L'0';
        str[1] = L'\0';
        return;
    }

    // Convert integer to string in reverse order
    while (value != 0) {
        tempBuffer[i++] = (CHAR16)((value % 10) + L'0');
        value /= 10;
    }
    tempBuffer[i] = L'\0'; // Null-terminate the temporary string

    // Reverse the string into the output buffer
    while (i > 0) {
        str[j++] = tempBuffer[--i];
    }
    str[j] = L'\0'; // Null-terminate the output string
}