/*
	SimpleBlog
	a minimal blog generator writen in C++

*/
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include <iostream>

#include "lib.h"
#include "config.h"
#include "parse.h"
#include "folder.h"
#include "blog_parser.h"

#include "write.h"


void printHelp(){

	std::cout << "simpleblog";
	std::cout << "\tVer: " << VERSION_STRING << '\n';
	std::cout << "USAGE: ./simpleblog <mode> <arguments>\n\n";
	std::cout << "Modes:\n";
	std::cout << "\thelp\t(display help)\n";  
	std::cout << "\tinit <dir>\t(setup a website directory structure)\n"; 
	std::cout << "\tcompile <dir>\t(parse .sb files and compile blog)\n";
	std::cout << "\tparse <dir>\t(parse .sb files, does not write)\n";
}





int main(int argc, char *argv[]){

	//create a blog_t 

	blog_t main_blog;
	//allocate memory and initlizaize

	main_blog.web_pages = new page_t[PAGES_MAX];
	main_blog.blogs = new blog_post_t[BLOG_MAX_POSTS];	
	main_blog.page_count = 0;
	main_blog.blog_count = 0;

	
	char *mode, *verb1, *verb2;
	/* parse arguments */
	switch (argc){
		case 1:
			std::cout << "No arguments provided: try 'simpleblog help'.\n";
			return 0;
			break;
		case 2:
			mode = argv[1];
			break;
		case 3:
			mode = argv[1];
			verb1 = argv[2];
			break;
		case 4:
			mode = argv[1];
			verb1 = argv[2];
			verb2 = argv[3];
			break;

		default:
			std::cout << "Too many arguments provided, see simpleblog help\n";
			break;

	}
	if (strcmp(mode, "help") == 0){
		printHelp();
	}	
	
	if (strcmp(mode, "init") == 0){
		makeDirs(verb1);
	}
	
	if (strcmp(mode, "compile") == 0){
		loadFiles(&main_blog, verb1);
		parseManifest(&main_blog);
		findBlogs(verb1, &main_blog);
		parseBlogs(&main_blog);
		writeAll(&main_blog, verb1);




	}	
	
	if (strcmp(mode, "parse") == 0){
		loadFiles(&main_blog, verb1);
		parseManifest(&main_blog);
		findBlogs(verb1, &main_blog);
		parseBlogs(&main_blog);

	}	


	delete[] main_blog.web_pages;
	delete[] main_blog.blogs;	
	return 0;
}
