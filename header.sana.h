/*
 * ------------------------- *
 * Application : SANA        *
 * Version : 3.2             *
 * By : Md. Salman Morshed   *
 * salmanmorshed@gmail.com   *
 * Date : 13-08-2012         *
 * ------------------------- *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>


typedef struct {
    char *data;
    size_t size;
} dataHolder;


char *URLEncode(char *);
char *GetXMLReply(char *, char *, char *);
char *FormatXMLReply(char *, char);
char *GetCustomerID(char *);
int VersionCheck();
static size_t WriteFunction(void *, size_t, size_t, void *);
