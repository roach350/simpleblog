/* 
	SimpleBlog blog parser

*/
#include <dirent.h>

#include "blog.h"

//setup blogs

blog_post_t blogs[BLOG_MAX_POSTS];

int blog_count = 0;


int parseBlog(FILE *blog_file, int blog_index);
int parseContents(FILE *blog_file, int blog_index);


int findBlogs(const char *dir){
	std::cout << "[PARSING BLOGS]\n";
	/* setup */
	struct dirent *de;
	DIR *blog_dir;
	int i = 0; //index

	std::string blog_dir_str = dir;
	blog_dir_str += "/contents/blog";
	std::cout << "checking " << blog_dir_str.c_str() << " for blogs\n";
	blog_dir = opendir(blog_dir_str.c_str());

	if (blog_dir == NULL){
		std::cout << "Could not load blog dir\n";
		return 0;
	}

	/* index blogs */
	while ((de = readdir(blog_dir)) != NULL){
		if (de->d_name[0] != '.'){ //skip . , .. , and hidden files
			
			std::cout << "\tFound " <<  de->d_name << '\n';
			std::string index_dir = blog_dir_str;
			index_dir += "/";
			index_dir += de->d_name;
			index_dir += "/index.sb";

			blogs[i].setSB(index_dir.c_str());		
			blog_count++;
			i++;
		}
	}
	return 1;

}


int parseBlogs(){



	for (int i = 0; i < blog_count; i++){
		FILE *blog_file = fopen(blogs[i].getSB(), "r");
		if (blog_file == NULL) {
			std::cout << "couldn't open " << blogs[i].getSB() << '\n';
			return 0;
		}
		parseBlog(blog_file, i);
		fclose(blog_file);
	}

	return 1;
}









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
	std::cout << "\t[Parsing Blog Entry " << blog_index << "]\n";

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
