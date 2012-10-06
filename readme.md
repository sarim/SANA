SANA is a chatterbot application, or half of a chatterbot application to be precise. It's a frontend to the popular Pandorabots API, coded in C programming language. I've coded it just to experiment with the C programming language, not for serious deployment of this application, therefore this application may (or may not) contain bad or offensive code.


BUILDING THE PROJECT
    > This project needs the standard GCC compiler to be built.
    > You also need the LibCURL 4 to be configured in your building environment.
    > Clone this repository (or download the sources) in you local storage.
    > Open Terminal/CMD and change to the directory containing the sources.
    > Issue the `make` command. The project will be compiled as SANA (.exe on Windows).
    > Execute from the Terminal (Double clicking the binary works on Windows only).


IN-CHAT COMMANDS
    SANA packs some in chat commands. Type `!help` to see the available command list. 
    NOTE: Every command starts with the "!" symbol, don't forget to type it.


LOADING ALIEN BOTS
    You can make SANA load with a different Pandorabot BotID than the built in one. Example:
    `$ ./SANA --botid a23qrw9r9uqaij4a`

