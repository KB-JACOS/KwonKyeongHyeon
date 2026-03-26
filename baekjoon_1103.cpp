#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int boardHeight, boardWidth;
vector<string> gameBoard;

vector<vector<int>> maximumTurnCountMemo;


vector<vector<bool>> isCellInCurrentPath;

bool infiniteGameDetected = false;

const int rowDirection[4] = { -1, 1, 0, 0 };
const int colDirection[4] = { 0, 0, -1, 1 };

bool isInsideBoard(int row, int col) {
    return 0 <= row && row < boardHeight && 0 <= col && col < boardWidth;
}

int calculateMaximumTurns(int currentRow, int currentCol) {

    if (isCellInCurrentPath[currentRow][currentCol]) {
        infiniteGameDetected = true;
        return 0;
    }

    int& cachedResult = maximumTurnCountMemo[currentRow][currentCol];
    if (cachedResult != -1) {
        return cachedResult;
    }

    isCellInCurrentPath[currentRow][currentCol] = true;

    int moveDistance = gameBoard[currentRow][currentCol] - '0';
    int maximumTurnCountFromCurrentCell = 1; 


    for (int directionIndex = 0; directionIndex < 4; ++directionIndex) {
        int nextRow = currentRow + rowDirection[directionIndex] * moveDistance;
        int nextCol = currentCol + colDirection[directionIndex] * moveDistance;


        if (!isInsideBoard(nextRow, nextCol) || gameBoard[nextRow][nextCol] == 'H') {
            continue;
        }


        int nextCellMaximumTurnCount = calculateMaximumTurns(nextRow, nextCol);


        if (infiniteGameDetected) {
            isCellInCurrentPath[currentRow][currentCol] = false;
            return 0;
        }

        maximumTurnCountFromCurrentCell = max(
            maximumTurnCountFromCurrentCell,
            nextCellMaximumTurnCount + 1
        );
    }


    isCellInCurrentPath[currentRow][currentCol] = false;

    //maximumTurnCountMemo[currentRow][currentCol]¿¡ ±â·Ï
    cachedResult = maximumTurnCountFromCurrentCell;
    return cachedResult;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> boardHeight >> boardWidth;
    gameBoard.resize(boardHeight);

    for (int row = 0; row < boardHeight; ++row) {
        cin >> gameBoard[row];
    }

    maximumTurnCountMemo.assign(boardHeight, vector<int>(boardWidth, -1));
    isCellInCurrentPath.assign(boardHeight, vector<bool>(boardWidth, false));

    int answer = calculateMaximumTurns(0, 0);


    if (infiniteGameDetected) {
        cout << -1 << '\n';
    }
    else {
        cout << answer << '\n';
    }

    return 0;
}