Byte Bandits.cpp
# Snake Game 
1. Arrays (Fixed-size Data Structure)
  Snake Body Storage: 
  - The snake's body is stored using two arrays(tailX[] and tailY[]).  
  - Each element in these arrays represents a part of the snake’s tail, storing its X and Y coordinates.
  Obstacles Storage: 
  - the same as Snake's body.
  - These obstacles are randomly placed on the grid and increase in number as the score increases.
    
2. Object-Oriented Programming (OOP)
The game is structured using three main classes, which help to encapsulate data and make the program modular and reusable.

Class: Food 
- Stores the food's position (x, y).
- It has a function called Generate() that randomly places food on the screen.

Class: Snake 
- Stores the snake’s position (x, y), direction (dir), and tail length (nTail).
- Moves the snake by shifting tail positions and updating the head's location.
- Checks for collisions with the wall, itself, or obstacles.
- when food is eaten by increasing tail size.

3. File Handling (ifstream and ofstream)
- Used for saving and loading the high score in a file called highscore.txt.
- This ensures the best score is stored permanently even after closing the game.

4. Procedural Functions
- Draw() → Renders the game board with the snake, food, and obstacles.
- Input()→ Handles user key presses (w, a, s, d) to control the snake.
- ShowMenu() → Displays the game menu and allows users to start a new game or view the high score.

How Objects Are Structured
- The main function creates a Snake object and a Food object.
- The game loop updates the snake’s position, checks collisions, and redraws the game screen.
- Functions like Move() and Grow() modify the snake object’s attributes dynamically.



