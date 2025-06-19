
/* define class for web pages */



class page_t{
	private:
		char title[64];
		char url[64];
		char html[64];
		char base_url[64];
		char css[64]; //css address
		char js[64]; //js address
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

		char *getProjectURL(){
			return base_url;

		}

		char *getHTML(){
			return html;
		}

		void setTitle(const char *t){
			strncpy(title, t, 64);
		}

		void setHTML(const char *u){
			/* set file name*/
			strncpy(html, u, 64);
			/*set URL relative index */
			std::string temp = "";
			temp += "/web/pages/";
			temp += html;
			strncpy(url, temp.c_str(), 64);
			

		}

		void setProjectURL(const char *u){
			/* set location relative to executable path */

			std::string temp = u;
			temp += "/web/pages/";
			temp += html;
			strncpy(base_url, temp.c_str(), 64);
			
		}
		
		void print(){
			std::cout << "page_t: " << title << ' ' << url << ' ' << css << ' ' << js << '\n';

		}
};




int find_page(page_t array[], const char *key){
	
	for (int i = 0; i < MAX_WEB_PAGES; i++){
		if (strncmp(array[i].getTitle(), key, 64) == 0){
			return i;
		}
		
	}

	return -1;

}
