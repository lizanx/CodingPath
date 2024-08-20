function descendingSort(arr) {
    arr.sort((a, b) => b - a);
}

let arr = [5, 2, 1, -10, 8];

// ……你的代码以降序对其进行排序
descendingSort(arr);

console.log(arr); // 8, 5, 2, 1, -10
