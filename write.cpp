/* 
	SimpleBlog
	writes html files
*/

#include <iostream>
#include <cstddef>
#include <string>
#include <cstring>


#include "config.h"
#include "parse.h"
#include "write.h"
#include "lib.h"
#include "blog_parser.h"


int openFiles(blog_t* blog, const char *dir){

	std::string url = dir;
	url += "/";
	url += INDEX_FILE_NAME;

	blog->index_file = fopen(url.c_str(), "w");

	if (blog->index_file == NULL){
		std::cout << "Could not make index.html\n";
		return 0;
	}
	/* blog index*/
	
	url = dir;
	int index = find_page(blog->web_pages, "Blog");
	url += "/";
	url += blog->web_pages[index].getHTML();
	blog->blog_index_file = fopen(url.c_str(), "w");
	
	if (blog->blog_index_file == NULL){
		std::cout << "Could not make " << url << '\n';
		return 0;
	}


	return 1;







}


int writeBlogs(blog_t* blog){
	for (int i = 0; i < blog->blog_count; i++){
        	FILE *blog_file = fopen(blog->blogs[i].getHTML(), "w");
                if (blog_file == NULL) {
                        std::cout << "couldn't open " << blog->blogs[i].getHTML() << '\n';
                        return 0;
                }
		write_blog(blog_file, blog, i);		                 
		fclose(blog_file);
         }
         return 1;



}


void writeAll(blog_t* blog, const char *dir) {
	std::cout << "[COMPILING]\n";
	openFiles(blog, dir);

	/* index.html */
	write_index(blog->index_file, blog);
	fclose(blog->index_file);
	std::cout << "\tindex.html written\n";
	/* blog index */
	write_blog_index(blog->blog_index_file, blog);
	fclose(blog->blog_index_file);
	std::cout << "\tblog.html written\n";
	
	/* blogs */
	writeBlogs(blog);
	std::cout << "\tblog HTML written\n";

}


/* specific write functions */


void write_header(FILE *fptr, blog_t* blog, int blog_index, int lib){
	fprintf(fptr, "<html>\n");
	fprintf(fptr, "<!DOCTYPE html>\n");
	fprintf(fptr, "\t<head>\n");
	if (blog_index >= 0){
		fprintf(fptr, "\t\t<title>%s</title>\n", blog->blogs[blog_index].getTitle());
	}else{

		fprintf(fptr, "\t\t<title>%s</title>\n", blog->blog_title);
	}
	
	std::string lib_str_css = "";	
	
	for (int i = 0; i < lib; i++){
		
		if (lib == 0){			
			break;
		}
		if (lib > 0){
			
		lib_str_css += "../";
		
		}


	}
	lib_str_css += blog->main_css;

	fprintf(fptr, "\t\t<link rel = 'stylesheet' href = '%s'>\n", lib_str_css.c_str());

	fprintf(fptr, "\t\t<meta name=\"twitter:card\" content=\"summary\"></meta>\n");
	fprintf(fptr, "\t\t<meta name=\"twitter:title\" content=\"%s\"></meta>\n", blog->blog_title);
	fprintf(fptr, "\t\t<meta name=\"twitter:description\" content=\"%s\"></meta>\n", blog->blog_slogan);
	fprintf(fptr, "\t</head>\n");
}


void write_nav(FILE *fptr, blog_t* blog){
	
	
	
	fprintf(fptr, "\t\t<hr>\n");
	fprintf(fptr, "\t\t\t<nav>\n");
	for (int i = 0; i < blog->page_count; i++){
		fprintf(fptr, "\t\t\t\t<a href='%s'>%s</a>\n", blog->web_pages[i].getFName(), blog->web_pages[i].getTitle());
	}


	fprintf(fptr, "\t\t</nav>\n");
	fprintf(fptr, "\t\t<hr>\n");


}


void write_nav_index(FILE *fptr, blog_t* blog, int dir){
	std::string offset = "";
	for (int i = 0; i < dir; i++){
		offset += "../";

	}



	fprintf(fptr, "\t\t<hr>\n");
	fprintf(fptr, "\t\t\t<nav>\n");
	for (int i = 0; i < blog->page_count; i++){
	
		std::string temp_offset = "";

		temp_offset += offset;
		temp_offset += blog->web_pages[i].getHTML();
		fprintf(fptr, "\t\t\t\t<a href='%s'>%s</a>\n", temp_offset.c_str(), blog->web_pages[i].getTitle());
	}


	fprintf(fptr, "\t\t</nav>\n");
	fprintf(fptr, "\t\t<hr>\n");


}





void write_footer(FILE *fptr, blog_t* blog){
	fprintf(fptr, "\t\t<footer>\n");
	fprintf(fptr, "\t\t\t<p>%s</p>\n", blog->blog_footer);
	fprintf(fptr, "\t\t<footer>\n");

}


