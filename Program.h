#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>

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

    typedef std::vector<Block> BlockVector;
    typedef std::vector<int> State;
    typedef std::vector<Move> MoveVector;

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
    BlockVector blocks;
    MoveVector path;
};

#endif
