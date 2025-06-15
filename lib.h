void initStr(char *str, int len){
	/* initiate a string with a series of null terminators */
	for (int i = 0; i < len; i++){
		str[i] = 0;
	}
}


int countNonZero(char *str, int len){
	int count = 0;
	for (int i = 0; i < len; i++){
		if (str[i] > 0){
			count++;
		}
	}
	return count;
	
}


void appendStr(char *base, const char *addition, int index){

	int len = strlen(addition); //length of string to add
	int end = len + index; //where to end
	// end - index = where to end - where to start 


	int increment = 0;
	// add comma
	if (index > 0){
		base[index] = ',';
		increment = 1;
	}
	for (int i = 0; i < (end - index); i++){
		base[index + i + increment] = addition[i];
	}

}

int countChar(char *str, int key){
	//checks if single char. key is in str
	int count = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++){
		if (str[i] == key){

			count++;
		}
	}
	return count;

}

