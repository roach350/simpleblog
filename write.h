/* 
	simpleblog
	writes html files
*/


#include "parse.h"
#include "writers.h"

FILE *index_file;


int openFiles(){

	index_file = fopen(INDEX_LOCATION, "w");

	if (index_file == NULL){
		std::cout << "Could not make index.html\n";
		return 0;
	}

	return 1;




}



void writeAll(){

	openFiles();

	/* index.html */
	write_index(index_file);
	fclose(index_file);
}



