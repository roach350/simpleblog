/* 
	simpleblog
	writes html files
*/


#include "parse.h"
#include "writers.h"


FILE *index_file;


int openFiles(const char *dir){

	std::string url = dir;
	url += "/";
	url += INDEX_FILE_NAME;

	index_file = fopen(url.c_str(), "w");

	if (index_file == NULL){
		std::cout << "Could not make index.html\n";
		return 0;
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

}



