#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <ostream>
#include <fstream>
#include "GameState.h"
#include "Graph.h"
#include "Vertex.h"
#include "Queue.h"


int stateUtility(const GameState& state) {
    // Check if X has won
    if (state.hasWon(0)) {
        return 100;  // A high positive score for a winning state for X
    }

    // Check if O has won
    if (state.hasWon(1)) {
        return -100;  // A high negative score for a winning state for O
    }

    // If the game is a tie
    if (state.turnCount == state.size * state.size) {
        return 0;  // Score 0 for a tie
    }

    // If the game is not finished yet
    return 1;  // A small positive score for an unfinished game
}
Vec validMove(GameState game){
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                return Vec(i, j);
            }
        }
    }
    return Vec(0,0);
}

int miniMax(const GameState& state, int depth, bool maximizingPlayer) {
    if (state.done || depth == 0) {
        // Return a simple score based on the current state (you need to define this)
        return stateUtility(state);
    }
    if (maximizingPlayer) {
        int maxEval = -1000000;
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) {
                if (state.grid[i][j] == -1) {
                    GameState nextState = state;
                    nextState.play(i, j);
                    int eval = miniMax(nextState, depth - 1, false);
                    maxEval = std::max(maxEval, eval);
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 1000000;
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) {
                if (state.grid[i][j] == -1) {
                    GameState nextState = state;
                    nextState.play(i, j);
                    int eval = miniMax(nextState, depth - 1, true);
                    minEval = std::min(minEval, eval);
                }
            }
        }
        return minEval;
    }
}

