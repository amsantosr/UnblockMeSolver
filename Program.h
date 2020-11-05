#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <map>
#include <iostream>

class Program
{
public:
    Program();
    void execute();

private:
    enum Direction { Horizontal, Vertical };

    struct Block {
        int row, column;
        int length;
        Direction direction;
    };

    struct Move {
        int blockIndex, distance;
    };

    typedef std::vector<Block> Puzzle;
    typedef std::vector<int> State;
    typedef std::vector<Move> Path;

private:
    void readPuzzle();
    bool solvePuzzle();
    void showSolution();
    bool moveLeft(State &state, int blockIndex) const;
    bool moveRight(State &state, int blockIndex) const;
    bool moveUp(State &state, int blockIndex) const;
    bool moveDown(State &state, int blockIndex) const;

private:
    int blockCount;
    Puzzle puzzle;
    Path solution;
};

#endif
