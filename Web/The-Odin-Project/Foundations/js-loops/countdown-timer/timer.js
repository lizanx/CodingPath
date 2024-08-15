var output = document.querySelector('.output');
output.innerHTML = '';

for (let i = 10; i >= 0; i--) {
    let para = document.createElement("p");
    para.textContent = (i === 10) ? "Countdown 10"
        : (i === 0) ? "Blast off!"
            : `${i}`;
    output.appendChild(para);
}
