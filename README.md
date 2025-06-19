# SimpleBlog
A minimal blog compiler written in C++
## NOTE
This project is in a semi functional state as it is in heavy development
## Overview
SimpleBlog takes a series of simple text files and turns them into a static HTML blog.<br>
It is up to you for how you want host it.
### Features
- code formating
- simple syntax
- minimal dependencies
- fast (written in C++)

### File Structure
Here is an example file structure:
```
website_dir/
	index.html
	manifest.sb
	contents/
		blog/
			index.sb
			assets/
				pic.png
		extra/
			about.sb
			home.sb
			download.sb
			assets/
				pic.jpg
	web/
		pages/
			blog.html
			downloads.html
			about.html
		lib/
			main.css
			main.js
```			
## Compilation 
```
chmod +x build.sh
./build.sh

```
A makefile will likely be introduced as the project matures.
### Dependencies
- standard C/C++ libraries (stdio, stdlib, string, iostream, etc.)
- sys/types.h
- sys/stat.h
- unistd.h

## Usage
```
simpleblog init <dir>
simpleblog compile <dir>
```
