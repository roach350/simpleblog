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
- top x newest blog html generator
- code formatting
- link embedding
- proper linking
- auto index generation based on headings


### File Structure
Here is an example file structure:
```
website_dir/
	index.html
	manifest.sb
	contents/
		blog/
			blog_entry/
				index.html
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
1. Create a directory for your blog and run the init command. That will create a file structure for your blog. 
2. Copy the manifest.sb file from the template to your blog and edit it to your needs.
3. Create folders under dir/content/blog, each folder will contain a blog entry.
4. Copy the index.sb from the template and edit it, this file defines your blog entry.
5. Run the compile command to write the HTML files. (NOTE: a lot of functionality is missing at the moment, e.g proper HTML linking)
### index.sb formatting
Variable definitions are terminated with the ';' character.<br>
Between the '`' characters is the main content of the entry. Here are some syntax guidelines:
- '#' declares a header, similar to markdown
- '$' declares an image, links to images in the same directory, e.g. "$picture_preview.jpg,full_size_hyperlinked_img.jpg,alt_text;"
- '^' declares a code snipped, not implemented yet
```
simpleblog init <dir>
simpleblog compile <dir>
```
