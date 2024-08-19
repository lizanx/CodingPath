let container = document.querySelector(".container");
for (let row of createGrid(16)) {
    container.appendChild(row);
}
addHoverEffects(".element");

let btn = document.querySelector("button");
btn.addEventListener('click', function () {
    try {
        let size = parseInt(prompt("Enter the size of the grid(1~100): "));
        container.replaceChildren();
        for (let row of createGrid(size)) {
            container.appendChild(row);
        }
        addHoverEffects(".element");
    } catch (e) {
        alert("Your input is not a valid size!");
    }
});

function addHoverEffects(selector) {
    document.querySelectorAll(selector).forEach((element) => {
        element.addEventListener("mouseover", () => element.style.backgroundColor = generateRandomColor());
        element.addEventListener("mouseout", () => element.style.backgroundColor = '');
    });
}

function createGrid(size) {
    if (size <= 0 || size > 100) {
        throw new RangeError('Size out of range: (0, 100]');
    }

    let rows = [];

    for (let i = 0; i < size; i++) {
        let row = document.createElement("div");
        row.style.display = "flex";
        row.style.justifyContent = "center";
        // row.style.gap = "5px";
        row.style.flex = "1 1 auto";
        row.classList.add("row");
        for (let j = 0; j < size; j++) {
            let element = document.createElement("div");
            element.classList.add("element");
            element.style.flex = "1 1 auto";
            element.style.border = "1px solid black";
            row.appendChild(element);
        }
        rows.push(row);
    }

    return rows;
}

function generateRandomColor() {
    let randomValue = Math.floor(Math.random() * 0xFFFFFF);
    let randomColor = randomValue.toString(16);
    return `#${randomColor.padStart(6, "0")}`;
}