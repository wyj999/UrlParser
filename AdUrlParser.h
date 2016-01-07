/*************************************************************************
	> File Name: AdUrlParser.h
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Nov 2015 11:16:33 AM CST
 ************************************************************************/

#ifndef _ADURLPARSER_H
#define _ADURLPARSER_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
using namespace std;

static const char *str_hosttype[] = { "host ipv4", "host ipv6", "host domain", NULL };

typedef enum
{
   HOST_IPV4,
   HOST_IPV6,
   HOST_DOMAIN
} host_type_t;

typedef struct {
      char *name;
      char *value;
} S_QUERY;

typedef struct _url_field
{
   host_type_t host_type;
   char *href;
   char *schema;
   char *username;
   char *password;
   char *host;
   char *port;
   char *path;
   int query_num;
   S_QUERY *query;
   char *fragment;
} url_field_t;

class AdUrlParser
{
public:
    AdUrlParser();
    ~AdUrlParser();
    void ParserClean();
    void UrlParser(const char *str);
    void QueryParser(char *query);

    void QueryParameterPrint();
    void AdUrlPrint();

    bool getQueryParameter(const string & strName, string & strVal);
private:
    int host_is_ipv4(char *str);
    char *mystrndup(const char *str, int n);
    
    url_field_t* url;

};


#endif
