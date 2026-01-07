/* 
	blog entry class and helper code


*/

#ifndef BLOG_H
#define BLOG_H

#include "page.h"
#include <cstdio>


class blog_post_t{

	private:
		char title[64];
		char author[64];
		char summary[128];
		int month, day, year;
		char html[64];
		char sb[64];
		char *contents;

	public:

		blog_post_t();

		~blog_post_t();

		//deep copy constrcutor
		blog_post_t(const blog_post_t &to_copy);
		/* the setters */
		void setTitle(const char *t);
		void setAuthor(const char *a);
		void setSummary(const char *s);
		void setDate(int m, int d, int y);
		void setHTML(const char *h);
		void setSB(const char *s);
		void addChar(char c, int i);
		char *getTitle();
		int getM();
		int getD();
		int getY();
		char *getSummary();
		char *getAuthor();
		char *getSB();
		char *getHTML();
		char getChar(int i);
		char *getContents();

};


struct blog_t{
	page_t *web_pages;
	blog_post_t *blogs;
	int page_count;
	int blog_count;
	//todo change to size_t
	char main_css[64]; //main css for all websites
	char blog_footer[256];
	char blog_title[128];
	char blog_slogan[128];
	char blog_domain[64];
	FILE *manifest_file;
	FILE *index_file, *blog_index_file;
};


#endif
