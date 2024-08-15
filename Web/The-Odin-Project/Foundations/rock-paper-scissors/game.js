let choices = ["ROCK", "PAPER", "SCISSORS"];
let humanScore = 0;
let computerScore = 0;

function getComputerChoice() {
    return choices[Math.floor(Math.random() * choices.length)]
}

function getHumanChoice() {
    let input = prompt("Enter your choice: ", "rock");
    input = input.toUpperCase();
    while (!choices.includes(input)) {
        alert("Your input is not a valid one! Please choose from rock/paper/scissors");
        input = prompt("Enter your choice: ", "rock");
    }
    return input;
}


function playGame() {
    for (let i = 0; i < 5; i++) {
        playRound(getHumanChoice(), getComputerChoice());
    }

    if (humanScore === computerScore) {
        alert("Tie!");
    } else if (humanScore > computerScore) {
        alert("You win!");
    } else {
        alert("You lose!");
    }

    function playRound(humanChoice, computerChoice) {
        humanChoice = humanChoice.toUpperCase();
        computerChoice = computerChoice.toUpperCase();

        if (!choices.includes(humanChoice) || !(choices.includes(computerChoice))) {
            throw new Error("Invalid choice input");
        }

        if (humanChoice === computerChoice) {
            console.log("A tie!");
            return;
        }
        if (humanChoice === "ROCK") {
            if (computerChoice === "PAPER") {
                console.log(`You lose! ${computerChoice} beats ${humanChoice}`);
                computerScore++;
            }
            else {
                console.log(`You win! ${humanChoice} beats ${computerChoice}`);
                humanScore++;
            }
        } else if (humanChoice === "PAPER") {
            if (computerChoice === "SCISSORS") {
                console.log(`You lose! ${computerChoice} beats ${humanChoice}`);
                computerScore++;
            }
            else {
                console.log(`You win! ${humanChoice} beats ${computerChoice}`);
                humanScore++;
            }
        } else { // hunmanChoice === "SCISSORS"
            if (computerChoice === "ROCK") {
                console.log(`You lose! ${computerChoice} beats ${humanChoice}`);
                computerScore++;
            }
            else {
                console.log(`You win! ${humanChoice} beats ${computerChoice}`);
                humanScore++;
            }
        }
    }
}

playGame();
