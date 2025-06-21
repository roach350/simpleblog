# SimpleBlog
A minimal blog compiler written in C++
## NOTE
This project is in a semi functional state as it is in heavy development
## Overview
SimpleBlog takes a series of simple text files and turns them into a static HTML blog.<br>
It is up to you for how you want host it.
### Features
- code formating
- auto image size handling
- simple syntax
- minimal dependencies
- fast (written in C++)

### TODO
SimpleBlog is a work in progress at the moment, this is a list of core functionality that needs to be implemented before it is useable:
- index.sb parser for blog posts and other pages
- blog index html generator
- top x newest blog html generator
- per blog page html generator

### File Structure
Here is an example file structure:
```
website_dir/
	index.html
	manifest.sb
	contents/
		blog/
			blog_entry/
				index.sb
				assets/
					pic.png
		extra/
			blog.sb
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
