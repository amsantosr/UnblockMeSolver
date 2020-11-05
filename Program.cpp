#include "Program.h"

using namespace std;

Program::Program()
{
}

void Program::execute()
{
    readPuzzle();
    if (solvePuzzle())
        showSolution();
    else
        cout << "Unable to solve the given puzzle.\n";
}

void Program::readPuzzle()
{
    puzzle.clear();
    puzzle.push_back({ 0, 3, 2, Vertical });
    puzzle.push_back({ 0, 4, 2, Horizontal });
    puzzle.push_back({ 1, 2, 2, Vertical });
    puzzle.push_back({ 1, 5, 2, Vertical });
    puzzle.push_back({ 2, 0, 2, Horizontal });
    puzzle.push_back({ 2, 3, 2, Vertical });
    puzzle.push_back({ 2, 4, 3, Vertical });
    puzzle.push_back({ 3, 0, 2, Horizontal });
    puzzle.push_back({ 3, 5, 2, Vertical });
    puzzle.push_back({ 4, 0, 2, Vertical });
    puzzle.push_back({ 4, 1, 3, Horizontal });
    pieceCount = puzzle.size();
}

bool Program::solvePuzzle()
{
    map<State, Path> mapStates;
    vector<State> stack1, stack2;
    State childState;
    int distance;

    mapStates[vector<int>(pieceCount, 0)];
    stack1.push_back(vector<int>(pieceCount, 0));

    do {
        stack2.clear();
        for (const State &parentState : stack1) {
            for (int i = 0; i < pieceCount; ++i) {
                if (puzzle[i].direction == Horizontal) {
                    childState = parentState;
                    distance = 0;
                    while (moveLeft(childState, i)) {
                        --distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            stack2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                        }
                    }
                    childState = parentState;
                    distance = 0;
                    while (moveRight(childState, i)) {
                        ++distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            stack2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                            if (puzzle[i].row == 2 && puzzle[i].column + childState[i] == 4) {
                                solution = mapStates[childState];
                                return true;
                            }
                        }
                    }
                }
                else if (puzzle[i].direction == Vertical) {
                    childState = parentState;
                    distance = 0;
                    while (moveUp(childState, i)) {
                        --distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            stack2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                        }
                    }
                    childState = parentState;
                    distance = 0;
                    while (moveDown(childState, i)) {
                        ++distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            stack2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                        }
                    }
                }
            }
        }
        stack1.swap(stack2);
    } while (!stack1.empty());
    return false;
}

void Program::showSolution()
{
    int movementNumber = 1;
    for (auto &move : solution) {
        cout << movementNumber << ": " << "[" << move.pieceIndex << ", " << move.distance << "]\n";
        ++movementNumber;
    }
}

bool Program::moveLeft(Program::State &state, int pieceIndex) const
{
    const auto &piece = puzzle[pieceIndex];
    int newColumn = piece.column + state[pieceIndex] - 1;
    if (newColumn < 0)
        return false;
    for (int i = 0; i < pieceCount; ++i) {
        if (i != pieceIndex) {
            const auto &pieceI = puzzle[i];
            if (pieceI.direction == Horizontal) {
                if (piece.row == pieceI.row && newColumn == pieceI.column + state[i] + pieceI.length - 1)
                    return false;
            }
            else if (pieceI.direction == Vertical) {
                if (newColumn == pieceI.column) {
                    int filaI = pieceI.row + state[i];
                    if (piece.row >= filaI && piece.row < filaI + pieceI.length)
                        return false;
                }
            }
        }
    }
    --state[pieceIndex];
    return true;
}

bool Program::moveRight(Program::State &state, int pieceIndex) const
{
    const auto &piece = puzzle[pieceIndex];
    int nuevaColumna = piece.column + state[pieceIndex] + piece.length;
    if (nuevaColumna >= 6)
        return false;
    for (int i = 0; i < pieceCount; ++i) {
        if (i != pieceIndex) {
            const auto &pieceI = puzzle[i];
            if (pieceI.direction == Horizontal) {
                if (piece.row == pieceI.row && nuevaColumna == pieceI.column + state[i])
                    return false;
            }
            else if (pieceI.direction == Vertical) {
                if (nuevaColumna == pieceI.column) {
                    int filaI = pieceI.row + state[i];
                    if (piece.row >= filaI && piece.row < filaI + pieceI.length)
                        return false;
                }
            }
        }
    }
    ++state[pieceIndex];
    return true;
}

bool Program::moveUp(Program::State &state, int pieceIndex) const
{
    const auto &piece = puzzle[pieceIndex];
    int newRow = piece.row + state[pieceIndex] - 1;
    if (newRow < 0)
        return false;
    for (int i = 0; i < pieceCount; ++i) {
        if (i != pieceIndex) {
            const auto &pieceI = puzzle[i];
            if (pieceI.direction == Horizontal) {
                if (newRow == pieceI.row) {
                    int columnI = pieceI.column + state[i];
                    if (piece.column >= columnI && piece.column < columnI + pieceI.length)
                        return false;
                }
            }
            else if (pieceI.direction == Vertical) {
                if (piece.column == pieceI.column && newRow == pieceI.row + state[i] + pieceI.length - 1)
                    return false;
            }
        }
    }
    --state[pieceIndex];
    return true;
}

bool Program::moveDown(Program::State &estado, int pieceIndex) const
{
    const auto &piece = puzzle[pieceIndex];
    int newRow = piece.row + estado[pieceIndex] + piece.length;
    if (newRow >= 6)
        return false;
    for (int i = 0; i < pieceCount; ++i) {
        if (i != pieceIndex) {
            const auto &pieceI = puzzle[i];
            if (pieceI.direction == Horizontal) {
                if (newRow == pieceI.row) {
                    int columnI = pieceI.column + estado[i];
                    if (piece.column >= columnI &&piece.column < columnI + pieceI.length)
                        return false;
                }
            }
            else if (pieceI.direction == Vertical) {
                if (piece.column == pieceI.column && newRow == pieceI.row + estado[i])
                    return false;
            }
        }
    }
    ++estado[pieceIndex];
    return true;
}

int main()
{
    Program program;
    program.execute();
    return 0;
}
