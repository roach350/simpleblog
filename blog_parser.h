#include "config.h"
#include "blog.h"

/* 
	SimpleBlog blog parser

*/
#ifndef BLOG_PARSER_H
#define BLOG_PARSER_H

/*
//setup blogs

blog_post_t blogs[BLOG_MAX_POSTS];
int blog_count = 0;


int parseBlog(FILE *blog_file, int blog_index);
int parseContents(FILE *blog_file, int blog_index);
int findBlogs(const char *dir);
int parseBlogs();
bool compareDates(blog_post_t &d1, blog_post_t &d2);
int sortBlogs(blog_post_t arr[], int n);
*/

int findBlogs(const char *dir, blog_post_t *blogs, int &blog_count);
int parseBlogs(blog_post_t *blogs, int blog_count);
int parseContents(FILE *blog_file, int blog_index, blog_post_t *blogs);
int parseBlog(FILE *blog_file, int blog_index, blog_post_t *blogs);
bool compareDates(blog_post_t &d1, blog_post_t &d2);
int sortBlogs(blog_post_t arr[], int n);


#endif
