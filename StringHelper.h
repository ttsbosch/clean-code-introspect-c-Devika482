
char** SplitString(const char* inputstring, char delimiter) {
    int noofdelimiter = 0;
    const char* StringPtr = inputstring;
    while (*StringPtr != '\0') {
        if (*StringPtr++ == delimiter) {
            noofdelimiter++;
        }
    }
    char** stringDuplicaionBuffer = (char**)malloc(sizeof(char*) * (noofdelimiter + 2));
    int index = 0;
    StringPtr = inputstring;
    char* stringBufferWithoutDelimiter = (char*)malloc(stringlen(inputstring) + 1);
    int stringposition = 0;
    while (*StringPtr != '\0') {
        if (*StringPtr == delimiter) {
            stringBufferWithoutDelimiter[stringposition] = '\0';
            stringDuplicaionBuffer[index++] = stringdup(stringBufferWithoutDelimiter);
            stringposition = 0;
        } else {
            stringBufferWithoutDelimiter[stringposition++] = *StringPtr;
        }
        StringPtr++;
    }
    stringBufferWithoutDelimiter[j] = '\0';
    stringDuplicaionBuffer[index++] = stringdup(stringBufferWithoutDelimiter);
    stringDuplicaionBuffer[index] = NULL;
    free(stringBufferWithoutDelimiter);
    return stringDuplicaionBuffer;
}
