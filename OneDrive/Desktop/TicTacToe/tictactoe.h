#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "board.h"


struct Vec{
    int x;
    int y;

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }
};

struct TicTacToe{

    Board board;

    bool player1;
    bool done;

    Vec (*player1func)(Board, SquareState);
    Vec (*player2func)(Board, SquareState);

    TicTacToe(){
        player1 = true;
        done = false;
        board = Board();
        player1func = nullptr;
        player2func = nullptr;
    }

    TicTacToe(int size){
        player1 = true;
        done = false;
        board = Board(size);
        player1func = nullptr;
        player2func = nullptr;
    }

    void setPlayer1(Vec (*f)(Board, SquareState)){
        player1func = f;
    }

    void setPlayer2(Vec (*f)(Board, SquareState)){
        player2func = f;
    }

    void play(){
        while(!done) {
            system("clear");
            std::cout << board;

            if (player1) {
                bool success = false;

                Vec move = player1func(board, PLAYER1);
                success = board.updateGrid(move.x, move.y, PLAYER1);

                if (!success){
                    system("clear");
                    std::cout << board;
                    std::cout << "Invalid move" << std::endl;
                    std::cout << "Player 1 wins!!!" << std::endl;
                    done = true;
                }
            } else {
                bool success = false;

                Vec move = player2func(board, PLAYER2);
                success = board.updateGrid(move.x, move.y, PLAYER2);

                if (!success){
                    system("clear");
                    std::cout << board;
                    std::cout << "Invalid move" << std::endl;
                    std::cout << "Player 1 wins!!!" << std::endl;
                    done = true;
                }

                // while (!success) {
                //     int x, y;
                //     std::cout << "Player 2: ";
                //     std::cin >> x >> y;
                //     success = board.updateGrid(x, y, PLAYER2);
                // }
            }
            player1 = !player1;

            if (board.isWinner(PLAYER1)) {
                system("clear");
                std::cout << board;
                std::cout << "Player 1 wins!!!" << std::endl;
                done = true;
            } else if (board.isWinner(PLAYER2)) {
                system("clear");
                std::cout << board;
                std::cout << "Player 2 wins!!!" << std::endl;
                done = true;
            }
            else if (board.full()){
                system("clear");
                std::cout << board;
                std::cout << "It's a tie" << std::endl;
                done = true;
            }
        }
    }

};

#endif