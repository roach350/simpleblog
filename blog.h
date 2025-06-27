/* 
	blog entry class and helper code


*/


class blog_post_t{

	private:
		char title[64];
		char author[64];
		char summary[128];
		int month, day, year;
		char html[64];
		char sb[64];
		char *contents;

	public:

		blog_post_t(){

			contents = new char[BLOG_CONTENT_SIZE];
		}

		~blog_post_t(){

			delete contents;
		}
	
		/* the setters */
		void setTitle(const char *t){
			strncpy(title, t, 64);
		}
	
		void setAuthor(const char *a){

			strncpy(author, a, 64);
		}	
		void setSummary(const char *s){
			strncpy(summary, s, 128);

		} 


		void setDate(int m, int d, int y){
			month = m;
			day = d;
			year = y;
		}

		void setHTML(const char *h){
			strncpy(html, h, 64);
		}

		void setSB(const char *s){
			strncpy(sb, s, 64);
		}

		void addChar(char c, int i){
			//for feeding individual characters to content buffer
			contents[i] = c;

		}

		/* the getters*/


		char *getTitle(){
			return title;
		}

		int getM(){
			return month;
		}

		int getD(){

			return day;
		}

		int getY(){
			return year;
		}

		char *getSummary(){
			return summary;

		}

		char *getAuthor(){

			return author;
		}

		char *getSB(){
			return sb;
		}


		char *getHTML(){
			return html;
		}

		char getChar(int i){
			return contents[i];
		}		
		char *getContents(){
			return contents;
		}

};



