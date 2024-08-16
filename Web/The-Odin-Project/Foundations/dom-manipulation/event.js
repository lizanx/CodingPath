const btn2 = document.querySelector("#btn-2");
btn2.onclick = () => alert("You have clicked button-2!");

const btn3 = document.querySelector("#btn-3");
btn3.addEventListener("click", (e) => {
    alert(`You've click button-3!`);
    console.log(e);
    console.log(e.target);
    e.target.style.backgroundColor = "blue";
});

const group2 = document.querySelector("#group-2");
group2.querySelectorAll("button").forEach((button) => {
    button.addEventListener("click", () => alert(button.id));
});
