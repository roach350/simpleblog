#ifndef WRITE_H
#define WRITE_H


/* 
	simpleblog
	writes html files
*/


#include "blog.h"
#include "page.h"
//#include "parse.h"




/* high level writer functions (old writ.h) */
void writeAll(blog_t* blog, const char *dir);
int writeBlogs(blog_t* blog);
int openFiles(blog_t* blog, const char *dir);

/*specific write functions (writers.h)*/






void write_header(FILE *fptr, blog_t* blog, int blog_index, int lib);
void write_nav(FILE *fptr, blog_t* blog);
void write_nav_index(FILE *fptr, blog_t* blog, int dir);
void write_footer(FILE *fptr, blog_t* blog);
void write_blog_preview(FILE *fptr, blog_t* blog, int blog_index, int dir);
void write_n_blog_preview(FILE *fptr, blog_t* blog, int n, int dir);
void write_heading(FILE *fptr, char *string, int heading);
void write_code_sec(FILE *fptr, int blog_index, int start, int end);
void write_paragraph(FILE *fptr, char *string);
void write_pic(FILE *fptr, char *pic, char *pic_fs, char *pic_alt);
void write_start_ulist(FILE *fptr);
void write_append_ulist(FILE *fptr, char *string);
void write_end_ulist(FILE *fptr);
void write_index(FILE *fptr, blog_t* blog);
void write_blog_index(FILE *fptr, blog_t* blog);
void write_page(FILE *fptr, blog_t* blog);
void write_blog(FILE *fptr, blog_t* blog, int blog_index);
void write_contents(FILE *fptr, blog_t* blog, int blog_index);

#endif
