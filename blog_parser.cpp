/* 
	SimpleBlog blog parser

*/
#include <dirent.h>
#include <bits/stdc++.h>

#include "blog.h"
#include "blog_parser.h"
#include "lib.h"


int findBlogs(const char *dir, blog_t *blog){
	std::cout << "[PARSING BLOGS]\n";
	/* setup */
	struct dirent **de;
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
	//while ((de = readdir(blog_dir)) != NULL){
	int num = scandir(blog_dir_str.c_str(), &de, NULL, alphasort);

	for (int n = 0; n < num; n++){
		if (de[n]->d_name[0] != '.'){ //skip . , .. , and hidden files
			
			std::cout << "\tFound " <<  de[n]->d_name << '\n';
			std::string index_dir = blog_dir_str;
			index_dir += "/";
			index_dir += de[n]->d_name;
			std::string html = index_dir;
			html += "/index.html";
			index_dir += "/index.sb";
			
			//set class data
			blog->blogs[i].setSB(index_dir.c_str());
			blog->blogs[i].setHTML(html.c_str());	

			//std::cout << "set html " << blogs[i].getHTML() << '\n';	
			blog->blog_count++;
			i++;
		}
		free(de[n]);
	}
	free(de);
	return 1;

}


int parseBlogs(blog_t *blog){



	for (int i = 0; i < blog->blog_count; i++){
		FILE *blog_file = fopen(blog->blogs[i].getSB(), "r");
		if (blog_file == NULL) {
			std::cout << "couldn't open " << blog->blogs[i].getSB() << '\n';
			return 0;
		}
		parseBlog(blog_file, blog, i);
		fclose(blog_file);
	}

	return 1;
}







int parseContents(FILE *blog_file, blog_t *blog, int blog_index){
	char c = 0;
	int i = 0;
	std::cout << "\tParsing contents begin\n";
	
	while((c = fgetc(blog_file)) != '`'){
		
		blog->blogs[blog_index].addChar(c, i);
		i++;

	}
	blog->blogs[blog_index].addChar(0, i); //null terminator
	std::cout << "\tParsing contents end\n";
	return 1;

}




int parseBlog(FILE *blog_file, blog_t *blog, int blog_index){
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
				parseContents(blog_file, blog, blog_index);
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
			blog->blogs[blog_index].setTitle(value);
			
		}
	
		if (strcmp(token, "author") == 0){
			blog->blogs[blog_index].setAuthor(value);
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

		blog->blogs[blog_index].setDate(m, d, y); //should be put somewhere else		


		if (strcmp(token, "summary") == 0){
	
			blog->blogs[blog_index].setSummary(value);
		}





		//reset and parse next line
		initStr(token, 32);
		initStr(value, 128);

	}



}


//sorting code is broken

bool compareDates(blog_post_t &d1, blog_post_t &d2){
    // All cases when true should be returned
	if (d1.getY() < d2.getY()){
        	return true;
	}
    	if (d1.getY() == d2.getY() && d1.getM() < d2.getM()){
        	return true;
	}
    	if (d1.getY() == d2.getY() && d1.getM() == d2.getM() && d1.getD() < d2.getD()){
        	return true;
	}
    // If none of the above cases satisfy, return false
    	return false;



} 


int sortBlogs(blog_post_t arr[], int n){
	//use built in sorting function
	std::sort(arr, arr + n, compareDates);
}
