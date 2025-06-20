/*
	simpleblog
	helper functions for write.h

*/


void write_header(FILE *fptr){
	fprintf(fptr, "<html>\n");
	fprintf(fptr, "<!DOCTYPE html>\n");
	fprintf(fptr, "\t<head>\n");
	fprintf(fptr, "\t\t<title>%s</title>\n", BLOG_TITLE);
	fprintf(fptr, "\t\t<link rel = 'stylesheet' href = '%s'>\n", main_css); 
	fprintf(fptr, "\t<head>\n");
}


void write_nav(FILE *fptr){


	fprintf(fptr, "\t\t<hr>\n");
	fprintf(fptr, "\t\t\t<nav>\n");
	for (int i = 0; i < page_count; i++){
		fprintf(fptr, "\t\t\t\t<i><a href='%s'>%s</a></i>\n", web_pages[i].getHTML(), web_pages[i].getTitle());
	}


	fprintf(fptr, "\t\t</nav>\n");
	fprintf(fptr, "\t\t<hr>\n");


}

void write_index(FILE *fptr){
	write_header(fptr);

	fprintf(fptr, "\t<body>\n");
	fprintf(fptr, "\t\t<header>\n");
	fprintf(fptr, "\t\t\t<h1>%s</h1>\n", BLOG_TITLE);	
	fprintf(fptr, "\t\t\t<i><p>%s</p></i>\n", BLOG_SLOGAN);	
	fprintf(fptr, "\t\t</header>\n");

	write_nav(fptr);


	fprintf(fptr, "\t</body>\n");

	fprintf(fptr, "</html>\n");
}


