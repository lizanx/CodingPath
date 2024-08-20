const operations = {
    ["+"]: (a, b) => a + b,
    ["-"]: (a, b) => a - b,
    ["*"]: (a, b) => a * b,
    ["/"]: (a, b) => {
        if (b === 0) {
            throw new Error("Divided by 0!");
        }
        return a / b;
    },
};
const actions = ["Calculate", "Clear", "Backspace"];

function operate(operator, operand1, operand2) {
    return operations[operator](operand1, operand2);
}

