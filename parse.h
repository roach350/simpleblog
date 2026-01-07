#include "page.h"

#ifndef PARSE_H
#define PARSE_H

/* pages and assets */
/*
page_t web_pages[PAGES_MAX];

int page_count = 0;

// strings

char main_css[64]; //main css for all websites
char blog_footer[256];
char blog_title[128];
char blog_slogan[128];
char blog_domain[64];

// files 
FILE *manifest_file;



int loadFiles(const char *dir);
int parsePageIndex();
int parseLib();
int parsePageSection(char *section);
int parseManifest();
*/


int loadFiles(const char *dir, FILE *manifest_file_str);
int parsePageIndex(FILE *manifest_file_str, int &page_count_var, page_t *web_pages);
int parseLib(FILE *manifest_file_str, char *main_css_str, char *blog_footer_str, char *blog_title_str, char *blog_slogan_str, char *blog_domain_str);
int parsePageSection(FILE *manifest_file_str, char *section, page_t *web_pages);
int parseManifest(FILE *manifest_file_str, int &page_count_var, page_t *web_pages, char *main_css_str, char *blog_footer_str, char *blog_title_str, char *blog_slogan_str, char *blog_domain_str);



#endif
