void append(char *dest, char* str) {
    while (*dest != '\0') { // find end of dest
        dest++;
    }
    while (*str != '\0') { // copy str to dest
        *dest = *str;
        dest++;
        str++;
    }
    *dest = '\0'; // terminate dest
}