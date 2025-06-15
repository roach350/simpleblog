#include "lib.h"


char *page_index;
char *page_count;

/* files */
FILE *manifest_file;

int loadFiles(){

	manifest_file = fopen(MANIFEST_DIR, "r");
	if (manifest_file == NULL) {
        	std::cout << "Failed to open manifest.sb\n";
		return 0;
    	}

	return 1;

}

int parsePageIndex(){
	std::cout << "page index found\n";
}


int parseLib(){
	std::cout << "lib section found\n";
}

int parsePageSection(char *section){
	std::cout << section << " section found\n";
}


int parseManifest(){

	/* look for section titles */
	char c;
	char title[32];
	int i = 0;
	while(!(feof(manifest_file)) ){
		//Looks for [
		c = fgetc(manifest_file);
		//std::cout << c << '\n';
		if (c == '['){
			//std::cout << "bracket begin\n";
			c = fgetc(manifest_file);
			while (c != ']'){
				title[i] = c;
				i++;
				c = fgetc(manifest_file);
			}
			title[i] = 0; // add null terminator
			//std::cout << title << '\n';
			if (strcmp(title, "pages") == 0){
				parsePageIndex();
			}	


		}
	
	
	}







	return 1; //success

}
