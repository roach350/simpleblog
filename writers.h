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


