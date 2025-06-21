/* 
	SimpleBlog blog parser

*/


#include "blog.h"

//setup blogs

blog_post_t blogs[BLOG_MAX_POSTS];



int parseContents(FILE *blog_file, int blog_index){
	char c = 0;
	int i = 0;
	std::cout << "\tParsing contents begin\n";
	
	while((c = fgetc(blog_file)) != '`'){
		
		blogs[blog_index].addChar(c, i);
		i++;

	}
	std::cout << "\tParsing contents end\n";
	return 1;

}




int parseBlog(FILE *blog_file, int blog_index){
	std::cout << "[Parsing Blog Entry " << blog_index << "]\n";

	char c = 0;
	char token[32];
	char value[128];
	int m, d, y; //month day and year
	int equal_set = 0; //used for including spaces
	while(!(feof(blog_file))){
		
	int i = 0; // page name index
		while((c = fgetc(blog_file)) != '='){
			/* get page name  'name=...'*/
			if (c != '\n' && c != ' '){
				token[i] = c;
				i++;
			}


			if (c == '['){
				fseek(blog_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}

			if (c == '`'){
				/* time to parse contents */
				parseContents(blog_file, blog_index);
			}	

			if ((feof(blog_file))){
				return 1;
			}
	
		
		}
		equal_set = 1;
		token[i] = 0; //null terminator
		i = 0; // reset index
		while((c = fgetc(blog_file)) != ';'){
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
				fseek(blog_file, -1, SEEK_CUR);//decrement pointer
				// end of section
				return 1;
			}

			if ((feof(blog_file))){
				return 1;
			}


		
		}
		equal_set = 0;
		value[i] = 0; //null terminator
		
		std::cout << "\tVALUE " << token << " = "  << value << '\n'; 		
		//parse and set values

		if (strcmp(token, "title") == 0){
			blogs[blog_index].setTitle(value);
			
		}
	
		if (strcmp(token, "author") == 0){
			blogs[blog_index].setAuthor(value);
		}	


		if (strcmp(token, "month") == 0){
			m = std::stoi(value);
		}

		if (strcmp(token, "day") == 0){
			d = std::stoi(value);
		}

		if (strcmp(token, "year") == 0){

			y = std::stoi(value);
		}

		blogs[blog_index].setDate(m, d, y); //should be put somewhere else		


		if (strcmp(token, "summary") == 0){
	
			blogs[blog_index].setSummary(value);
		}





		//reset and parse next line
		initStr(token, 32);
		initStr(value, 128);

	}













}
