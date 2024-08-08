#include <head_files.h>
#include <stdio.h>
#include <limits.h>

int board[BOARD_SIZE];


int isBoardFull(int board[BOARD_SIZE]) {
	int i=0;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == 0) {
            return 0;
        }
    }
    return 1;
}
int max(int a, int b) {
    return a > b ? a : b;
}


int min(int a, int b) {
    return a < b ? a : b;
}

int checkWin(int board[BOARD_SIZE], int player) {
	int i=0;
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
        {0, 4, 8}, {2, 4, 6}             
    };
    for (i = 0; i < 8; i++) {
        if (board[winPatterns[i][0]] == player &&
            board[winPatterns[i][1]] == player &&
            board[winPatterns[i][2]] == player) {
            return 1;
        }
    }
    return 0;
}

// Minimax??
int minimax(int board[BOARD_SIZE], int depth, int isMax, int alpha, int beta) {
    int score = checkWin(board, 2) ? 10 - depth : (checkWin(board, 1) ? depth - 10 : 0);
    if (score != 0 || isBoardFull(board)) {
        return score;
    }

    if (isMax) {
		int i=0;
        int best = INT_MIN;
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == 0) {
                board[i] = 2;
                best = max(best, minimax(board, depth + 1, !isMax, alpha, beta));
                board[i] = 0;
                alpha = max(alpha, best);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
		int i=0;
        for (i = 0; i < BOARD_SIZE; i++) {
            if (board[i] == 0) {
                board[i] = 1;
                best = min(best, minimax(board, depth + 1, !isMax, alpha, beta));
                board[i] = 0;
                beta = min(beta, best);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return best;
    }
}


int findBestMove(int board[BOARD_SIZE]) {
    int bestVal = INT_MIN;
    int bestMove = -1;
	int i=0;
	int moveVal;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == 0) {
            board[i] = 2;
            moveVal = minimax(board, 0, 0, INT_MIN, INT_MAX);
            board[i] = 0;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

//int main() {
//    int board[BOARD_SIZE] = {	2, 2, 1, 
//								0, 0, 0, 
//								0, 0, 1};
//    int bestMove = findBestMove(board);
//    printf("The best move is at index: %d\n", bestMove);
//    return 0;
//}
