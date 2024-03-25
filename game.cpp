#include <iostream>
#include <limits>

char game[3][3]; // 3X3 matrix 
int bestX = -1, bestY = -1; // to store coordinates of best move 
char player, opponent; // player is user and opponent is computer

bool checkMoveLeft() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (game[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

void display() {
    std::cout << "\n\n\n\t\t\t" << game[0][0] << " | " << game[0][1] << " | " << game[0][2] << std::endl << std::endl;
    std::cout << "\t\t\t" << game[1][0] << " | " << game[1][1] << " | " << game[1][2] << std::endl << std::endl;
    std::cout << "\t\t\t" << game[2][0] << " | " << game[2][1] << " | " << game[2][2] << std::endl << "\n\n\n";
}

int evaluate(int depth) {
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2]) {
        if (game[0][0] == player)
            return -10 + depth;
        if (game[0][0] == opponent)
            return 10 - depth;
    }
    if (game[2][0] == game[1][1] && game[1][1] == game[0][2]) {
        if (game[1][1] == player)
            return -10 + depth;
        if (game[1][1] == opponent)
            return 10 - depth;
    }

    for (int i = 0; i < 3; ++i) {
        if (game[i][0] == game[i][1] && game[i][1] == game[i][2]) {
            if (game[i][0] == player)
                return -10 + depth;
            if (game[i][0] == opponent)
                return 10 - depth;
        }
        if (game[0][i] == game[1][i] && game[1][i] == game[2][i]) {
            if (game[0][i] == player)
                return -10 + depth;
            if (game[0][i] == opponent)
                return 10 - depth;
        }
    }

    return 0;
}

int miniMax(int depth, bool isMax) {
    int score = evaluate(depth);
    if (score == 10 - depth)
        return score;
    if (score == -10 + depth)
        return score;
    if (!checkMoveLeft())
        return 0;

    if (isMax) {
        int bestScore = -10000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (game[i][j] == ' ') {
                    game[i][j] = opponent;
                    bestScore = std::max(miniMax(depth + 1, false), bestScore);
                    game[i][j] = ' ';
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 10000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (game[i][j] == ' ') {
                    game[i][j] = player;
                    bestScore = std::min(miniMax(depth + 1, true), bestScore);
                    game[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

void bestMove(int depth) {
    int bestValue = -1000;
    int value;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (game[i][j] == ' ') {
                game[i][j] = opponent;
                value = miniMax(depth, false);
                if (value > bestValue) {
                    bestX = i;
                    bestY = j;
                    bestValue = value;
                }
                game[i][j] = ' '; // undo changes
            }
        }
    }
}

void playerMove() {
    int row, col;
    std::cout << "Enter row and column numbers (1-3) for your move: ";
    std::cin >> row >> col;
    if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && game[row - 1][col - 1] == ' ') {
        game[row - 1][col - 1] = player;
    } else {
        std::cout << "Invalid move. Please enter row and column numbers (1-3) for your move: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        playerMove(); // Retry input
    }
}

void playGame() {
    int depth = 0;
    while (true) {
        display();
        playerMove();
        if (evaluate(0) == -10) {
            display();
            std::cout << "Congratulations! You win!" << std::endl;
            break;
        } else if (!checkMoveLeft()) {
            std::cout << "It's a draw!" << std::endl;
            break;
        }
        bestMove(depth);
        game[bestX][bestY] = opponent;
        if (evaluate(0) == 10) {
            display();
            std::cout << "Computer wins! Better luck next time." << std::endl;
            break;
        }
        depth++;
    }
}

int main() {
    std::cout << "Welcome to Tic-Tac-Toe game!!!" << std::endl;
    std::cout << "Please enter your choice 'O' or 'X' for the game: ";
    std::cin >> player;
    opponent = (player == 'X') ? 'O' : 'X

