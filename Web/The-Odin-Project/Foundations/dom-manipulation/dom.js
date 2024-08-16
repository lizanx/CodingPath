const container = document.querySelector("#container");

const content = document.createElement("div");
content.classList.add("content");
content.textContent = "This is the glorious text-content!";
container.appendChild(content);

const para = document.createElement("p");
para.textContent = "Hey I'm red!";
para.style.color = "red";
container.appendChild(para);

const header3 = document.createElement("h3");
header3.textContent = "I'm a blue h3!";
header3.style.color = "blue";
container.appendChild(header3);

const anotherContainer = document.createElement("div");
anotherContainer.style.border.color = "black";
anotherContainer.style.backgroundColor = "pink";

const header1 = document.createElement("h1");
header1.textContent = "I'm in a div";
anotherContainer.appendChild(header1);

const anotherPara = document.createElement("p");
anotherPara.textContent = "ME TOO!";
anotherContainer.appendChild(anotherPara);

container.appendChild(anotherContainer);