void write_blog_preview(FILE *fptr, blog_t* blog, int blog_index, int dir){
	std::string html = "";
	for (int i = 0; i < dir; i++){
		html += "../";
	}
	html += blog->blogs[blog_index].getHTML();	
	fprintf(fptr, "\t\t\t\t<article>\n");
	fprintf(fptr, "\t\t\t\t\t<a href= '%s'><h3>%s</h3></a>\n", html.c_str(), blog->blogs[blog_index].getTitle());
	fprintf(fptr, "\t\t\t\t\t<p><b>PUBLISHED </b>%i/%i/%i</p>\n", blog->blogs[blog_index].getM(), blog->blogs[blog_index].getD(), blog->blogs[blog_index].getY());
	fprintf(fptr, "\t\t\t\t\t<p><b>WRITTEN BY </b>%s</p>\n", blog->blogs[blog_index].getAuthor());
	fprintf(fptr, "\t\t\t\t\t<p>%s</p>\n", blog->blogs[blog_index].getSummary());
	fprintf(fptr, "\t\t\t\t</article>\n");

}




void write_n_blog_preview(FILE *fptr, blog_t* blog, int n, int dir){

	
	fprintf(fptr, "\t\t\t<main>\n");
	for (int i = 0; i < n; i++){

		write_blog_preview(fptr, blog, blog->blog_count - 1 - i, dir);
	}

	fprintf(fptr, "\t\t\t</main>\n");

}


void write_heading(FILE *fptr, char *string, int heading){
	//std::cout << heading << '\n';
	fprintf(fptr, "\t\t<h%d>%s</h%d>\n", heading, string, heading);
	
	//fprintf(fptr, "\t\t<h1>%s</h1>\n", string);


}

void write_code_sec(FILE *fptr, int blog_index, int start, int end){


}

void write_paragraph(FILE *fptr, char *string){

	fprintf(fptr, "\t\t<p>%s</p>\n", string);
	//fprintf(fptr, "\t\t<br>\n");
}

void write_pic(FILE *fptr, char *pic, char *pic_fs, char *pic_alt){

	fprintf(fptr, "\t\t<a href='%s' ><img src='%s' alt='%s' width=\"25%\"></a> \n", pic_fs, pic, pic_alt);
	fprintf(fptr, "\t\t<p>%s</p>\n", pic_alt);
	fprintf(fptr, "\t\t<br>\n");
}


void write_start_ulist(FILE *fptr){

	fprintf(fptr, "\t\t<ul>\n");

}
void write_append_ulist(FILE *fptr, char *string){

	fprintf(fptr, "\t\t\t<li>%s</li>\n", string);
}

void write_end_ulist(FILE *fptr){

	fprintf(fptr, "\t\t</ul>\n");

}


void write_index(FILE *fptr, blog_t* blog){
	/* used for testing */
	write_header(fptr, blog, -1, 0);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", blog->blog_title);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", blog->blog_slogan);	
	fprintf(fptr, "\t\t</header>\n");


	write_nav_index(fptr, blog, 0);

	
	fprintf(fptr, "\t\t<h2>Latest News</h2>\n");
	write_n_blog_preview(fptr, blog, 3, 1);


	
	write_footer(fptr, blog);
	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");

}

void write_blog_index(FILE *fptr, blog_t* blog){
	write_header(fptr, blog, -1, 2);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", blog->blog_title);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", blog->blog_slogan);	
	fprintf(fptr, "\t\t</header>\n");


	write_nav(fptr, blog);

	
	fprintf(fptr, "\t\t<h2>All Blog Entries</h2>\n");
	write_n_blog_preview(fptr, blog, blog->blog_count, 3);


	
	write_footer(fptr, blog);
	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");



}


void write_page(FILE *fptr, blog_t* blog){
	/*not complete*/


	write_header(fptr, blog, -1, 0);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", blog->blog_title);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", blog->blog_slogan);	
	fprintf(fptr, "\t\t</header>\n");

	write_nav(fptr, blog);

	
	write_footer(fptr, blog);
	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");
	
}




void write_blog(FILE *fptr, blog_t* blog, int blog_index){
	write_header(fptr, blog, blog_index, 3);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", blog->blog_title);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", blog->blog_slogan);	
	fprintf(fptr, "\t\t</header>\n");




	write_nav_index(fptr, blog, 3);
	fprintf(fptr, "\t\t<h2>%s</h2>\n", blog->blogs[blog_index].getTitle());	
	fprintf(fptr, "\t\t<p><b>PUBLISHED </b>%i/%i/%i</p>\n", blog->blogs[blog_index].getM(), blog->blogs[blog_index].getD(), blog->blogs[blog_index].getY());
	fprintf(fptr, "\t\t<p><b>WRITTEN BY </b>%s</p>\n", blog->blogs[blog_index].getAuthor());

	write_contents(fptr, blog, blog_index);

	write_footer(fptr, blog);
	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");

}


