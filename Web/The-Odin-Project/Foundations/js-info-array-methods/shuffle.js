function shuffle(arr) {
    arr.sort((a, b) => Math.random() - Math.random());
}

let arr = [1, 2, 3];

for (let i = 0; i < 10; i++) {
    shuffle(arr);
    console.log(arr);
}
