#include <iostream>
#include <string>
#include <cstring>


#include "lib.h"
#include "page.h"
#include "parse.h"



int loadFiles(blog_t* blog, const char *dir){

	std::string manifest_dir = dir;
	manifest_dir += "/manifest.sb";

	blog->manifest_file = fopen(manifest_dir.c_str(), "r");
	if (blog->manifest_file == NULL) {
        	std::cout << "Failed to open manifest.sb\n";
		return 0;
    	}




	return 1;

}

int parsePageIndex(blog_t *blog){
	
	std::cout << "[page index found]\n";
	char c = 0;
	char page[32];
	int page_index = 0;; //page index for class array	
	while(!(feof(blog->manifest_file))){

		int i = 0; // page name index
		while((c = fgetc(blog->manifest_file)) != ';'){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				page[i] = c;
				i++;
			}
			if (c == '['){
				fseek(blog->manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}		
		
		}
		page[i] = 0; //add null terminator
		std::cout << "\tAdding index " << page << '\n'; 		

		/* setup page classes */

		blog->web_pages[page_index].setTitle(page);
		//web_pages[page_index].setHTML(url);

		//web_pages[page_index].setSB();

		blog->page_count++;
		page_index++;
		//reset and parse next line
		initStr(page, 32);
		
		
	}
	


}


int parseLib(blog_t *blog){
	std::cout << "[lib section found]\n";
	char c = 0;
	char token[32];
	char value[256];
	int equal_set = 0; //used for including spaces
	while(!(feof(blog->manifest_file))){

		int i = 0; // page name index
		while((c = fgetc(blog->manifest_file)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				token[i] = c;
				i++;
			}


			if (c == '['){
				fseek(blog->manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}		
		
		}
		equal_set = 1;
		token[i] = 0; //null terminator
		i = 0; // reset index
		while((c = fgetc(blog->manifest_file)) != ';'){
			/* get url */
			if (c != '\n' && c != ' '){
				value[i] = c;
				i++;
			}

			if (c == ' ' && equal_set == 1){
				value[i] = c;
				i++;		
			}
			if (c == '['){
				fseek(blog->manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}

		
		}
		equal_set = 0;
		value[i] = 0; //null terminator
		
		std::cout << "\tVALUE " << token << " = "  << value << '\n'; 		
		//parse and set values

		if (strcmp(token, "css") == 0){
			strncpy(blog->main_css, value, 64); 
		}
	
		if (strcmp(token, "title") == 0){
			strncpy(blog->blog_title, value, 128); 
		}	


		if (strcmp(token, "slogan") == 0){
			strncpy(blog->blog_slogan, value, 128); 
		}

		if (strcmp(token, "footer") == 0){
			strncpy(blog->blog_footer, value, 256); 
		}
		if (strcmp(token, "domain") == 0){
			strncpy(blog->blog_domain, value, 64); 
		}

		//reset and parse next line
		initStr(token, 32);
		initStr(value, 64);

	}

}

int parsePageSection(blog_t *blog, char *section){
	std::cout << '[' << section << " section found]\n";
	char c = 0;
	char token[32];
	char value[64];
	int page_index;
	while(!(feof(blog->manifest_file))){

		int i = 0; // token index
		while((c = fgetc(blog->manifest_file)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				token[i] = c;
				i++;
			}
			if (c == '['){
				fseek(blog->manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}
			if ((feof(blog->manifest_file))){
				return 1;
			}
		
		}
		token[i] = 0; //null terminator
		i = 0; // reset index

		while((c = fgetc(blog->manifest_file)) != ';'){
			/* get url */
			if (c != '\n' && c != ' '){
				value[i] = c;
				i++;
			}
			if (c == '['){
				fseek(blog->manifest_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}
			if ((feof(blog->manifest_file))){
				return 1;
			}
		
		}
		value[i] = 0; //null terminator

		std::cout << "\tVALUE " << token << " = "  << value << '\n'; 		
		//parse and set values

		if (strcmp(token, "sb") == 0){
			
			page_index = find_page(blog->web_pages, section);
			blog->web_pages[page_index].setSB(value);


		}
		if (strcmp(token, "html") == 0){
			
			page_index = find_page(blog->web_pages, section);
			blog->web_pages[page_index].setHTML(value);


		}
		if (strcmp(token, "filename") == 0){
			page_index = find_page(blog->web_pages, section);
			blog->web_pages[page_index].setFName(value);

		}


		//reset and parse next line
		initStr(token, 32);
		initStr(value, 64);

	}

	return 1;

}


int parseManifest(blog_t *blog){
	std::cout << "[PARSING MANIFEST]\n";
	/* look for section titles */
	char c;
	char title[32];
	int i = 0;
	while(!(feof(blog->manifest_file)) ){
		//Looks for [
	
		c = fgetc(blog->manifest_file);
		//std::cout << c << '\n';
		if (c == '['){
			//std::cout << "bracket begin\n";
			c = fgetc(blog->manifest_file);
			while (c != ']'){
				title[i] = c;
				i++;
				c = fgetc(blog->manifest_file);
			}
			title[i] = 0; // add null terminator
			//std::cout << title << '\n';
			if (strcmp(title, "pages") == 0){
				parsePageIndex(blog);
			}
			if (strcmp(title, "lib") == 0){
				parseLib(blog);
			}
			/* check found pages */

			int valid_page = find_page(blog->web_pages, title);
			if (valid_page != -1){
				parsePageSection(blog, title);
 
			}		

	
	
			i = 0; //reset index
			initStr(title, 32);



		}
	
	
	}





	fclose(blog->manifest_file);
	return 1; //success

}
