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

    struct Piece {
        int row, column;
        int length;
        Direction direction;
    };

    struct Move {
        int pieceIndex, distance;
    };

    typedef std::vector<Piece> Puzzle;
    typedef std::vector<int> State;
    typedef std::vector<Move> Path;

private:
    void readPuzzle();
    bool solvePuzzle();
    void showSolution();
    bool moveLeft(State &state, int pieceIndex) const;
    bool moveRight(State &state, int pieceIndex) const;
    bool moveUp(State &state, int pieceIndex) const;
    bool moveDown(State &state, int pieceIndex) const;

private:
    int pieceCount;
    Puzzle puzzle;
    Path solution;
};

#endif
