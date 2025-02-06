#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int width = 30;
const int height = 30;
int highscore = 0;

void LoadHighScore() {
    ifstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile >> highscore;
        highscoreFile.close();
    }
}

void SaveHighScore() {
    ofstream highscoreFile("highscore.txt");
    if (highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    }
}

class Food {
public:
    int x, y;
    void Generate() {
        x = (rand() % (width - 2)) + 1;
        y = (rand() % (height - 2)) + 1;
    }
};

class Snake {
public:
    int x, y;
    int tailX[150], tailY[150];
    int nTail;
    int score;
    bool gameover;
    int obstaclesX[10], obstaclesY[10];
    int numObstacles;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

    Snake() {
        Reset();
    }

    void Reset() {
        gameover = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        score = 0;
        nTail = 2;
        tailX[0] = x - 1;
        tailY[0] = y;
        tailX[1] = x - 2;
        tailY[1] = y;
        numObstacles = 3;
        GenerateObstacles();
    }

    void GenerateObstacles() {
        srand(time(0));
        for (int i = 0; i < numObstacles; i++) {
            obstaclesX[i] = rand() % (width - 2) + 1;
            obstaclesY[i] = rand() % (height - 2);
        }
    }

    void Move() {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int tempX, tempY;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++) {
            tempX = tailX[i];
            tempY = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = tempX;
            prevY = tempY;
        }

        switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
        }

        if (x >= width - 1 || x < 1 || y >= height || y < 0) 
            gameover = true;

        for (int i = 2; i < nTail; i++) {
            if (tailX[i] == x && tailY[i] == y)
                gameover = true;
        }

        for (int i = 0; i < numObstacles; i++) {
            if (obstaclesX[i] == x && obstaclesY[i] == y)
                gameover = true;
        }
    }

    void Grow(Food& food) {
        if (x == food.x && y == food.y) {
            score += 10;
            numObstacles += score / 50;
            food.Generate();
            GenerateObstacles();
            nTail++;
        }
        if (score > highscore) {
            highscore = score;
            SaveHighScore();
        }
    }
};

void Draw(Snake& snake, Food& food) {
    system("cls");
    for (int i = 0; i < width + 1; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) cout << "#";
            else if (i == snake.y && j == snake.x) cout << "O";
            else if (i == food.y && j == food.x) cout << "F";
            else {
                bool printed = false;
                for (int k = 0; k < snake.nTail; k++) {
                    if (snake.tailX[k] == j && snake.tailY[k] == i) {
                        cout << "o";
                        printed = true;
                    }
                }
                for (int k = 0; k < snake.numObstacles; k++) {
                    if (snake.obstaclesX[k] == j && snake.obstaclesY[k] == i) {
                        cout << "#";
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 1; i++) cout << "#";
    cout << "\nSCORE: " << snake.score << "\nHIGH SCORE: " << highscore << endl;
}

void Input(Snake& snake) {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': snake.dir = Snake::LEFT; break;
        case 'd': snake.dir = Snake::RIGHT; break;
        case 'w': snake.dir = Snake::UP; break;
        case 's': snake.dir = Snake::DOWN; break;
        case 'x': snake.gameover = true; break;
        }
    }
}

void ShowMenu() {
    system("cls");
    cout << "-------- SNAKE GAME --------" << endl;
    cout << "1. Start New Game" << endl;
    cout << "2. View Highscore" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    LoadHighScore();
    Snake snake;
    Food food;
    food.Generate();
    bool gameRunning = true;
     while (gameRunning) {
        ShowMenu();
        char choice;
        cin >> choice;

        switch (choice) {
        case '1': {
             Snake snake;
    Food food;
    food.Generate();
    while (!snake.gameover) {
        Draw(snake, food);
        Input(snake);
        snake.Move();
        snake.Grow(food);
        Sleep(100);
    }
     system("cls");
            cout << "Game Over!" << endl;
            cout << "Your Score: " << snake.score << endl;
            cout << "High Score: " << highscore << endl;
            cout << "Press any key to return to the menu..." << endl;
            _getch(); 
            break;
        }
        case '2':
            system("cls");
            cout << "Highscore: " << highscore << endl;
            cout << "Press any key to return to menu..." << endl;
            _getch();  
            break;
        case '3':
            gameRunning = false;
            cout << "Thanks for playing! Final Score: " << snake.score << endl;
            cout << "Highest Score: " << highscore << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            Sleep(100);
            break;
        }
     }
    return 0;
}