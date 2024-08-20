function groupById(arr) {
    return arr.reduce((accumulator, current) => {
        accumulator[current.id] = current;
        return accumulator;
    }, {});
}

let users = [
    { id: 'john', name: "John Smith", age: 20 },
    { id: 'ann', name: "Ann Smith", age: 24 },
    { id: 'pete', name: "Pete Peterson", age: 31 },
];

let usersById = groupById(users);

/*
// 调用函数后，我们应该得到：
 
usersById = {
  john: {id: 'john', name: "John Smith", age: 20},
  ann: {id: 'ann', name: "Ann Smith", age: 24},
  pete: {id: 'pete', name: "Pete Peterson", age: 31},
}
*/
console.log(usersById);