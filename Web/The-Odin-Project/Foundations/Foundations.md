# The Odin Project - Foundations Course
## Asking For Help
### Describe the “XY Problem”
Someone wants to solve problem X and thinks that he/she can solve it through method Y.  
Thus as long as problem Y is solved, problem X is solved.  
Then he/she asks about problem Y which probably won't solve problem X at all but only to confuse helpers.  
He/She should always offer the background of the problem and clearly state the problem he/she actually wants to solve.

### Name the 5 things your question should include
1. The link to the chapter you're reading.
2. The problem you want to solve and difficulties you meet.
3. The link to source code repo or online editor.
4. The expected results and actual results.
5. The methods you've tried.
6. The development setup/environment.

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
6. Spare enough time for the answering.

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
Data sent/received via internet are split into small packets for transmission and combined together at destination.

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

## Intro to CSS
### What is the syntax for class and ID selectors?
- class selector: `.[class]`
- id selector: `#[id]`

### How would you apply a single rule to two different selectors?
Use grouping selectors:
```css
.class-1,
.class-2
{
    /* properties here */
}
```

### Given an element that has an id of title and a class of primary, how would you use both attributes for a single rule?
`#title, .primary {}`

### What does the descendant combinator do?
It matches a certain child whose parent/ancestor must match preceding requirements.

### What are the names of the three ways to add CSS to HTML?
1. External link
2. Embedded in HTML
3. Inline in HTML element

### What are the main differences between the three ways of adding CSS to HTML?
External link offers good separation and better universality.  
Embedded styles can be file-scope only thus won't affect styles of other HTML.  
Inline styles apply to a certain unique element but may cause maintainability and readability issue if used too much.

## The Cascade
### Between a rule that uses one class selector and a rule that uses three type selectors, which rule has the higher specificity?
Class selector.

## Inspecting HTML and CSS
### How do you select a specific element on your page with your browser’s developer tools?
Select the element, right click and select "inspect" in menu.

### What does a strike-through in a CSS declaration mean in your browser’s developer tools?
The overridden CSS.

### How do you change CSS in real time on specific elements of a web page with your browser’s developer tools?
When inspecting an element, edit its style in style editor window.

## The Box Model
### From inside to outside, what is the order of box-model properties?
padding/border/margin

### What does the box-sizing CSS property do?
It defines whether the size of the box is affected only by its width/height or dependent on padding/border too.

### What is the difference between the standard and alternative box model?
- Standard box model: height/width is for the content, any padding/border will add extra space.
- Alternative box model: height/width is for the whole box, not the content.

### Would you use margin or padding to create more space between 2 elements?
Margin.

### Would you use margin or padding to create more space between the contents of an element and its border?
Padding.

### Would you use margin or padding if you wanted two elements to overlap each other?
Margin.

### How do you set the alternative box model for all of your elements?
```css
html {
    box-sizing: border-box;
}
```

### How do you center an element horizontally?
Set its left and right margin to `auto`.

## Block and Inline
### What is the difference between a block element and an inline element?
A block element will start a new line and stretch to its parent's width.  
An inline element is adjacent to its neighbors in the same line.

### What is the difference between an inline element and an inline-block element?
Width/height properties of inline element won't take effect, and extra padding/border may overlap lines above or below the element.  
Width/height properties of inline-block element take effect, and extra padding/border will not overlap other elements.

### Is an h1 block or inline?
Block.

### Is button block or inline?
Inline.

### Is div block or inline?
Block.

### Is span block or inline?
Inline.

## Introduction to Flexbox
### What’s the difference between a flex container and a flex item?
A flex container is an element with property `display: flex`, while a flex item is a direct child of flex container.

### How do you create a flex item?
Add this property: `display: flex`.

## Growing and Shrinking
### What are the 3 values defined in the shorthand flex property (e.g. flex: 1 1 auto)?
`flex-grow` `flex-shrink` `flex-basis`

