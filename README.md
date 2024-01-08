# Terminal Minesweeper with AI Bot

🕹️ **Welcome to Minesweeper!**

This project is a C++ terminal-based Minesweeper clone with an AI bot that strives to find and execute moves autonomously. 🤖 Please note that the project is a work in progress, and is undergoing active development.

## Features

- **AI Bot Integration**: The game boasts an AI bot that autonomously discovers moves.
- **Still in Development**: This project is still under construction, evolving continually.
- **User Interaction**: If the bot halts or faces challenges, users can take over and make moves manually.

## Getting Started

To dive into the game:

1. Clone this repository.
2. Navigate to the project directory in your terminal.
3. Compile the C++ code.
4. Run the executable to unleash the gaming experience.

Please note: The AI may not always make optimal moves due to ongoing improvements. Your feedback and contributions are highly valued! 💡

## Original Minesweeper

For the classic Minesweeper experience without the AI bot, explore the [MineSweeperCpp](https://github.com/AndyNichol3/MineSweeperCpp).

## The Game

This is what a completed game should look like: 

<img src="https://github.com/AndyNichol3/Minesweeper-Bot/blob/main/completedBotGame.png" alt="completed game" width="400" height="400">

## Working Problems

Under some cases, the code will hault if there are no more 100% certian moves. 
This is where the mathWeightedGuess function comes in and is what I am currently developing. 
This would kick in after the board looks like this: 

<img src="https://github.com/AndyNichol3/Minesweeper-Bot/blob/main/botNeedToMakeAGuess.png" alt="completed game" width="400" height="400">

There is also a problem where the bot has no idea what do to when it doesnt find a mine from the inital reveal which doesnt happen often but looks like this. 

<img src="https://github.com/AndyNichol3/Minesweeper-Bot/blob/main/noMinesFound.png" alt="completed game" width="400" height="400">

Eventually, I will make a function to try to guess until it finds a 0 maybe? Not sure of the approach I will take here yet so if you have a suggestion reach out!

## Observations

A few things ive observed while developing this:

1. You cant win 100% of the time. this game does have some element of chance to it so you can only make your best guess sometimes.

This is an example of where there is a 50/50 chance of getting the right guess: 
The upper left cornere are the last 2 spaces remaining and one of them is a mine. 

<img src="https://github.com/AndyNichol3/Minesweeper-Bot/blob/main/50percentchance.png" alt="completed game" width="400" height="400">

2. Larger boards are harder for the bot to deal with right now.

## Lets Get In Touch

If you would like to reachout to suggest ideas, bug fixes, or connect, reach out to me here: 
[LinkedIn](https://www.linkedin.com/in/connectandrewnicholson) or [Email](mailto:andrewtodnicholson@gmail.com)






