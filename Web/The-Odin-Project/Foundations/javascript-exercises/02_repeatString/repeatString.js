const repeatString = function (str, count) {
    if (count < 0) {
        return "ERROR";
    }

    let repeatedStr = "";
    for (let i = 0; i < count; i++) {
        repeatedStr += str;
    }
    return repeatedStr;
};

// Do not edit below this line
module.exports = repeatString;
