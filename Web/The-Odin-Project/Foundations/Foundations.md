# The Odin Project - Foundations Course
## Asking For Help
### Describe the “XY Problem”
Someone wants to solve problem X and thinks that he/she can solve it through method Y.  
Thus as long as problem Y is solved, problem X is solved.  
Then he/she asks about problem Y which probably won't solve problem X at all but only to confuse helpers.  
He/She should always offer the background of the problem and clearly state the problem he/she actually wants to solve.

### Name the 5 things your question should include
1. The link to the chapter you're reading.
2. The problem you want to solve and diffculties you meet.
3. The link to source code repo or online editor.
4. The expected results and actual results.
5. The methods you've tried.
6. The devolopment setup/environment.

## Join the Odin Community
### How do you join The Odin Project’s Discord server?
Find the link on the website and get invited.

### What makes a good question that’s easier for others to help with?
1. Offer initial intents and contexts.
2. Ask questions directly instead of AskToAsk.
3. Try to tackle it by yourself first, and show what you've done.
4. Offer complete codes in GitHub/Replit if needed.
5. Declare your knowledge level and what you expect to get for output.

### How can you more effectively help others with their coding problems?
1. Instruct them to find the solutions themselves prior to answering directly.
2. Be patient.
3. Understand that different people have different knowledge level.
4. Only answer it if you know how to solve it.
5. Admit it if you're not sure about the answer as it goes deeper.
6. Spare enought time for the answering.

## Computer Basics
### Is Windows an operating system or an application?
OS.

### What’s the difference between open source and closed source software?
Open source softwares give everyone full access to their source codes while closed source softwares don't.

### What are some use cases of a screenshot?
Record the output or code for clarification.

### Give an example of a weak and a strong password.
- Weak: `123456`
- String: `Hello@329!nice`

## How Does the Web Work?
### What is a web server?
Some computing hardware which stores resources and responds to internet requests.

### What is a network?
A mechanism to connect multiple computers to form a net, which makes each computer can communicate with another one.

### What is the internet?
A widely used infrastructure built upon network, with standard protocols for communication like IP/TCP.

### What is an IP address?
An address of a device which is connected to internet, used to identify source/destination during communication.

### What is a router?
Arrange a set of computing devices and make them accessible to each other as well as outside network.  
It's used to reduce complexities and loads of the internet.

### What is an ISP?
The service provider which really connects the global internet, and offers internet access to users.

### What are packets and how are they used to transfer data?
Packets are packages of data with additional information for transmission.  
Data sent/received via internet are splitted into small packets for transmission and combined together at destination.

### What is a client?
A device which requests certain resources from the internet.

### What is a server?
A device which accepts requests and responds with requested resources.

### What is a web page?
A document which can be displayed by web browser and include certain information for users.

### What is a web browser?
A computer program for browsing websites.

### What is a search engine?
An indexing service for looking up a certain website or other information.

### What is a DNS request?
A request which tries to get the IP address of a domain name.

### Which browser are you currently using?
Firefox/Safari.

### In your own words, describe the process that takes place when you initiate a search on google.com in terms of what we discussed.
1. Open a browser program on computer.
2. Type in `www.google.com`, and browser searches for local DNS cache for IP address.
3. If there's no such cache, the browser will send DNS requests to acquire the IP address.
4. With the IP address, browser sends HTTP requests with information about your search to the Google websites server.
5. Google server receives the request and responds with results generated from its internal searching logic.
6. Browser receives the response, parses it, and displays it on the screen.

## Installations
### What operating systems does The Odin Project support?
Linux(especially official Ubuntu)/MacOS

### What browser does The Odin Project support?
Chrome

## Command Line Basics
### What is the command line?
Command line is an interactive mechanism for user to communicate with computer via commands.

### How do you open the command line on your computer?
Open terminal.

### How can you navigate to a particular directory?
`cd [Dir]`

### Where will cd on its own navigate you to?
Home directory, usually user's home directory.

### Where will cd .. navigate you to?
The parent directory.

### How do you display the name of the directory you are currently in?
`pwd`

### How do you display the contents of the directory you are currently in?
`ls`

### How do you create a new directory?
`mkdir [Dir]`

### How do you create a new file?
`touch [File]`

### How do you destroy a directory or file?
`rm [File]` / `rmdir [Dir]`

