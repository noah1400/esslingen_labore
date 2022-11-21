int stringlength(const char *str) {
    const char *ptr = str;
    while(*(ptr++) != '\0');
    return ptr-1-str;
}
