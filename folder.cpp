/* 
	simpleblog 
	directory structure maker

*/



#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include "folder.h"
#include "config.h"




int makeDirs(const char *dir){

	/* directory strings */
	std::string web_dir = "";
	std::string pages_dir = "";
	std::string lib_dir = "";

	std::string contents_dir = "";
	std::string blog_dir = "";
	std::string extra_dir = "";
	std::string assets_dir = "";
	/*file strings */
	std::string index_sb_file = "";
	std::string index_html_file = "";

	/* build strings */

	web_dir += dir;
	web_dir += "/web";
	pages_dir += dir;
	pages_dir += "/web/pages";
	lib_dir += dir;
	lib_dir += "/web/lib";

	contents_dir += dir;
	contents_dir += "/contents";

	blog_dir += contents_dir;
	blog_dir += "/blog";
	
	extra_dir += contents_dir;
	extra_dir += "/extra";

	assets_dir += extra_dir;
	assets_dir += "/assets";


	/* mkdirs */
	mkdir(dir, 0700);
	mkdir(web_dir.c_str(), 0700);
	mkdir(pages_dir.c_str(), 0700);
	mkdir(lib_dir.c_str(), 0700);
	mkdir(contents_dir.c_str(), 0700);
	mkdir(blog_dir.c_str(), 0700);
	mkdir(extra_dir.c_str(), 0700);
	mkdir(assets_dir.c_str(), 0700);
	std::cout << "Made directories under " << dir << '/' << '\n';



	return 1; //success
}
