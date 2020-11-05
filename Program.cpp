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
    blocks.clear();
    blocks.push_back({ 0, 3, 2, Vertical });
    blocks.push_back({ 0, 4, 2, Horizontal });
    blocks.push_back({ 1, 2, 2, Vertical });
    blocks.push_back({ 1, 5, 2, Vertical });
    blocks.push_back({ 2, 0, 2, Horizontal });
    blocks.push_back({ 2, 3, 2, Vertical });
    blocks.push_back({ 2, 4, 3, Vertical });
    blocks.push_back({ 3, 0, 2, Horizontal });
    blocks.push_back({ 3, 5, 2, Vertical });
    blocks.push_back({ 4, 0, 2, Vertical });
    blocks.push_back({ 4, 1, 3, Horizontal });
    blockCount = blocks.size();
}

bool Program::solvePuzzle()
{
    map<State, MoveVector> mapStates;
    vector<State> vector1, vector2;
    State childState;
    int distance;

    mapStates[vector<int>(blockCount, 0)];
    vector1.push_back(vector<int>(blockCount, 0));

    do {
        vector2.clear();
        for (const State &parentState : vector1) {
            for (int i = 0; i < blockCount; ++i) {
                if (blocks[i].direction == Horizontal) {
                    childState = parentState;
                    distance = 0;
                    while (moveLeft(childState, i)) {
                        --distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            vector2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                        }
                    }
                    childState = parentState;
                    distance = 0;
                    while (moveRight(childState, i)) {
                        ++distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            vector2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                            if (blocks[i].row == 2 && blocks[i].column + childState[i] == 4) {
                                path = mapStates[childState];
                                return true;
                            }
                        }
                    }
                }
                else if (blocks[i].direction == Vertical) {
                    childState = parentState;
                    distance = 0;
                    while (moveUp(childState, i)) {
                        --distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            vector2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                        }
                    }
                    childState = parentState;
                    distance = 0;
                    while (moveDown(childState, i)) {
                        ++distance;
                        if (mapStates.find(childState) == mapStates.end()) {
                            vector2.push_back(childState);
                            mapStates[childState] = mapStates[parentState];
                            mapStates[childState].push_back({ i, distance });
                        }
                    }
                }
            }
        }
        vector1.swap(vector2);
    } while (!vector1.empty());
    return false;
}

void Program::showSolution()
{
    int number = 1;
    vector<int> rows(blockCount);
    vector<int> columns(blockCount);

    // initialize the positions of the blocks
    for (int i = 0; i < blockCount; ++i) {
        rows[i] = blocks[i].row;
        columns[i] = blocks[i].column;
    }

    for (auto &move : path) {
        int &row = rows[move.blockIndex];
        int &column = columns[move.blockIndex];
        cout << number << ": (" << row << ", " << column << ") ";
        Direction direction = blocks[move.blockIndex].direction;
        if (direction == Horizontal) {
            if (move.distance < 0)
                printMove(-move.distance, 'L');
            else if (move.distance > 0)
                printMove(move.distance, 'R');
            column += move.distance;
        }
        else if (direction == Vertical) {
            if (move.distance < 0)
                printMove(-move.distance, 'U');
            else if (move.distance > 0)
                printMove(move.distance, 'D');
            row += move.distance;
        }
        cout << '\n';
        ++number;
    }
}

bool Program::moveLeft(Program::State &state, int blockIndex) const
{
    const auto &block = blocks[blockIndex];
    int newColumn = block.column + state[blockIndex] - 1;
    if (newColumn < 0)
        return false;
    for (int i = 0; i < blockCount; ++i) {
        if (i != blockIndex) {
            const auto &blockI = blocks[i];
            if (blockI.direction == Horizontal) {
                if (block.row == blockI.row && newColumn == blockI.column + state[i] + blockI.length - 1)
                    return false;
            }
            else if (blockI.direction == Vertical) {
                if (newColumn == blockI.column) {
                    int filaI = blockI.row + state[i];
                    if (block.row >= filaI && block.row < filaI + blockI.length)
                        return false;
                }
            }
        }
    }
    --state[blockIndex];
    return true;
}

bool Program::moveRight(Program::State &state, int blockIndex) const
{
    const auto &block = blocks[blockIndex];
    int nuevaColumna = block.column + state[blockIndex] + block.length;
    if (nuevaColumna >= 6)
        return false;
    for (int i = 0; i < blockCount; ++i) {
        if (i != blockIndex) {
            const auto &blockI = blocks[i];
            if (blockI.direction == Horizontal) {
                if (block.row == blockI.row && nuevaColumna == blockI.column + state[i])
                    return false;
            }
            else if (blockI.direction == Vertical) {
                if (nuevaColumna == blockI.column) {
                    int filaI = blockI.row + state[i];
                    if (block.row >= filaI && block.row < filaI + blockI.length)
                        return false;
                }
            }
        }
    }
    ++state[blockIndex];
    return true;
}

bool Program::moveUp(Program::State &state, int blockIndex) const
{
    const auto &block = blocks[blockIndex];
    int newRow = block.row + state[blockIndex] - 1;
    if (newRow < 0)
        return false;
    for (int i = 0; i < blockCount; ++i) {
        if (i != blockIndex) {
            const auto &blockI = blocks[i];
            if (blockI.direction == Horizontal) {
                if (newRow == blockI.row) {
                    int columnI = blockI.column + state[i];
                    if (block.column >= columnI && block.column < columnI + blockI.length)
                        return false;
                }
            }
            else if (blockI.direction == Vertical) {
                if (block.column == blockI.column && newRow == blockI.row + state[i] + blockI.length - 1)
                    return false;
            }
        }
    }
    --state[blockIndex];
    return true;
}

bool Program::moveDown(Program::State &state, int blockIndex) const
{
    const auto &block = blocks[blockIndex];
    int newRow = block.row + state[blockIndex] + block.length;
    if (newRow >= 6)
        return false;
    for (int i = 0; i < blockCount; ++i) {
        if (i != blockIndex) {
            const auto &blockI = blocks[i];
            if (blockI.direction == Horizontal) {
                if (newRow == blockI.row) {
                    int columnI = blockI.column + state[i];
                    if (block.column >= columnI &&block.column < columnI + blockI.length)
                        return false;
                }
            }
            else if (blockI.direction == Vertical) {
                if (block.column == blockI.column && newRow == blockI.row + state[i])
                    return false;
            }
        }
    }
    ++state[blockIndex];
    return true;
}

void Program::printMove(int distance, char step) const
{
    for (int i = 0; i < distance; ++i)
        cout << step;
}

int main()
{
    Program program;
    program.execute();
    return 0;
}
