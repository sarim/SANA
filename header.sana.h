/*
 * ------------------------- *
 * Application : SANA        *
 * Version : 3.3             *
 * By : Md. Salman Morshed   *
 * salmanmorshed@gmail.com   *
 * Date : 13-08-2012         *
 * ------------------------- *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#define SANAVERSION 3.3

typedef struct {
    char *data;
    size_t size;
} dataHolder;


char *URLEncode(char *);
char *GetXMLReply(char *, char *, char *);
char *FormatXMLReply(char *, char);
char *GetCustomerID(char *);
char *StringReplace(char *, char *, char *);
int VersionCheck(char *);
static size_t WriteFunction(void *, size_t, size_t, void *);
