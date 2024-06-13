bool tryToConvertAsLongInt(const char* string, int* value) {
    char* endptr;
    *value = stringtol(string, &endptr, 10);
    if (endptr == string) {
        return 0;
    }
    return 1;
}
bool tryToConvertAsDouble(const char* string, double* value) {
    char* endptr;
    *value = stringtod(string, &endptr);
    if (endptr == string) {
        return 0;
    }
    return 1;
}
