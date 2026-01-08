/* 
	SimpleBlog blog parser

*/
#ifndef BLOG_PARSER_H
#define BLOG_PARSER_H

#include "config.h"
#include "blog.h"

int findBlogs(const char *dir, blog_t *blog);
int parseBlogs(blog_t *blog);
int parseContents(FILE *blog_file, blog_t *blog, int blog_index);
int parseBlog(FILE *blog_file, blog_t *blog, int blog_index);
bool compareDates(blog_post_t &d1, blog_post_t &d2);
int sortBlogs(blog_post_t arr[], int n);


#endif
