/*
	simpleblog
	helper functions for write.h

*/
void write_contents(FILE *fptr, int blog_index);

void write_header(FILE *fptr){
	fprintf(fptr, "<html>\n");
	fprintf(fptr, "<!DOCTYPE html>\n");
	fprintf(fptr, "\t<head>\n");
	fprintf(fptr, "\t\t<title>%s</title>\n", blog_title);
	fprintf(fptr, "\t\t<link rel = 'stylesheet' href = '%s'>\n", main_css); 
	fprintf(fptr, "\t<head>\n");
}


void write_nav(FILE *fptr){


	fprintf(fptr, "\t\t<hr>\n");
	fprintf(fptr, "\t\t\t<nav>\n");
	for (int i = 0; i < page_count; i++){
		fprintf(fptr, "\t\t\t\t<a href='%s'>%s</a>\n", web_pages[i].getHTML(), web_pages[i].getTitle());
	}


	fprintf(fptr, "\t\t</nav>\n");
	fprintf(fptr, "\t\t<hr>\n");


}

void write_footer(FILE *fptr){
	fprintf(fptr, "\t\t<footer>\n");
	fprintf(fptr, "\t\t\t<p>%s</p>", blog_footer);
	fprintf(fptr, "\t\t<footer>\n");

}


void write_blog_preview(FILE *fptr, int blog_index){


	fprintf(fptr, "\t\t\t\t<article>\n");
	fprintf(fptr, "\t\t\t\t\t<a href= ''><h3>%s</h3></a>\n", blogs[blog_index].getTitle());
	fprintf(fptr, "\t\t\t\t\t<p><b>PUBLISHED </b>%i/%i/%i</p>\n", blogs[blog_index].getM(), blogs[blog_index].getD(), blogs[blog_index].getY());
	fprintf(fptr, "\t\t\t\t\t<p><b>WRITTEN BY </b>%s</p>\n", blogs[blog_index].getAuthor());
	fprintf(fptr, "\t\t\t\t\t<p>%s</p>\n", blogs[blog_index].getSummary());
	fprintf(fptr, "\t\t\t\t</article>\n");

}




void write_n_blog_preview(FILE *fptr, int n){

	
	fprintf(fptr, "\t\t\t<main>\n");
	for (int i = 0; i < n; i++){

		write_blog_preview(fptr, i);
	}

	fprintf(fptr, "\t\t\t</main>\n");

}


void write_heading(FILE *fptr, char *string, int heading){

	fprintf(fptr, "\t\t<h1>%s</h1>\n", string);
	


}

void write_code_sec(FILE *fptr, int blog_index, int start, int end){


}

void write_paragraph(FILE *fptr, char *string){

	fprintf(fptr, "\t\t<p>%s</p>\n", string);
	//fprintf(fptr, "\t\t<br>\n");
}

void write_pic(FILE *fptr, char *pic, char *pic_fs, char *pic_alt){

	fprintf(fptr, "\t\t<a href='%s' ><img src='%s' alt='%s'></a> \n", pic_fs, pic, pic_alt);
	fprintf(fptr, "\t\t<p>%s</p>\n", pic_alt);
	fprintf(fptr, "\t\t<br>\n");
}


void write_index(FILE *fptr){
	write_header(fptr);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", blog_title);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", blog_slogan);	
	fprintf(fptr, "\t\t</header>\n");


	write_nav(fptr);

	
	fprintf(fptr, "\t\t<h2>Latest News</h2>\n");
	write_n_blog_preview(fptr, 3);


	
	write_footer(fptr);
	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");
}


