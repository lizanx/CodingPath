let choices = ["ROCK", "PAPER", "SCISSORS"];
let humanScore = 0;
let computerScore = 0;

let results = document.querySelector("#results");
let playerChoices = document.querySelector("#player-choices");
for (let i = 0; i < playerChoices.children.length; i++) {
    playerChoices.children[i].addEventListener("click", (e) => {
        playRound(e.target.textContent, getComputerChoice());
    });
}

function getComputerChoice() {
    return choices[Math.floor(Math.random() * choices.length)]
}

function playRound(humanChoice, computerChoice) {
    humanChoice = humanChoice.toUpperCase();
    computerChoice = computerChoice.toUpperCase();
    let lastHumanScore = humanScore;
    let lastComputerScore = computerScore;

    if (!choices.includes(humanChoice) || !(choices.includes(computerChoice))) {
        throw new Error("Invalid choice input");
    }

    let roundResult = document.createElement("li");

    if (humanChoice !== computerChoice) {
        if (humanChoice === "ROCK") {
            if (computerChoice === "PAPER") {
                computerScore++;
            }
            else {
                humanScore++;
            }
        } else if (humanChoice === "PAPER") {
            if (computerChoice === "SCISSORS") {
                computerScore++;
            }
            else {
                humanScore++;
            }
        } else { // hunmanChoice === "SCISSORS"
            if (computerChoice === "ROCK") {
                computerScore++;
            }
            else {
                humanScore++;
            }
        }
    }

    if (humanScore > lastHumanScore) {
        roundResult.textContent = "Win";
        roundResult.style.color = "green";
    } else if (computerScore > lastComputerScore) {
        roundResult.textContent = "Lose";
        roundResult.style.color = "red";
    } else {
        roundResult.textContent = "Tie";
    }
    results.appendChild(roundResult);

    if (humanScore >= 5) {
        alert("You win!");
        resetGame();
    } else if (computerScore >= 5) {
        alert("You lose!");
        resetGame();
    }

    function resetGame() {
        humanScore = 0;
        computerScore = 0;
        results.replaceChildren();
    }
}
