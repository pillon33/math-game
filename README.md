# Math Game
Game that helps you learn math operations (addition, subtraction, multiplication and division).

# TODO

## Frontend
  - Main menu with four buttons ✔️
  - Options panel with two sliders ✔️
  - Panel to choose game type ✔️
  - Panel to choose operation ✔️
  - Question window ✔️
  - Good answer window ✔️
  - Bad answer window ✔️
  - Leaderboard tab ❌
  - Entering initials for leaderboard ❌
  
## Backend
  - Saving and loadnig options from a file ✔️
  - Saving and loading best scores from a file ❌
  - Learning game type ❌
  - Test game type ❌
  - Arcade game type ❌
  
# Game types

## Normal
Game type focused on learning, user enters answer, if answer is wrong correct answer is shown, game ends when user gives correct answer to all questions

## Test
Game type that evaluates users knowledge, user enters answer, and is only informed if answer was correct, game ends when user enters any answer to all questions.
User is informed about correct answer percentage, if it is above 80% user passed the test.

## Arcade
Game type that focuses mostly on rivlary between players. The goal is to answer correct to as many questions as possible, the game ends when incorrect answer is given
or when the time is up. The score is the number of questions answered multiplied by 10, 20 or 30 depending on dificulty level. 
If user qualifies for TOP 10 then he must enter his intials and the score is saved to the leaderboard.

# Options
There are two sliders to adjust game options, after leaving this tab all options are saved to a file. When the program starts it loads options from this file or sets 
default values if the file is missing.

## Game length
This option adjusts game length (amount of questions in Normal and Test mode (5, 10 or 15 questions), time in Arcade mode (30, 45 or 60s after each correct answer 5s are added))

## Difficulty level
This option adjusts the difficulty. This means that in each question result range will change. There are 3 options Easy, Medium and hard.

### Easy
  - Range <1, 50> for addition and subtraction.
  - Range <1, 100> for multiplication.
  - Range <1, 20> for division.
  
### Medium
  - Range <30, 100> for addition and subtraction.
  - Range <49, 400> for multiplication.
  - Range <10, 40> for division.
  
### Hard
  - Range <50, 150> for addition and subtraction.
  - Range <100, 1000> for multiplication.
  - Range <20, 60> for division.
