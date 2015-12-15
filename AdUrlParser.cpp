/*************************************************************************
	> File Name: AdUrlParser.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 19 Nov 2015 11:18:33 AM CST
 ************************************************************************/


#include "AdUrlParser.h"



AdUrlParser::AdUrlParser()
{
   if ((url = (url_field_t *)malloc(sizeof(url_field_t))) == NULL){
      cout<< "AdUrlParser:malloc error" << endl;
   }
      
   memset(url, 0, sizeof(url_field_t));

}

AdUrlParser::~AdUrlParser()
{

   if (!url) return;
   if (url->href) free(url->href);
   if (url->schema) free(url->schema);
   if (url->username) free(url->username);
   if (url->password) free(url->password);
   if (url->host) free(url->host);
   if (url->port) free(url->port);
   if (url->path) free(url->path);
   if (url->query)
   {
      int i;
      for (i = 0; i < url->query_num; i++)
      {
         free(url->query[i].name);
         free(url->query[i].value);
      }
      free(url->query);
   }
   if (url->fragment) free(url->fragment);
   free(url);

}

void AdUrlParser::UrlParser(const char *url)
{



}

void AdUrlParser::QueryParser(char *p_query)
{
   
   int offset;
   char *chr;
   offset = 0;
   int length = strlen(p_query);
   char *query = p_query;
   char *pch = strchr(query, '?');
   if (pch)
   {
      url->path = mystrndup(query, pch - query);
      query = pch + 1;
   }

   chr = strchr(query, '=');
   while (chr)
   {
      if (url->query)
         url->query =(S_QUERY *) realloc(url->query, (url->query_num + 1) * sizeof(*url->query));
      else
         url->query = (S_QUERY *) malloc(sizeof(*url->query));
      url->query[url->query_num].name = mystrndup(query, chr - query);
      query = chr + 1;
      chr = strchr(query, '&');
      if (chr)
      {
         url->query[url->query_num].value = mystrndup(query, chr - query);
         url->query_num++;
         query = chr + 1;
         chr = strchr(query, '=');
      }
      else
      {
         url->query[url->query_num].value = mystrndup(query, -1);
         url->query_num++;
         break;
      }
   }
}

void AdUrlParser::QueryParameterPrint()
{

   if (url->path)
   fprintf(stdout, "  - path:     '%s'\n", url->path);

   if (url->query_num > 0)
   {
      int i;
      fprintf(stdout, "  - query\n");
      for (i = 0; i < url->query_num; i++)
      {
         fprintf(stdout, "    * %s : %s\n", url->query[i].name, url->query[i].value);
      }
   }
   else
   {
      printf("no query!\n");
   }
}

char * AdUrlParser::mystrndup(const char *str, int n)
{
   char *dst;
   if (!str) return NULL;
   if (n < 0) n = strlen(str);
   if (n == 0) return NULL;
   if ((dst = (char *)malloc(n + 1)) == NULL)
      return NULL;
   memcpy(dst, str, n);
   dst[n] = 0;
   return dst;
}

int AdUrlParser::host_is_ipv4(char *str)
{
   if (!str) return 0;
   while (*str)
   {
      if ((*str >= '0' && *str <= '9') || *str == '.')
         str++;
      else
         return 0;
   }
   return 1;
}

bool AdUrlParser::getQueryParameter(const string& strName, string& strVal)
{
   if (url->query_num > 0)
   {
      int i;
      for (i = 0; i < url->query_num; i++)
      {
         if (0 == strncmp(url->query[i].name, strName.c_str(), strName.size()))
         {
            strVal = url->query[i].value;
            return true;
         }            
      }
      return false;
   }
   else
   {
      return false;
   }
}

#if 1
int main()
{
   while (1){
      
      string get_pid = "i";
      string get_val;
      AdUrlParser *parser = new AdUrlParser;
      //parser->QueryParser("/aaaaa?start=2015-10-19&end=2015-10-19");
      parser->QueryParser("/ex?i=mm_10982364_973726_8930541&cb=jsonp_callback_22854&callback=&userid=&o=&f=&n=&re=1366x768&r=1&cah=686&caw=1366&ccd=24&ctz=8&chl=1&cja=1&cpl=33&cmm=96&cf=18.0&cg=abb3a4bb884fdbc911c53e487b2a818e&pvid=a324ed143b06b8223ac6106316e52a03&pvid_1=7bd2e368594ddc959d961f05279705e1&ai=0&ac=61&prk=19692513&cas=prk&cbh=250&cbw=300&dx=1&u=http%3A%2F%2Fstatic.atm.youku.com%2Fsunxin%2Ftaobao%2F20110831%2Ftaobaox300x250x20110831.html%23105%2C2334%2C&k=&tt=");
      parser->QueryParameterPrint();

      parser->getQueryParameter(get_pid,get_val);
      cout << get_val << endl;
      delete parser;  
      sleep(10); 
   }


}
#endif
