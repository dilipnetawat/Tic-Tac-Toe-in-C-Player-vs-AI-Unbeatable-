#include <stdio.h>

char board[3][3];

void initBoard() {
    char p = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = p++;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0]==board[i][1] && board[i][1]==board[i][2]) return board[i][0];
        if (board[0][i]==board[1][i] && board[1][i]==board[2][i]) return board[0][i];
    }
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2]) return board[0][0];
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0]) return board[0][2];

    return 0;
}

int movesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 1;
    return 0;
}

int minimax(int depth, int isAI) {
    int result = checkWin();
    if (result == 'O') return +10 - depth;  // AI wins
    if (result == 'X') return -10 + depth;  // Player wins
    if (!movesLeft()) return 0;            // Draw

    if (isAI) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'O';
                    int score = minimax(depth + 1, 0);
                    board[i][j] = backup;
                    if (score > best) best = score;
                }
            }
        }
        return best;
    } 
    else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    char backup = board[i][j];
                    board[i][j] = 'X';
                    int score = minimax(depth + 1, 1);
                    board[i][j] = backup;
                    if (score < best) best = score;
                }
            }
        }
        return best;
    }
}

void aiMove() {
    int bestScore = -1000;
    int bestR = -1, bestC = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char backup = board[i][j];
                board[i][j] = 'O';

                int score = minimax(0, 0);
                board[i][j] = backup;

                if (score > bestScore) {
                    bestScore = score;
                    bestR = i;
                    bestC = j;
                }
            }
        }
    }
    board[bestR][bestC] = 'O';
}

int main() {
    initBoard();
    int pos;
    char winner;

    printf("TIC TAC TOE (Player = X, AI = O)\n");
    printBoard();

    while (1) {
        printf("Your move (1-9): ");
        scanf("%d", &pos);
        if (pos < 1 || pos > 9) {
            printf("Invalid move!\n");
            continue;
        }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;

        if (board[r][c] == 'X' || board[r][c] == 'O') {
            printf("Spot taken, try again!\n");
            continue;
        }

        board[r][c] = 'X';
        printBoard();

        winner = checkWin();
        if (winner == 'X') {
            printf("You WIN!\n");
            break;
        }
        if (!movesLeft()) {
            printf("DRAW!\n");
            break;
        }

        printf("AI is thinking...\n");
        aiMove();
        printBoard();

        winner = checkWin();
        if (winner == 'O') {
            printf("AI WINS! (Unbeatable)\n");
            break;
        }
        if (!movesLeft()) {
            printf("DRAW!\n");
            break;
        }
    }

    return 0;
}