Vec findBestMove(const GameState& game) {
    Graph<GameState> stateSpace;
    Queue<Vertex<GameState>*> frontier;
    Vertex<GameState>* start = new Vertex<GameState>(game);
    int x = -1, y = -1;

    stateSpace.addVertex(start);
    frontier.enqueue(start);

    int bestValue = -1000;

    while (!frontier.isEmpty()) {
        Vertex<GameState>* curr = frontier.dequeue();
        if (!curr->data.done) {
            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (curr->data.grid[i][j] == -1) {
                        GameState next = curr->data;
                        next.play(i, j);
                        Vertex<GameState>* successor = new Vertex<GameState>(next);

                        // Check if the board configuration already exists
                        bool alreadyExist = false;
                        for (int k = 0; k < stateSpace.vertices.size(); k++) {
                            if ((stateSpace.vertices[k]->data) == next) {
                                alreadyExist = true;
                                break;
                            }
                        }


                        if (!alreadyExist) {
                            stateSpace.addVertex(successor);
                            stateSpace.addDirectedEdge(curr, successor);

                            if (!successor->data.done) {
                                frontier.enqueue(successor);
                            }
                            int value = miniMax(next, 2, false);  // Adjust depth as needed
                            if (value > bestValue) {
                                bestValue = value;
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
            }
        }
    }
    return Vec(x, y);
}

//reads the file like "player1"space"player2"
int readStats(std::string player){ 
    int x, o;
    std::ifstream MyReadFile("stats.txt");

    while (MyReadFile >> x >> o) {
        // std::cout << x << " " << o << std::endl;
    }

    if (player == "x") {
        return x;
    } else {
        return o;
    }
    
}

// Resets Statistics (You can add this to menu if you want)
void resetStatistics() {
  std::ofstream outFile("stats.txt", std::ios::app);
  outFile << "0 0";
}

// Completely Clears Stats File ~ used for Updating {NOT FOR RESETING STATS}
void clearStatsFile() {
  std::ofstream outFile("stats.txt", std::ofstream::trunc);
  outFile << "";
}

//Saving function score 1, score 2
void updateStatistics(char winner) {
  // Save individual stats to override later
  int xWins = readStats("x");
  int oWins = readStats("o");
  
  // Clear file to override later
  clearStatsFile();

  // Increment Wins for winner according to input of 'winner'
  if(winner == 'X'){
    xWins += 1;
  }
  else if(winner == 'O') {
    oWins += 1;
  }

// Override Statistics in stats.txt with updated statistics
std::ofstream outFile("stats.txt", std::ios::app);
outFile << xWins << " " << oWins;
}

void hardMode(){
     GameState game;
// Human Gameplay

// Print Message When Game is Over
    std::cout << game << std::endl;
    std::cout << std::endl;

    if(game.hasWon(0)){
        std::cout << "Player X has won"<< std::endl;
    } else if (game.hasWon(1)){
        std::cout << "Player O has won" << std::endl;
    }
    else {
        std::cout << "It's a tie" << std::endl;
    }

    std::cout << "Press [ENTER] to go to menu: ";

    std::cin.ignore();
    std::string empty;
    getline(std::cin, empty);
}


void showStatistics(int& xWins, int& oWins){
//FINISH CODE.. X & Y VARIABLES ARE SET TO 0
    system("clear");

    int x = 0;
    int o = 0;

    //Finish code for x & y implementation

    std::cout << "=========================" << std:: endl;
    std::cout << "     STATISTICS PAGE     " << std::endl;
    std::cout << "=========================" << std:: endl;

    std::cout << std::endl;
    std::cout << "Player 1 has WON " << xWins << " times" << std::endl;
    std::cout << "Player 2 has WON " << oWins << " times" << std::endl;
    std::cout << std::endl;
    std::cout <<"------------------------------"<<std::endl;
    std::cout << "Press [ENTER] to go back to menu: ";
    std::cin.ignore();
    std::string empty;
    getline(std::cin,empty);
}



void humanMode(int& xWins, int& oWins){
    GameState game;
// Human Gameplay
    while(!game.done){
        system("clear");
         int currentPLayer = game.getCurrentTurn()+1; 
        std::cout<<game<<std::endl;
        std::cout<<"Player " << currentPLayer <<": ";
        std::string input;
        int pos1, pos2;
        std::cin >> input;

            if(input.length() == 2 && 
            toupper(input[0]) >= 'A' && toupper(input[0]) <= 'C' &&
            input[1] >= '1' && input[1] <= '3') {
              
                pos2 = int(toupper(input[0])) - 65;
                pos1 = int(input[1]) - 49;
        }
        game.play(pos1,pos2);
        
    }
// Print Message When Game is Over
    std::cout << game << std::endl;
    std::cout << std::endl;

  if(game.hasWon(0)){
        std::cout << "Player X has won"<< std::endl;
        updateStatistics('X');
        
    } else if (game.hasWon(1)){
        std::cout << "Player O has won" << std::endl;
        updateStatistics('O');
    }
    else {
        std::cout << "It's a tie" << std::endl;
    }

    std::cout << "Press [ENTER] to go to menu: ";

    std::cin.ignore();
    std::string empty;
    getline(std::cin, empty);
}

void easyMode(){
    GameState game;
// Computer Gameplay - Picks first available spot
    while(!game.done){
        system("clear");
        std::cout << game << std::endl;
        int x, y;
        if(game.currentTurn){
            Vec move = validMove(game);
            x = move.x;
            y = move.y;
        } else{
            std::cout << std::endl;
            std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;
        }
        game.play(x,y);
    }

    system("clear");
    std::cout << game << std::endl;
    std::cout << std::endl;
    if(game.hasWon(0)){
        std::cout << "Player X has won"<< std::endl;
    } else if (game.hasWon(1)){
        std::cout << "Player O has won" << std::endl;
    }
    else {
        std::cout << "It's a tie" << std::endl;
    }
    std::cout << "Press [ENTER] to go to menu: ";
    std::cin.ignore();
    std::string empty;
    getline(std::cin,empty);

}



void menu(){
    system("clear");
    std::cout << "============================" << std:: endl;
    std::cout << "   WELCOME TO TIC-TAC-TOE   " << std::endl;
    std::cout << "============================" << std:: endl;

    std::cout<<std::endl;
    std::cout << "1. Play against Human" << std::endl;
    std::cout << "2. Play against Computer"  << std::endl;
    std::cout << "3. How to Play" << std::endl;
    std::cout << "4. Statistics" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "SELECT AN OPTION: ";
}

void chooseDifficulty(){

// Completed
    system("clear");
    std::cout << "=========================" << std:: endl;
    std::cout << "    SELECT DIFFICULTY     " << std::endl;
    std::cout << "=========================" << std:: endl;
    std::cout << std::endl;
    std::cout << "1. Easy Mode" << std::endl;
    std::cout << "2. Hard Mode" << std::endl;
    std::cout << std::endl;
    std::cout << "SELECT AN OPTION: ";

    int option;
    std::cin>>option;

// User Selects Difficulty;
    switch(option){
        case 1:
            easyMode();
            break;
        case 2:
            hardMode();
            break;
    }
}


void printRules() {
    std::cout << "=========================" << std:: endl;
    std::cout << "       HOW TO PLAY       " << std::endl;
    std::cout << "=========================" << std:: endl << std::endl;
    std::cout << "[*] Player 1 and Player 2 play the game is played on a 3x3 grid." << std::endl;
    std::cout << "[*] Player 1 goes first and places an X in any empty square." << std::endl;
    std::cout << "[*] Player 2 then places an O in any empty square." << std::endl;
    std::cout << "[*] Players take turns placing their marks in empty squares until one player gets 3 of their marks in a row, either horizontally, vertically, or diagonally." << std::endl;
    std::cout << "[*] If all 9 squares are filled and no player has 3 in a row, the game is a tie." << std::endl << std::endl;
    std::cout << "Example: If player 1 inputs A1:" << std::endl;
    std::cout << "    A   B   C  " << std::endl;
    std::cout << "   --- --- --- " << std::endl;
    std::cout << "1 | X |   |   |" << std::endl;
    std::cout << "   --- --- --- " << std::endl;
    std::cout << "2 |   |   |   |" << std::endl;
    std::cout << "   --- --- --- " << std::endl;
    std::cout << "3 |   |   |   |" << std::endl;
    std::cout << "   --- --- --- " << std::endl;

    std::cout << "Press [ENTER] to go back to the main menu: " << std::endl;
    
    std::cin.ignore();
    std::string empty;
    getline(std::cin,empty);
}


#endif