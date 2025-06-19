#include "lib.h"
#include "page.h"


/* pages and assets */

page_t web_pages[MAX_WEB_PAGES];

int page_count = 0;

char main_css[64]; //main css for all websites



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

int parseBlogs(){


}


int parsePageIndex(){
	std::cout << "page index found\n";
	char c = 0;
	char page[32];
	char url[64];
	int page_index = 0;; //page index for class array	
	while(!(feof(manifest_file))){

		int i = 0; // page name index
		while((c = fgetc(manifest_file)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				page[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}		
		
		}
		page[i] = 0; //null terminator
		page_count++;
		i = 0; // reset index
		while((c = fgetc(manifest_file)) != ';'){
			/* get url */
			if (c != '\n' && c != ' '){
				url[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}

		
		}
		url[i] = 0; //null terminator

		std::cout << "Found index for " << page << '@' << url << '\n'; 		

		web_pages[page_index].setTitle(page);
		web_pages[page_index].setHTML(url);
		page_index++;
		//reset and parse next line
		initStr(page, 32);
		initStr(url, 64);
		
		
	}
	


}


int parseLib(){
	std::cout << "lib section found\n";
	char c = 0;
	char token[32];
	char value[64];
	while(!(feof(manifest_file))){

		int i = 0; // page name index
		while((c = fgetc(manifest_file)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				token[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}		
		
		}
		token[i] = 0; //null terminator
		i = 0; // reset index
		while((c = fgetc(manifest_file)) != ';'){
			/* get url */
			if (c != '\n' && c != ' '){
				value[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}

		
		}
		value[i] = 0; //null terminator

		std::cout << "VALUE " << token << " = "  << value << '\n'; 		
		//parse and set values

		if (strcmp(token, "css") == 0){
			strncpy(main_css, value, 64); 
		}

		//reset and parse next line
		initStr(token, 32);
		initStr(value, 64);

	}

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
			if (strcmp(title, "lib") == 0){
				parseLib();
			}
			/* check found pages */

			int valid_page = find_page(web_pages, title);
			if (valid_page != -1){
				std::cout << title << " does exist\n";
				
 
			}		

	
	
			i = 0; //reset index
			initStr(title, 32);



		}
	
	
	}






	fclose(manifest_file);
	return 1; //success

}
