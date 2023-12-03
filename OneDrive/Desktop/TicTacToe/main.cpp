#include <cstdint>
#include <iostream>
#include "board.h"
#include "tictactoe.h"
#include <cstring>
using namespace std;


Vec simpleAI(Board board, SquareState player){
    Vec result(0,0);
    for (int i = 0; i < board.getSize(); i++){
        for (int j = 0; j < board.getSize(); j++){
            if (board.getGrid(i, j) == EMPTY){
                result = Vec(i, j);
                goto end;
            }
        }
    }
    end:
    board.updateGrid(2, 0, PLAYER2);
    board.updateGrid(2, 1, PLAYER2);
    board.updateGrid(2, 2, PLAYER2);

    return result;
}

Vec human(Board board, SquareState player){
    if (player == PLAYER1){
        int x, y;
        cout << "Player 1: ";
        cin >> x >> y;
        return Vec(x, y);
    }
    else{
        int x, y;
        cout << "Player 2: ";
        cin >> x >> y;
        return Vec(x, y);
    }
}

int main(int argc, char* argv[]) {

    int size = 3;

    Vec (*func1)(Board, SquareState) = human;
    Vec (*func2)(Board, SquareState) = simpleAI;
    if (argc > 1){
        size = stoi(argv[1]);
    }
        
    TicTacToe game(size);

    game.setPlayer1(func1);
    game.setPlayer2(func2);

    game.play();

    return 0;
}