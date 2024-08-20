const add = function (a, b) {
  return a + b;
};

const subtract = function (a, b) {
  return a - b;
};

const sum = function (arr) {
  return arr.reduce(add, 0);
};

const multiply = function (arr) {
  return arr.reduce((a, b) => a * b, 1);
};

const power = function (a, b) {
  return a ** b;
};

const factorial = function (num) {
  let result = 1;
  for (let i = 2; i <= num; i++) {
    result *= i;
  }
  return result;
};

// Do not edit below this line
module.exports = {
  add,
  subtract,
  sum,
  multiply,
  power,
  factorial
};
