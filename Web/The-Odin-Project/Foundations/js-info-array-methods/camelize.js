function camelize(str) {
    return str.split("-")
        .map((item, index) => (index > 0) ? (item[0].toUpperCase() + item.slice(1)) : item)
        .filter((item) => item.trim().length > 0)
        .join('');
}

console.assert(camelize("background-color") == 'backgroundColor', "Failed");
console.assert(camelize("list-style-image") == 'listStyleImage', "Failed");
console.assert(camelize("-webkit-transition") == 'WebkitTransition', "Failed");
