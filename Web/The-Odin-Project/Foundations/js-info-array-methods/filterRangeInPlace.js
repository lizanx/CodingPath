function filterRangeInPlace(arr, min, max) {
    let filteredArr = arr.filter(item => item >= min && item <= max);
    arr.splice(0, arr.length);
    arr.push(...filteredArr);
}

let arr = [5, 3, 8, 1];

filterRangeInPlace(arr, 1, 4); // 删除了范围在 1 到 4 之外的所有值

console.log(arr); // [3, 1]
