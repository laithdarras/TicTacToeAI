#ifndef BOARD_H
#define BOARD_H

#include <iostream>

enum SquareState {EMPTY, PLAYER1, PLAYER2};

struct Board {
private:
    int size;
    SquareState **grid;
    
    // allocating memory for grid on the heap
    void initGrid() {
        grid = new SquareState*[size];

        for (int i = 0; i < size; i++) {
            grid[i] = new SquareState[size];
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                grid[i][j] = EMPTY;
            }
        }
    }

public:
    // default constructor
    Board() {
        // std::cout << "default constructor" << std::endl;
        size = 3;
        initGrid();
    }

    // overloaded constructor
    Board(int size) {
        // std::cout << "overloaded constructor" << std::endl;
        this->size = size;
        initGrid();
    }

    // copy constructor
    // used to initialize NEWLY created object using another object
    Board(const Board& other) {
        // std::cout << "copy constructor" << std::endl;
        size = other.size;
        initGrid();

        // copying elements over from other grid
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    // overloaded assignment operator
    Board& operator=(const Board& other) {
        if (size == other.size) {
            // copying elements over from other grid
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    grid[i][j] = other.grid[i][j];
                }
            }
        } else {
            for (int i = 0; i < size; i++) {
                delete[] grid[i];
            }
            delete[] grid;

            size = other.size;
            initGrid();

            // copying elements over from other grid
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    grid[i][j] = other.grid[i][j];
                }
            }
        }
        return *this;
    }

    // overloaded comparison operator
    bool operator==(const Board& other) {
        if (size != other.size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] != other.grid[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    int getSize() const {
        return size;
    }

    SquareState getGrid(int x, int y) const {
        return grid[x][y];
    }

    // destructor
    ~Board() {
        for (int i = 0; i < size; i++) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    // update function
    bool updateGrid(int x, int y, SquareState player) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            return false;
        }

        if (grid[x][y] != EMPTY) {
            return false;
        }

        grid[x][y] = player;
        return true;
    }

    // check if winner
    bool isWinner(SquareState player) const {
        for (int i = 0; i < size; i++){
            bool fullRow = true;
            for (int j = 0; j < size; j++){
                if (grid[i][j] != player){
                    fullRow = false;
                }
            }
            if (fullRow) return true;
        }


        for (int i = 0; i < size; i++){
            bool fullCol = true;
            for (int j = 0; j < size; j++){
                if (grid[j][i] != player){
                    fullCol = false;
                }
            }
            if (fullCol) return true;
        }

        bool topDiag = true;
        for (int i = 0; i < size; i++){
            if (grid[i][i] != player){
                topDiag = false;
            }
        }
        if (topDiag) return true;

        bool botDiag = true;
        for (int i = 0; i < size; i++){
            if (grid[i][size - 1 -i] != player){
                botDiag = false;
            }
        }
        if (botDiag) return true;

        return false;
    }

    bool full() const {
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (grid[i][j] == EMPTY){
                    return false;
                }
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream&, const Board&);
};

// overloaded shift left operator
std::ostream& operator<<(std::ostream& os, const Board& board){
    os << "   ";
    for (int j = 0; j < board.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < board.size; j++){
        os << "--- ";
    }
    os << std::endl;
    for (int i = 0; i < board.size; i++){
        os << i << " ";
        for (int j = 0; j < board.size; j++){
            char c = ' ';
            if (board.grid[i][j] == PLAYER1){
                c = 'X';
            }
            else if (board.grid[i][j] == PLAYER2){
                c = 'O';
            }
            os << "| " << c << " ";
            if (j == board.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < board.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif