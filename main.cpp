#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <array>
#include <algorithm>
using namespace std;

const vector<int> UP = { -1,0};
const vector<int> DOWN = { 1,0 };
const vector<int> LEFT = { 0,-1 };
const vector<int> RIGHT = { 0,1 };
int score = 0;


class Snake {
public:
    vector<vector<int>> body;
    vector<int> direction;
    vector<int> position = { 0,0 };

    Snake(vector<vector<int>> init_body, vector<int> init_direction ) {
        body = init_body;
        direction = init_direction;
    }
    void take_step() {
        body = vector<vector<int>>(body.begin() + 1, body.end());
        body.push_back(position);
    }
    void set_position() {
        position[0] = head()[0] + direction[0];
        position[1] = head()[1] + direction[1];
    }
    void set_direction(vector<int> new_direction) {
        direction = new_direction;
    }
    vector<int> head() {
        return body.back();
    }
};

class Apple {
public:
    int apple_x;
    int apple_y;
    int apple_max_x;
    int apple_max_y;
    Apple(int max_y, int max_x) {
        apple_max_x = max_x;
        apple_max_y = max_y;
        apple_x = rand() % max_x;
        apple_y = rand() % max_y;
    }
    void new_apple() {
        apple_x = rand() % apple_max_x;
        apple_y = rand() % apple_max_y;
    }
};

class Game {

public:
    int height;
    int width;
    Game(int y, int x) {
        height = y;
        width = x;
    }
    vector<vector<int>> board_matrix() {
        vector<vector<int>> matrix(height, vector<int>(width, 0));
        return matrix;
    }
    void render(Snake test, Apple apple) {
        try {
            vector<vector<int>> board = board_matrix();
            int a = test.body.size()-1;
            board[apple.apple_y][apple.apple_x] = 3;
            for (int b = 0; b < a; b++) {
                if (test.body[b][0] == test.head()[0] and test.body[b][1] == test.head()[1]) {
                    throw invalid_argument("Snake not eating snake");
                }
                else {
                    board[test.body[b][0]][test.body[b][1]] = 1;
                }
            }
            if (test.head()[0] < 0 or test.head()[1] < 0 or test.head()[0] >= board.size() or test.head()[1] >= board[0].size()) {
                throw invalid_argument("Wall no good");
            }
            else {
                board[test.head()[0]][test.head()[1]] = 2;
            }
            int max_y = board.size();
            int max_x = board[0].size();
            for (int i = 0; i < max_y; i++) {
                if (i == 0) {
                    cout << "+";
                    for (int a = 0; a <= max_x; a++) {
                        if (a == max_x) {
                            cout << "+";
                        }
                        else {
                            cout << "-";
                        }
                    }
                    cout << endl;
                }
                for (int j = 0; j < max_x; j++) {
                    if (j == 0) {
                        cout << "|";
                    }
                    if (board[i][j] == 0) {
                        cout << " ";
                    }
                    else if (board[i][j] == 1) {
                        cout << "O";
                    }
                    else if (board[i][j] == 2) {
                        cout << "X";
                    }
                    else if (board[i][j] == 3) {
                        cout << "A";
                    }
                    if (j == max_x - 1) {
                        cout << "|";
                    }

                }

                cout << endl;
                if (i == max_y - 1) {
                    cout << "+";
                    for (int b = 0; b <= max_x; b++) {
                        if (b == max_x) {
                            cout << "+";
                        }
                        else {
                            cout << "-";
                        }
                    }
                    cout << endl << " Score: " << score << endl;
                   
                }
            }

        }
        catch (const invalid_argument& error_) {
            cout << error_.what() << endl << endl;
            game_over();
        }
    }
    void game_over() {
        cout << "###############" << endl << "###############" << endl << " YOU LOST " << endl << "Score: " << score << endl << "###############" << endl << "###############";
        Sleep(5000);
        exit(0);
    }
    };
int main() {
        Game game(20, 30);
        Apple apple(20, 30);
        Snake snake({ {0, 0 }, {1, 0}, {2, 0}, {3, 0}, {4, 0} }, DOWN);
        char movement;
        while (true) {
            game.render(snake, apple);
            if (snake.head()[0] == apple.apple_y and snake.head()[1] == apple.apple_x) {
                score++;
                apple.new_apple();
                snake.body.insert(snake.body.begin(), snake.body.front());
            }
            cin >> movement;
            if (movement == 'w') {
                snake.set_direction(UP);
                snake.set_position();
                snake.take_step();
            }
            else if (movement == 'a') {
                snake.set_direction(LEFT);
                snake.set_position();
                snake.take_step();
            }
            else if (movement == 's') {
                snake.set_direction(DOWN);
                snake.set_position();
                snake.take_step();
            }
            else if (movement == 'd') {
                snake.set_direction(RIGHT);
                snake.set_position();
                snake.take_step();
            }
            system("cls");
        }
        return 0;
}