void write_blog(FILE *fptr, int blog_index){
	write_header(fptr);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", blog_title);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", blog_slogan);	
	fprintf(fptr, "\t\t</header>\n");




	write_nav(fptr);
	fprintf(fptr, "\t\t<h2>%s</h2>\n", blogs[blog_index].getTitle());	
	fprintf(fptr, "\t\t<p><b>PUBLISHED </b>%i/%i/%i</p>\n", blogs[blog_index].getM(), blogs[blog_index].getD(), blogs[blog_index].getY());
	fprintf(fptr, "\t\t<p><b>WRITTEN BY </b>%s</p>\n", blogs[blog_index].getAuthor());

	write_contents(fptr, blog_index);

	write_footer(fptr);
	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");

}


void write_contents(FILE *fptr, int blog_index){
	int i = 0;

	/*temp vars */
	int heading = 0; char heading_str[128];
	int code_start = 0; int code_end = 0;
	char pic[64]; char pic_fs[64]; char pic_alt[64];
	initStr(pic, 64); initStr(pic_fs, 64);
	char paragraph[1024];
	initStr(paragraph, 1024);
	int end = 0; //used for checking if at end of content
	/* parse and write contents of blog entry */

	while (i < BLOG_CONTENT_SIZE && end != 1){
		while (i != '\n'){
			//should use switch
			/* begin parsing line */
			if (blogs[blog_index].getChar(i) == '#'){

				//parse headings

				while (blogs[blog_index].getChar(i) == '#'){	
					heading++;
					i++;
				}

				initStr(heading_str, 128);
				int j = 0;
				while (blogs[blog_index].getChar(i) != '\n'){
					heading_str[j] = blogs[blog_index].getChar(i);
					i++; j++;
				}
				heading_str[j] = 0;

				//write heading and new line
				
				std::cout << "write heading\n";
				write_heading(fptr, heading_str, heading);
				heading = 0;
			}


			if (blogs[blog_index].getChar(i) == '^'){
				//begin code section
				code_start = i;
				while (blogs[blog_index].getChar(i) != '^'){
					i++;
				}
				code_end = i;

				//write code section with code_end and code_i
				std::cout << "write code section\n";
			}

	
			if (blogs[blog_index].getChar(i) == '$'){
				/*
				picture
				ex:
					$pic_prev.jpg,pic_fs.jpg;
				*/
				int j = 0;
				i++; //advance
				initStr(pic, 64); initStr(pic_fs, 64); initStr(pic_alt, 64);
				// pic
				while (blogs[blog_index].getChar(i) != ','){
					pic[j] = blogs[blog_index].getChar(i);
					i++; j++;
	
				}
				pic[j] = 0;
				j = 0;
				i++; //advance
				//fullsize pic
				while (blogs[blog_index].getChar(i) != ','){
					pic_fs[j] = blogs[blog_index].getChar(i);
					i++; j++;
	
				}
				pic_fs[j] = 0;
				j = 0;
				i++; //advance
				while (blogs[blog_index].getChar(i) != ';'){
					pic_alt[j] = blogs[blog_index].getChar(i);
					i++; j++;
	
				}
				
				pic_alt[j] = 0;

				//write pic
				std::cout << "write pic\n";
				write_pic(fptr, pic, pic_fs, pic_alt);
				
			}
			
			/* if line does not begin with special character, assume paragraph */
			if (blogs[blog_index].getChar(i) != '#' && blogs[blog_index].getChar(i) != ';' && blogs[blog_index].getChar(i) != '^' && blogs[blog_index].getChar(i) != '$' && blogs[blog_index].getChar(i) != ' ' && blogs[blog_index].getChar(i) != 0) {
				int j = 0;
				while (blogs[blog_index].getChar(i) != '\n' && blogs[blog_index].getChar(i) != 0){
					paragraph[j] = blogs[blog_index].getChar(i);
					j++;
					i++;
	
				}
				paragraph[j] = 0; //null terminate
				//write paragprah		

				std::cout << "write parapgraph\n";	

				write_paragraph(fptr, paragraph);
			}
			if (blogs[blog_index].getChar(i) == 0){
				end = 1;
				break;
			}
		
			i++;

		}
		// new line



	}



	




}
