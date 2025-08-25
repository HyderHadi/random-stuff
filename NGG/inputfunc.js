const readline = require('readline');

function input(prompt) {
    const read_instance = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    return new Promise((resolve) => {
        read_instance.question(prompt, (val) => {
            read_instance.close();
            resolve(val.trim());
        });
    });
}

module.exports = { input };