void write_contents(FILE *fptr, blog_t* blog, int blog_index){
	int i = 0;

	/*temp vars */
	int heading = 0; char heading_str[128];
	int code_start = 0; int code_end = 0;
	char pic[64]; char pic_fs[64]; char pic_alt[256];
	initStr(pic, 64); initStr(pic_fs, 64);
	char paragraph[1024];
	initStr(paragraph, 1024);
	int end = 0; //used for checking if at end of content
	int ul = 0; //unordered list status
	
	/* parse and write contents of blog entry */

	while (i < BLOG_CONTENT_SIZE && end != 1){
		while (blog->blogs[blog_index].getChar(i) != '\n'){
			//should use switch
			/* begin parsing line */
			if (blog->blogs[blog_index].getChar(i) == '#'){

				//parse headings

				while (blog->blogs[blog_index].getChar(i) == '#'){	
					heading++;
					i++;
				}

				initStr(heading_str, 128);
				int j = 0;
				while (blog->blogs[blog_index].getChar(i) != '\n'){
					heading_str[j] = blog->blogs[blog_index].getChar(i);
					i++; j++;
				}
				heading_str[j] = 0;

				//write heading and new line
				
				std::cout << "write heading\n";
				write_heading(fptr, heading_str, heading);
				heading = 0;
			}


			if (blog->blogs[blog_index].getChar(i) == '^'){
				//begin code section
				code_start = i;
				while (blog->blogs[blog_index].getChar(i) != '^'){
					i++;
				}
				code_end = i;

				//write code section with code_end and code_i
				std::cout << "write code section\n";
			}

	
			if (blog->blogs[blog_index].getChar(i) == '$'){
				/*
				picture
				ex:
					$pic_prev.jpg,pic_fs.jpg;
				*/
				int j = 0;
				i++; //advance
				initStr(pic, 64); initStr(pic_fs, 64); initStr(pic_alt, 256);
				// pic
				while (blog->blogs[blog_index].getChar(i) != ','){
					pic[j] = blog->blogs[blog_index].getChar(i);
					i++; j++;
	
				}
				pic[j] = 0;
				j = 0;
				i++; //advance
				//fullsize pic
				while (blog->blogs[blog_index].getChar(i) != ','){
					pic_fs[j] = blog->blogs[blog_index].getChar(i);
					i++; j++;
	
				}
				pic_fs[j] = 0;
				j = 0;
				i++; //advance
				while (blog->blogs[blog_index].getChar(i) != ';'){
					pic_alt[j] = blog->blogs[blog_index].getChar(i);
					i++; j++;
	
				}
				
				pic_alt[j] = 0;

				//write pic
				std::cout << "write pic\n";
				write_pic(fptr, pic, pic_fs, pic_alt);
				
			}
			if (blog->blogs[blog_index].getChar(i) == '-'){
				/* unordered list */	
				//list not started
				char list_str[128];
				initStr(list_str, 128);
				int j = 0;
				i++; //advance
				while (blog->blogs[blog_index].getChar(i) != '\n'){
					list_str[j] = blog->blogs[blog_index].getChar(i);
					i++;
					j++;
				}
				list_str[j] = 0; //null terminator
				if (ul == 0){
					write_start_ulist(fptr);
					ul = 1;
				}
				if (ul == 1){
					//list already started
					write_append_ulist(fptr, list_str);
					if (blog->blogs[blog_index].getChar(i + 1) != '-'){
						//end of list
						write_end_ulist(fptr);
						ul = 0;
					}
				}


					
			}
		

			if (blog->blogs[blog_index].getChar(i) == '?'){
				/* print preview */
				int prev_count = blog->blogs[blog_index].getChar(i + 1) - '0'; //get count as int
				write_n_blog_preview(fptr, blog, prev_count, 4);
				i++; 

				
			}
			


			
			/* if line does not begin with special character, assume paragraph */
			char c = blog->blogs[blog_index].getChar(i);
			if (c != '#' && c != ';' && c != '$' && c != '^' && c != ' ' && c != 0 && c!= '-' && c!= '?' && ul == 0){
				int j = 0;
				while (blog->blogs[blog_index].getChar(i) != '\n' && blog->blogs[blog_index].getChar(i) != 0){
					paragraph[j] = blog->blogs[blog_index].getChar(i);
					j++;
					i++;
	
				}
				paragraph[j] = 0; //null terminate
				//write paragprah		

				std::cout << "write parapgraph\n";	

				write_paragraph(fptr, paragraph);
			}
			if (blog->blogs[blog_index].getChar(i) == 0){
				end = 1;
				break;
			}
		
			i++;

		}
		// new line


		i++;
	}



	




}


