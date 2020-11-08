#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <map>

class Program
{
public:
    Program() {}
    void execute();

private:
    enum Direction { Horizontal, Vertical };

    struct Block {
        int row, column;
        int length;
        Direction direction;
    };

    typedef std::vector<Block> BlockVector;
    typedef std::vector<int> State;
    struct Move;
    typedef std::map<State, Move> MapStates;

    struct Move {
        int blockIndex, distance;
        MapStates::iterator previous;
    };

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
    BlockVector puzzle;
    MapStates::iterator lastIterator;
};

#endif
