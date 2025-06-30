/* 
	simpleblog
	writes html files
*/


#include "parse.h"
#include "writers.h"


FILE *index_file, *blog_index_file;


int openFiles(const char *dir){

	std::string url = dir;
	url += "/";
	url += INDEX_FILE_NAME;

	index_file = fopen(url.c_str(), "w");

	if (index_file == NULL){
		std::cout << "Could not make index.html\n";
		return 0;
	}
	/* blog index*/
	
	url = dir;
	int index = find_page(web_pages, "Blog");
	url += "/";
	url += web_pages[index].getHTML();
	blog_index_file = fopen(url.c_str(), "w");
	
	if (blog_index_file == NULL){
		std::cout << "Could not make " << url << '\n';
		return 0;
	}


	return 1;







}


int writeBlogs(){
	for (int i = 0; i < blog_count; i++){
        	FILE *blog_file = fopen(blogs[i].getHTML(), "w");
                if (blog_file == NULL) {
                        std::cout << "couldn't open " << blogs[i].getHTML() << '\n';
                        return 0;
                }
		write_blog(blog_file, i);		                 
		fclose(blog_file);
         }
         return 1;



}


void writeAll(const char *dir){
	std::cout << "[COMPILING]\n";
	openFiles(dir);

	/* index.html */
	write_index(index_file);
	fclose(index_file);
	std::cout << "\tindex.html written\n";
	/* blog index */
	write_blog_index(blog_index_file);
	fclose(blog_index_file);
	std::cout << "\tblog.html written\n";
	
	/* blogs */
	writeBlogs();
	std::cout << "\tblog HTML written\n";

}



