#include <cstring>

#include "config.h"
#include "blog.h"


blog_post_t::blog_post_t(){

	contents = new char[BLOG_CONTENT_SIZE];
}

blog_post_t::~blog_post_t(){

	delete contents;
}
//deep copy constrcutor
blog_post_t::blog_post_t(const blog_post_t &to_copy){
	contents = new char[BLOG_CONTENT_SIZE];
	strncpy(contents, to_copy.contents, BLOG_CONTENT_SIZE);
}

/* the setters */
void blog_post_t::setTitle(const char *t){
	strncpy(title, t, 64);
}

void blog_post_t::setAuthor(const char *a){

	strncpy(author, a, 64);
}	
void blog_post_t::setSummary(const char *s){
	strncpy(summary, s, 128);

} 


void blog_post_t::setDate(int m, int d, int y){
	month = m;
	day = d;
	year = y;
}

void blog_post_t::setHTML(const char *h){
	strncpy(html, h, 64);
}

void blog_post_t::setSB(const char *s){
	strncpy(sb, s, 64);
}

void blog_post_t::addChar(char c, int i){
	//for feeding individual characters to content buffer
	contents[i] = c;

}

/* the getters*/


char* blog_post_t::getTitle(){
	return title;
}

int blog_post_t::getM(){
	return month;
}

int blog_post_t::getD(){

	return day;
}

int blog_post_t::getY(){
	return year;
}

char* blog_post_t::getSummary(){
	return summary;

}

char* blog_post_t::getAuthor(){

	return author;
}

char* blog_post_t::getSB(){
	return sb;
}


char *blog_post_t::getHTML(){
	return html;
}

char blog_post_t::getChar(int i){
	return contents[i];
}		
char* blog_post_t::getContents(){
	return contents;
}


