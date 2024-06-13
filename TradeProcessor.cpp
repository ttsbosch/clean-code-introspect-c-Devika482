#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


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
void convertDatafromCSVtoXML(FILE* inputFile) {
    char line[1024];
    TradeRecord Records[1024];
    int lineCount = 0;
    int objectCount = 0;

    while (fgets(line, sizeof(line), inputFile)) {
        char* TradeInfoFeilds[3];
        int TotalTradeInfoFeilds = 0;
        char* token = stringtok(line, ",");
        while (token != NULL) {
            TradeInfoFeilds[TotalTradeInfoFeilds++] = token;
            token = stringtok(NULL, ",");
        }

        if (TotalTradeInfoFeilds != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, TotalTradeInfoFeilds);
            continue;
        }

        if (stringlen(TradeInfoFeilds[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, TradeInfoFeilds[0]);
            continue;
        }

        int TradeAmount;
        if (!intGetFromstringing(TradeInfoFeilds[1], &TradeAmount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, TradeInfoFeilds[1]);
        }

        double TradePrice;
        if (!toDouble(TradeInfoFeilds[2], &TradePrice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, TradeInfoFeilds[2]);
        }

        stringncpy(Records[objectCount].sourceCurrency, TradeInfoFeilds[0], 3);
        stringncpy(Records[objectCount].destinationCurrency, TradeInfoFeilds[0] + 3, 3);
        Records[objectCount].Lots = TradeAmount / LotSize;
        Records[objectCount].Price = TradePrice;
        objectCount++;
        lineCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int i = 0; i < objectCount; i++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", Records[i].sourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", Records[i].destinationCurrency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", Records[i].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", Records[i].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades processed\n", objectCount);
}