### What are the 3 defined values for the flex shorthand flex:auto?
`flex-grow: 1; flex-shrink: 1; flex-basis: auto`

## Axes
### How do you make flex items arrange themselves vertically instead of horizontally?
`flex-direction: column;`

### In a column flex-container, what does flex-basis refer to?
`height`

### In a row flex-container, what does flex-basis refer to?
`width`

### Why do the previous two questions have different answers?
Because `flex-basis` always refer to the main axis which is horizontal for `row` while vertical for `column`.

## Alignment
### What is the difference between justify-content and align-items?
The former is along the main axis while the latter is along the cross axis.

### How do you use flexbox to completely center a div inside a flex container?
```css
.flex-container{
    display: flex;
    justify-content: center;
    align-items: center;
}
```

### What’s the difference between justify-content: space-between and justify-content: space-around?
The former only cares about space between two items, while the latter cares about the space against the container edge as well.

## Variables and Operators
### Name the three ways to declare a variable
```js
let a;
const b;
var c;
```

### Which of the three variable declarations should you avoid and why?
`var`, because vars declared this way has scope issues and redefinition issues.

### What rules should you follow when naming variables?
Use camel-case in general and make the name meaningful.

### What happens when you add numbers and strings together?
The numbers are converted to strings automatically and "add" becomes concatenation.

### How does the Modulo (%), or Remainder, operator work?
It returns the remainder.

### Explain the difference between == and ===.
`==` only compares values and ignores types, while `===` compared both types and values.

### When would you receive a NaN result?
When some value cannot be correctly converted to a number.

### How do you increment and decrement a number?
Prefix or postfix `++`/`--`

### Explain the difference between prefixing and postfixing increment/decrement operators.
Prefixing returns the number after increment/decrement, while postfixing return the number before increment/decrement.

### What is operator precedence and how is it handled in JS?
Different math operators have different priorities, operations with higher priorities are executed before lower ones.  
For operations that have the same priorities, the execution order is left-to-right.

### How do you access developer tools and the console?
Press `F12` shortcut.

### How do you log information to the console?
`console.log`

### What does unary plus operator do to string representations of integers? eg. +”10”
Same as `Number("10")`, it converts the string to a number.

## Data Types and Conditionals
### What are the eight data types in JavaScript?
- string
- number
- bigint
- boolean
- null
- undefined
- object
- symbol

### Which data type is NOT primitive?
object

### What is the relationship between null and undefined?
- `null`: nothing, value unknown
- `undefined`: value not assigned

### What is the difference between single, double, and backtick quotes for strings?
Single quotes and double quotes are barely the same,  
while backtick quotes strings can contain string interpolation and multiple lines.

### What is the term for joining strings together?
Concatenation.

### Which type of quote lets you embed variables/expressions in a string?
Backtick quotes.

### How do you embed variables/expressions in a string?
```js
`${Expression}`
```

### How do you use escape characters in a string?
`"\n"`

### What is the difference between the slice/substring/substr string methods?
`slice` and `substring` accept start index and end index as parameters,  
while `substr` accepts start index and length as parameters.  
`slice` can accept negative indexes which means counting from end,  
while `substring` doesn't support negative indexes.

### What are the three logical operators, and what do they stand for?
`&&` - and, `||` - or, `!` - not.

### What are the comparison operators?
`== > < >= <= ===`

### What are truthy and falsy values?
- falsy values: `null` `undefined` `false` `0` `""`
- truthy values: all values other than falsy values

### What are the falsy values in JavaScript?
`null` `undefined` `false` `0` `""`

### What are conditionals?
Decisions to determine the code flow.

### What is the syntax for an if/else conditional?
```js
if (condition) {
    // statements
} else {
    // statements
}
```

### What is the syntax for a switch statement?
```js
switch (variable) {
    case condition:
        // statement
        break;
    // case ...
    default:
        // statement
}
```

