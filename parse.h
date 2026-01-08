#ifndef PARSE_H
#define PARSE_H


#include "page.h"
#include "blog.h"

/* pages and assets */


int loadFiles(blog_t* blog, const char *dir);
int parsePageIndex(blog_t* blog);
int parseLib(blog_t* blog);
int parsePageSection(blog_t* blog, char *section);
int parseManifest(blog_t* blog);


/*
int loadFiles(const char *dir, FILE *manifest_file_str);
int parsePageIndex(FILE *manifest_file_str, int &page_count_var, page_t *web_pages);
int parseLib(FILE *manifest_file_str, char *main_css_str, char *blog_footer_str, char *blog_title_str, char *blog_slogan_str, char *blog_domain_str);
int parsePageSection(FILE *manifest_file_str, char *section, page_t *web_pages);
int parseManifest(FILE *manifest_file_str, int &page_count_var, page_t *web_pages, char *main_css_str, char *blog_footer_str, char *blog_title_str, char *blog_slogan_str, char *blog_domain_str);
*/


#endif
