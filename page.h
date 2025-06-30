
/* define class for web pages */



class page_t{
	private:
		char title[64];
		char url[64];
		char html[64]; //
		char css[64]; //css address
		char js[64]; //js address
		char sb[64]; // markup file location
	public:
		page_t(const char *t, const char *u){
			strncpy(title, t, 64);
			strncpy(url, u, 64);
		}
		page_t(){
			
		}

		char* getTitle(){
			return title;
		}
		char *getURL(){

			/* return URL relative to index*/
			return url;
		}

		char *getHTML(){
			return html;
		}

		void setTitle(const char *t){
			strncpy(title, t, 64);
		}

		void setHTML(const char *u){
			strncpy(html, u, 64);
			

		}

		void setURL(const char *u){
			/* set location relative to executable path */

			std::string temp = u;
			temp += html;
			strncpy(url, temp.c_str(), 64);
			
		}
		
		void setSB(const char *url){
			strncpy(sb, url, 64);
		}

		char *getSB(){
			return sb;
		}
		
		void print(){
			/* for debugging */
			std::cout << "page_t: " << title << ' ' << url << ' ' << css << ' ' << js << '\n';

		}
};




int find_page(page_t array[], const char *key){
	
	for (int i = 0; i < PAGES_MAX; i++){
		if (strncmp(array[i].getTitle(), key, 64) == 0){
			return i;
		}
		
	}

	return -1;

}