### What is the syntax for a ternary operator?
`(condition) ? action-when-tue : action-when-false`

### What is nesting?
A language structure for control flow can be nested in another one.

## JavaScript Developer Tools
### How do you open developer tools?
- Right click and select "Inspect".
- Press shortcut key `F12`.

### How do you change screen size of a website using developer tools?
Go to the device panel and enter sizes or drag and drop the displayed screen.

### What is a breakpoint?
It's a debugging method which pauses the execution of codes at a certain point or when certain conditions are met.

### How do you set a breakpoint?
- Click the line number of code.
- Call `debug(funcName)` in code.
- Use other options in dev-tools panel like event breakpoints.

## Function Basics
### What are functions useful for?
To define a certain action and reuse code blocks.

### How do you invoke a function?
`funcName(parameters...)`

### What are anonymous functions?
Functions that are defined without a name, which can only be assigned to a variable or passed as arguments.

### What is function scope?
A function has its only scope starting from `{` and ending at `}`, the scope may influence variable definitions and references.

### What are return values?
Values returned from a function, namely after some actions the function can return a value.

### What are arrow functions?
A simplified way to define function expressions: `(params...) => { /* code blocks */ }`

## Problem Solving
### What are the three stages in the problem solving process?
1. Understand the problem
2. Plan the solution
3. Divide the big problem into smaller ones and solve them one by one

### Why is it important to clearly understand the problem first?
If you don't truly understand a problem, you can't go in the right direction to solving it.

### What can you do to help get a clearer understanding of the problem?
Explain it in simple English by writing it down, speaking to someone else or a rubber duck.

### What are some of the things you should do in the planning stage of the problem solving process?
- Define initial inputs and final outputs
- Divide the big problem into small ones
- Write pseudocode if possible

### What is an algorithm?
It's just a group of steps to solve a particular problem.

### What is pseudocode?
It's a programming language independent representation of logical steps.

### What are the advantages of breaking a problem down and solving the smaller problems?
- Smaller problems are easier to understand and solve.
- Solve one small problem will probably make solving another one easy.
- Solution to each small problem will help determine if you're on the right way.

## Understanding Errors
### What are three reasons why you may see a TypeError?
- Modify a variable which is unchangeable
- Use a value in an inappropriate way
- An operand or parameter passed to a function is incompatible with the expected type

### What is the key difference between an error and a warning?
An error will terminate the execution of the program unless you explicitly catch it,  
while a warning only offers warning information about potential errors without terminating the execution.

### What is one method you can use to resolve an error?
```js
try {
    // something may cause error
}
catch (e) {
    // handle the error
}
```

## Clean Code
### Why is it important to write clean code?
Because it's more readable for later readers(including yourself),  which improves maintainability.

### Name 5 clean code principles previously mentioned
- Revise idea before coding
- Expose the structure of codes clearly
- Write meaningful and clear comments
- Use a good convention to name variables/functions
- Don't write very large functions

### What is the difference between good comments and bad comments?
Good comments explains what the code does and why,  
while bad comments only clutter the codes without useful information.

## Arrays and Loops
### What is an array?
An array is a sequence of values where each one has an index starting from 0.

### What are arrays useful for?
For a collection of data.

### How do you access an array element?
`arr[index]` or `arr.at(index)`

### How do you change an array element?
`arr[index] = value;`

### What are some useful array properties?
- `arr.length` returns the length of the array

### What are some useful array methods?
- `arr.slice()` returns a new array containing the requested elements
- `arr.forEach()` executes certain operation on each element

### What are loops useful for?
For executing certain operations repeatedly until the condition is broken.

### What is the break statement?
It stops the execution of the inner most loop immediately.

### What is the continue statement?
It skips the rest of loop for this round and immediately jumps to next round.

### What is the advantage of writing automated tests?
It simplifies verification process and help you make the logic of solution more clear.