### How do you rename a directory or file?
`mv [Src] [Dst]`

## Introduction to Git
### What kind of program is Git?
A distributed version control program.

### What are the differences between Git and a text editor in terms of what they save and their record keeping?
Text editor saves the file into the file itself on filesystem, while git saves the file into its internal storage.  
Text editor won't save any editing history, while git saves all commit histories with jumping to any version easily.

### Does Git work at a local or remote level?
Local level, everyone using git has a local copy of the repo.  
But there can be a remote centralized repo for sharing.

### Does GitHub work at a local or remote level?
Remote level.

### Why is Git useful for developers?
Because it offers version control in an effective, fast and easy manner.

### Why are Git and GitHub useful for a team of developers?
Together they benefit team collaboration as well data security.

## Git Basics
### How do you create a new repository on GitHub?
Find the "Create a repo" button on GitHub website.

### How do you copy a repository onto your local machine from GitHub?
`git clone [address]`

### What is the default name of your remote connection?
origin

### Explain what origin is in git push origin main.
The name of the remote repo.

### Explain what main is in git push origin main.
The branch you'd like to push into in the remote repo.

### Explain the two-stage system that Git uses to save files.
`git add [Files]` + `git commit -m "[Commit Message]`

### How do you check the status of your current repository?
`git status`

### How do you add files to the staging area in Git?
`git add [Files]`

### How do you commit the files in the staging area and add a descriptive message?
`git commit -m [Commit Message]`

### How do you push your changes to your repository on GitHub?
`git push origin main`

### How do you look at the history of your previous commits?
`git log`

## Introduction to HTML and CSS
### What do HTML and CSS stand for?
Hyper-text Markup Language. Cascading Style Sheets.

### Between HTML and CSS, which would you use for putting paragraphs of text on a webpage?
HTML

### Between HTML and CSS, which would you use for changing the font and background color of a button?
CSS

### What is the difference between HTML, CSS and JavaScript?
- HTML: contents and structures of a web page
- CSS: styles of the looking
- JavaScript: interactivity and many other stuff

## Elements and Tags
### What is an HTML tag?
A representation of start/end of an HTML element.

### What are the three parts of an HTML element?
- Opening tag
- Content
- Closing tag

## HTML Boilerplate
### What is the purpose of the doctype declaration?
To declare the version of HTML used.

### What is the HTML element?
An element is part of a web page which has its own contents and attributes.

### What is the purpose of the head element?
To declare non-display meta-info about the page, like charset/description/title...

### What is the purpose of the body element?
The actual contents to be displayed.

## Working with Text
### How do you create a paragraph in HTML?
`<p>Content</p>`

### How do you create a heading in HTML?
`<h1>Heading</h1>`  
From h1 to h6.

### How many different levels of headings are there and what is the difference between them?
6 levels, each level differs in size.

### What element should you use to make text bold and important?
`<strong>Content</strong>`

### What element should you use to make text italicized to add emphasis to it?
`<em>Content</em>`

### What relationship does an element have with any nested elements within it?
Parent/Children

### What relationship do two elements have if they are at the same level of nesting?
Siblings

### How do you create HTML comments?
`<!-- -->`

## Lists
### What HTML element is used to create an unordered list?
`<ul></ul>`

### What HTML element is used to create an ordered list?
`<ol></ol>`

### What HTML element is used to create list items within both unordered and ordered lists?
`<li></li>`

## Links and Images
### What element is used to create a link?
`<a href="">Content</a>`

### What is an attribute?
It offers additional information about an HTML element.

### What attribute tells links where to go to?
`href`

### What security considerations must be taken if you wish to use the target attribute to open links in a new tab/window?
`<a href="" target="_blank" rel="noopener noreferrer">Content</a>`

### What is the difference between an absolute and relative link?
- Absolute link: `[Protocol]://[Domain]/[Path]`
- Relative link: `[RelativePath]`

### Which element is used to display an image?
`<img>`

### What two attributes do images always need to have?
`alt` and `src`

### How do you access a parent directory in a filepath?
`..`

### What are the four main image formats that you can use for images on the web?
- JPG
- PNG
- GIF
- SVG

## Commit Messages
### What are two benefits of having well-written commit messages and a good commit history?
- Show to potential employer that you're a good collaborator.
- Provide great info for your coworkers or your future self.

### How many characters should the subject line of your commit message be?
72.

