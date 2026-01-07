#ifndef PAGE_H
#define PAGE_H

/* define class for web pages */

#include "config.h"


class page_t{
	private:
		char title[64];
		char fname[64];
		char url[64];
		char html[64]; //
		char css[64]; //css address
		char js[64]; //js address
		char sb[64]; // markup file location
	public:
		page_t(const char *t, const char *u);
		page_t();
		char* getTitle();
		char *getURL();
		char *getHTML();
		char *getFName();
		void setTitle(const char *t);
		void setHTML(const char *u);
		void setFName(const char *f);
		void setURL(const char *u);
		void setSB(const char *url);
		char *getSB();
		void print();
};




int find_page(page_t array[], const char *key);
#endif
