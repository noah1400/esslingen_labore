int stringlength(const char *str) {
    const char *ptr = str;
    while(*(ptr++) != '\0'); // Increment ptr until it points to the null character
    return ptr-1-str; // Return the difference between the pointers
}
