const removeFromArray = function (arr, ...excludes) {
    let newArray = [];
    for (let i = 0; i < arr.length; i++) {
        let isExcluded = false;
        for (const exclude of excludes) {
            if (arr[i] === exclude) {
                isExcluded = true;
                break;
            }
        }
        if (!isExcluded) {
            newArray.push(arr[i]);
        }
    }

    return newArray;
};

// Do not edit below this line
module.exports = removeFromArray;
