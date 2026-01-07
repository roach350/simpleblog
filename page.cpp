
/* define class for web pages */


#include <cstring>
#include <iostream>

#include "config.h"
#include "page.h"

page_t::page_t(const char *t, const char *u){
	strncpy(title, t, 64);
	strncpy(url, u, 64);
}
page_t::page_t(){

}

char* page_t::getTitle(){
	return title;
}
char* page_t::getURL(){

	/* return URL relative to index*/
	return url;
}

char* page_t::getHTML(){
	return html;
}

char* page_t::getFName(){
	return fname;

}

void page_t::setTitle(const char *t){
	strncpy(title, t, 64);
}

void page_t::setHTML(const char *u){
	strncpy(html, u, 64);


}
void page_t::setFName(const char *f){
	strncpy(fname, f, 64);


}
void page_t::setURL(const char *u){
	/* set location relative to executable path */

	std::string temp = u;
	temp += html;
	strncpy(url, temp.c_str(), 64);

}

void page_t::setSB(const char *url){
	strncpy(sb, url, 64);
}

char* page_t::getSB(){
	return sb;
}

void page_t::print(){
	/* for debugging */
	std::cout << "page_t: " << title << ' ' << url << ' ' << css << ' ' << js << '\n';

}




int find_page(page_t array[], const char *key){

	for (int i = 0; i < PAGES_MAX; i++){
		if (strncmp(array[i].getTitle(), key, 64) == 0){
			return i;
		}

	}

	return -1;

}
