#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <windows.h> // For Sleep function (Windows)

using namespace std;

const int MAX_ROWS = 100; // Maximum rows for the maze
const int MAX_COLS = 100; // Maximum columns for the maze

struct Position {
    int row;
    int col;
};

bool isValidMove(char maze[MAX_ROWS][MAX_COLS], int row, int col, bool visited[MAX_ROWS][MAX_COLS], int rows, int cols) {
    return row >= 0 && row < rows &&
           col >= 0 && col < cols &&
           (maze[row][col] == '0' || maze[row][col] == 'E') &&
           !visited[row][col];
}

// Function to display the maze in the CLI
void displayMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    system("CLS"); // Clear the console for smooth display
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
}

void solveMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    int startRow = -1, startCol = -1;

    // Find starting (#) position
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == '#') {
                startRow = i;
                startCol = j;
            }
        }
    }

    if (startRow == -1 || startCol == -1) {
        cout << "Maze does not have a valid start point!" << endl;
        return;
    }

    // Stack for backtracking
    stack<Position> pathStack;
    bool visited[MAX_ROWS][MAX_COLS];

    // Explicitly initialize the visited array to false
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            visited[i][j] = false;
        }
    }

    // Push starting position onto the stack
    pathStack.push({startRow, startCol});
    visited[startRow][startCol] = true;

    // Directions for moving: up, down, left, right
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

    while (!pathStack.empty()) {
        // Sleep for 1 second to observe the changes in the maze
        Sleep(1000);

        Position current = pathStack.top();
        pathStack.pop();

        int row = current.row;
        int col = current.col;

        if (maze[row][col] != 'E') {
             maze[row][col] = '#';
        }

        // Display the maze in the CLI
        displayMaze(maze, rows, cols);

        // Check if we have reached the end
        if (maze[row][col] == 'E') {
            cout << "Path found: (" << row + 1 << ", " << col + 1 << ")" << endl;
            return;
        }

        // Mark the current position as visited
        maze[row][col] = '-';

        // Explore all neighbors
        for (int i = 0; i < 4; i++) {
            int newRow = row + dRow[i];
            int newCol = col + dCol[i];

            if (isValidMove(maze, newRow, newCol, visited, rows, cols)) {
                pathStack.push({newRow, newCol});
                visited[newRow][newCol] = true;
            }
        }
    }

    cout << "No path found to the end!" << endl;
}

int main() {
    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    // Declare the ifstream object ONCE
    ifstream inputFile("maze.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    string line;

    // Read maze from file
    while (getline(inputFile, line) && rows < MAX_ROWS) {
        cols = 0;
        for (char c : line) {
            if (c != ' ') { // Skip spaces
                maze[rows][cols++] = c;
            }
        }
        rows++;
    }

    // Close the file after reading
    inputFile.close();

    // Solve the maze
    solveMaze(maze, rows, cols);

    return 0;
}
