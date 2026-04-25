#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

int N;
int solutionCount = 0;
int steps = 0;   // count recursive moves

// Set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Print board
void printBoard(vector<vector<int>>& board) {
    system("cls");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            if (board[i][j] == 1) {
                setColor(10);   // green queen
                cout << "Q ";
            } else {
                setColor(8);    // gray empty
                cout << ". ";
            }

            setColor(7);
        }
        cout << endl;
    }
    cout << endl;
}

// Check if queen can be placed
bool isSafe(vector<vector<int>>& board, int row, int col) {

    // Check left row
    for (int i = 0; i < col; i++)
        if (board[row][i] == 1)
            return false;

    // Upper diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    // Lower diagonal
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;

    return true;
}

// Solve using backtracking
void solve(vector<vector<int>>& board, int col) {

    // If all queens placed
    if (col == N) {
        solutionCount++;

        setColor(14);
        cout << "\nSolution " << solutionCount << " Found:\n";
        setColor(7);

        printBoard(board);
        Sleep(500);

        return;
    }

    for (int i = 0; i < N; i++) {

        if (isSafe(board, i, col)) {

            board[i][col] = 1;

            // Increase steps
            steps++;

            // Print only every 500 steps
            if (steps % 500 == 0) {
                printBoard(board);
                Sleep(5);
            }

            solve(board, col + 1);

            // Backtrack
            board[i][col] = 0;
        }
    }
}

// Main
int main() {

    cout << "Enter value of N (4 to 10): ";
    cin >> N;

    if (N < 4) {
        cout << "No solution exists for N < 4" << endl;
        return 0;
    }

    vector<vector<int>> board(N, vector<int>(N, 0));

    cout << "\nSolving...\n";
    Sleep(500);

    solve(board, 0);

    setColor(11);
    cout << "\nTotal Solutions = " << solutionCount << endl;
    setColor(7);

    return 0;
}