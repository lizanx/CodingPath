function Calculator() {
    this.operations = {
        "+": (a, b) => a + b,
        "-": (a, b) => a - b,
    };
    this.calculate = function (expression) {
        let tokens = expression.split(" ");
        console.assert(tokens.length === 3, "Invalid expression");
        let operand1 = parseInt(tokens[0]);
        let operator = tokens[1];
        let operand2 = parseInt(tokens[2]);
        if (operator in this.operations) {
            return this.operations[operator](operand1, operand2);
        } else {
            throw new Error(`Unknown operator ${operator}`);
        }
    };
    this.addMethod = function (operator, func) {
        if (!(operator in this.operations)) {
            this.operations[operator] = func;
        }
    };
}

let calc = new Calculator;
console.log(calc.calculate("3 + 7")); // 10

let powerCalc = new Calculator;
powerCalc.addMethod("*", (a, b) => a * b);
powerCalc.addMethod("/", (a, b) => a / b);
powerCalc.addMethod("**", (a, b) => a ** b);
let result = powerCalc.calculate("2 ** 3");
console.log(result); // 8
result = powerCalc.calculate("2 * 3");
console.log(result); // 6
result = powerCalc.calculate("12 / 3");
console.log(result); // 4
