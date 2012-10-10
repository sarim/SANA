/*
 * ------------------------- *
 * Application : SANA        *
 * Version : 3.3             *
 * By : Md. Salman Morshed   *
 * salmanmorshed@gmail.com   *
 * Date : 13-08-2012         *
 * ------------------------- *
 */


#include "header.sana.h"

/* *** Function to URL-encode a string to be used by libCURL  *** */
char *URLEncode(char *input) {
    char *output, *temp;
    temp = (char *) malloc(3 * (strlen(input) + 1) * sizeof (char));
    if (temp == NULL) {
        printf("Fatal Error: Memory allocation failed! [#001]\n");
        sleep(2);
        exit(1);
    } else {
        output = temp;
    }
    char *hex = "0123456789abcdef";
    while (*input != '\0') {
        if ('a' <= *input && *input <= 'z' || 'A' <= *input && *input <= 'Z' || '0' <= *input && *input <= '9' || *input == '-' || *input == '_' || *input == '.') {
            *temp = *input;
        } else if (*input == ' ') {
            *temp = '+';
        } else {
            *temp = '%';
            temp++;
            *temp = hex[*input >> 4];
            temp++;
            *temp = hex[*input & 0x0f];
        }
        input++;
        temp++;
    }
    *temp = '\0';
    return output;
}

/* *** Function to communicate with the Pandorabots server  *** */
char *GetXMLReply(char *botid, char *custid, char *inputData) {
    char *answer, *requestURL;
    CURL *handle;
    dataHolder variable;
    variable.data = malloc(1);
    variable.size = 0;
    char *encodedInput;
    encodedInput = URLEncode(inputData);
    requestURL = malloc((96 + strlen(inputData) + 1) * sizeof (char));
    if (requestURL == NULL) {
        printf("Fatal Error: Memory allocation failed! [#004]\n");
        sleep(2);
        exit(5);
    }
    strcpy(requestURL, "http://pandorabots.com/pandora/talk-xml");
    strcat(requestURL, "?botid=");
    strcat(requestURL, botid);
    if (strlen(custid)) {
        strcat(requestURL, "&custid=");
        strcat(requestURL, custid);
    }
    strcat(requestURL, "&input=");
    strcat(requestURL, encodedInput);
    free(encodedInput);
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, requestURL);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteFunction);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &variable);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_perform(handle);
    curl_easy_cleanup(handle);
    answer = variable.data;
    curl_global_cleanup();
    free(requestURL);
    return answer;
}

/* *** Function to format the XML output to get the results *** */
char *FormatXMLReply(char *xml, char returnType) {
    char startC[12], endC[8], *startP, *endP;
    if (!strlen(xml)) {
        printf("System Error: XML input is NULL. Is the network offline?\n");
        sleep(2);
        exit(2);
    }
    int sizeNeeded = 0;
    switch (returnType) {
        case 'a':
            strcpy(startC, "<that>");
            strcpy(endC, "</that>");
            sizeNeeded = 512;
            break;
        case 'b':
            strcpy(startC, "botid=\"");
            sizeNeeded = 16;
            break;
        case 'c':
            strcpy(startC, "custid=\"");
            sizeNeeded = 16;
            break;
        default:
            strcpy(startC, "status=\"");
            sizeNeeded = 1;
            break;
    }
    char *formatted, *temp;
    temp = (char *) malloc((sizeNeeded + 1) * sizeof (char));
    if (temp == NULL) {
        printf("Fatal Error: Memory allocation failed! [#002]\n");
        sleep(2);
        exit(3);
    } else {
        formatted = temp;
    }
    startP = strstr(xml, startC) + strlen(startC);
    if (returnType == 'a') {
        endP = strstr(xml, endC);
    } else {
        endP = startP + sizeNeeded;
    }
    while (1) {
        if (startP == endP) {
            *temp = '\0';
            break;
        }
        *temp = *startP;
        startP++;
        temp++;
    }
    free(xml);
    return formatted;
}

/* *** Function to manage the individual Customer ID  *** */
char *GetCustomerID(char *botid) {
    char *result = malloc((16 + 1) * sizeof (char));
    if (result == NULL) {
        printf("Fatal Error: Memory allocation failed! [#005]\n");
        sleep(2);
        exit(6);
    }
    FILE *fhandle;
    fhandle = fopen("customer.dat", "rb");
    if (fhandle == NULL) {
        char *newCustID;
        puts("Preparing SANA for the first-run...");
        newCustID = FormatXMLReply(GetXMLReply(botid, "", "startnewcustomer"), 'c');
        FILE *f2handle;
        f2handle = fopen("customer.dat", "wb");
        if (f2handle == NULL) {
            printf("System Error: Problem encountered with File I/O.\n");
            exit(7);
        }
        fputs(newCustID, f2handle);
        fclose(f2handle);
        puts("--------------------------------");
        return GetCustomerID(botid);
    } else {
        fgets(result, 17, fhandle);
        return result;
    }
}

/* *** WriteFunction to fetch and hold CURL data *** */
static size_t WriteFunction(void *contents, size_t size, size_t tempber, void *passedPointer) {
    size_t realSize = size * tempber;
    dataHolder *temp = (dataHolder *) passedPointer;
    temp->data = realloc(temp->data, temp->size + realSize + 1);
    if (temp->data == NULL) {
        printf("Fatal Error: Memory allocation failed! [#003]\n");
        sleep(2);
        exit(4);
    }
    memcpy(&(temp->data[temp->size]), contents, realSize);
    temp->size += realSize;
    temp->data[temp->size] = 0;
    return realSize;
}

/* *** Function to check new version availability *** */
int VersionCheck(char *theBotID) {
    puts(": Looking for updates...");
    char *vbk, *theCustID;
    theCustID = GetCustomerID(theBotID);
    vbk = FormatXMLReply(GetXMLReply(theBotID, theCustID, "latestversionnumber"), 'a');
    float latest = atof(vbk);
    if (latest > SANAVERSION) {
        puts(": New version is available!");
        printf("  Current: %1.1f, New: %1.1f\n", SANAVERSION, latest);
        puts(FormatXMLReply(GetXMLReply(theBotID, theCustID, "latestversioninfo"), 'a'));
        return 1;
    } else {
        printf("  You are using the latest version! [%1.1f]\n", latest);
        return 0;
    }
}

/* *** Function to replace a substring from inside a string *** */
char *StringReplace(char *str, char *what, char *with) {
    int strLen = strlen(str);
    int whatLen = strlen(what);
    int withLen = strlen(with);
    signed int delta = 0;
    delta = withLen - whatLen;
    int n = 0;
    char *foo = strstr(str, what);
    if (foo == NULL) return str;
    while (foo != NULL) {
        foo = strstr(foo + whatLen, what);
        n++;
    }
    int newLen = strLen + (n * delta);
    char *res = (char *) malloc(newLen + 1);
    memset(res, 0, newLen + 1);

    foo = strstr(str, what);
    while (foo != NULL) {
        strncat(res, str, foo - str);
        strcat(res, with);
        str = foo + whatLen;
        foo = strstr(str, what);
    }
    strcat(res, str);
    return res;
}
