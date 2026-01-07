#include <iostream>
#include <string>
#include <cstring>


#include "lib.h"
#include "page.h"
#include "parse.h"



int loadFiles(const char *dir, FILE *manifest_file_str){

	std::string manifest_dir = dir;
	manifest_dir += "/manifest.sb";

	manifest_file_str = fopen(manifest_dir.c_str(), "r");
	if (manifest_file_str == NULL) {
        	std::cout << "Failed to open manifest.sb\n";
		return 0;
    	}




	return 1;

}

int parsePageIndex(FILE *manifest_file_str, int &page_count_var, page_t *web_pages){
	
	std::cout << "[page index found]\n";
	char c = 0;
	char page[32];
	int page_index = 0;; //page index for class array	
	while(!(feof(manifest_file_str))){

		int i = 0; // page name index
		while((c = fgetc(manifest_file_str)) != ';'){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				page[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file_str, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}		
		
		}
		page[i] = 0; //add null terminator
		std::cout << "\tAdding index " << page << '\n'; 		

		/* setup page classes */

		web_pages[page_index].setTitle(page);
		//web_pages[page_index].setHTML(url);

		//web_pages[page_index].setSB();

		page_count_var++;
		page_index++;
		//reset and parse next line
		initStr(page, 32);
		
		
	}
	


}


int parseLib(FILE *manifest_file_str, char *main_css_str, char *blog_footer_str, char *blog_title_str, char *blog_slogan_str, char *blog_domain_str){
	std::cout << "[lib section found]\n";
	char c = 0;
	char token[32];
	char value[256];
	int equal_set = 0; //used for including spaces
	while(!(feof(manifest_file_str))){

		int i = 0; // page name index
		while((c = fgetc(manifest_file_str)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				token[i] = c;
				i++;
			}


			if (c == '['){
				fseek(manifest_file_str, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}		
		
		}
		equal_set = 1;
		token[i] = 0; //null terminator
		i = 0; // reset index
		while((c = fgetc(manifest_file_str)) != ';'){
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
				fseek(manifest_file_str, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}

		
		}
		equal_set = 0;
		value[i] = 0; //null terminator
		
		std::cout << "\tVALUE " << token << " = "  << value << '\n'; 		
		//parse and set values

		if (strcmp(token, "css") == 0){
			strncpy(main_css_str, value, 64); 
		}
	
		if (strcmp(token, "title") == 0){
			strncpy(blog_title_str, value, 128); 
		}	


		if (strcmp(token, "slogan") == 0){
			strncpy(blog_slogan_str, value, 128); 
		}

		if (strcmp(token, "footer") == 0){
			strncpy(blog_footer_str, value, 256); 
		}
		if (strcmp(token, "domain") == 0){
			strncpy(blog_domain_str, value, 64); 
		}

		//reset and parse next line
		initStr(token, 32);
		initStr(value, 64);

	}

}

int parsePageSection(FILE *manifest_file_str, char *section, page_t *web_pages){
	std::cout << '[' << section << " section found]\n";
	char c = 0;
	char token[32];
	char value[64];
	int page_index;
	while(!(feof(manifest_file_str))){

		int i = 0; // token index
		while((c = fgetc(manifest_file_str)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				token[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file_str, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}
			if ((feof(manifest_file_str))){
				return 1;
			}
		
		}
		token[i] = 0; //null terminator
		i = 0; // reset index

		while((c = fgetc(manifest_file_str)) != ';'){
			/* get url */
			if (c != '\n' && c != ' '){
				value[i] = c;
				i++;
			}
			if (c == '['){
				fseek(manifest_file_str, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}
			if ((feof(manifest_file_str))){
				return 1;
			}
		
		}
		value[i] = 0; //null terminator

		std::cout << "\tVALUE " << token << " = "  << value << '\n'; 		
		//parse and set values

		if (strcmp(token, "sb") == 0){
			
			page_index = find_page(web_pages, section);
			web_pages[page_index].setSB(value);


		}
		if (strcmp(token, "html") == 0){
			
			page_index = find_page(web_pages, section);
			web_pages[page_index].setHTML(value);


		}
		if (strcmp(token, "filename") == 0){
			page_index = find_page(web_pages, section);
			web_pages[page_index].setFName(value);

		}


		//reset and parse next line
		initStr(token, 32);
		initStr(value, 64);

	}

	return 1;

}


int parseManifest(FILE *manifest_file_str, int &page_count_var, page_t *web_pages, char *main_css_str, char *blog_footer_str, char *blog_title_str, char *blog_slogan_str, char *blog_domain_str){
	std::cout << "[PARSING MANIFEST]\n";
	/* look for section titles */
	char c;
	char title[32];
	int i = 0;
	while(!(feof(manifest_file_str)) ){
		//Looks for [
	
		c = fgetc(manifest_file_str);
		//std::cout << c << '\n';
		if (c == '['){
			//std::cout << "bracket begin\n";
			c = fgetc(manifest_file_str);
			while (c != ']'){
				title[i] = c;
				i++;
				c = fgetc(manifest_file_str);
			}
			title[i] = 0; // add null terminator
			//std::cout << title << '\n';
			if (strcmp(title, "pages") == 0){
				parsePageIndex(manifest_file_str, page_count_var, web_pages);
			}
			if (strcmp(title, "lib") == 0){
				parseLib(manifest_file_str, main_css_str, blog_footer_str, blog_title_str, blog_slogan_str, blog_domain_str);
			}
			/* check found pages */

			int valid_page = find_page(web_pages, title);
			if (valid_page != -1){
				parsePageSection(manifest_file_str, title, web_pages);
 
			}		

	
	
			i = 0; //reset index
			initStr(title, 32);



		}
	
	
	}





	fclose(manifest_file_str);
	return 1; //success

}
