const inputFunc = require('./inputfunc');

function numberGuessingGame(solution, range) {
    if (solution == range) {
        console.log("Correct guess!, Hurray 😌");
        return 0;
    }
    else if (solution < range) {
        console.log("Low guess 😁");
    }
    else if (solution > range) {
        console.log("High guess 😅");
    }
    else {
        console.log("Wrong input ☹️");
    }
}

(async () => {
    const range = Math.floor(Math.random() * (20 - 1 + 1) + 1);
    let attempts = 0;
    console.log("Guess the number? range is (1 to 20) (type 0 to Quit)\n");
    while (true) {
        let solution = await inputFunc.input("")
        let num = parseInt(solution, 10);
        if (num === 0) {
            console.log("🤗🤗🤗");
            break;
        }
        if (numberGuessingGame(solution, range) == 0) {
            attempts++;
        console.log("Attempts: " + attempts);
            break;
        }
        attempts++;
        console.log("Attempts: " + attempts);
    }
})();