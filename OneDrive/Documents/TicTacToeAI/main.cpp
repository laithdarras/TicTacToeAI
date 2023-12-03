#include <iostream>
#include "GameState.h"
#include "helper.h"

using namespace std;

int main(){
    GameState game;

    menu();
    int option;
    int xWins = readStats("x");
    int oWins = readStats("o");
    while(cin >> option){
        system("clear");
        switch(option){
            case 1:
                // User selects humanMode
                humanMode(xWins, oWins);
                break;
            case 2:
                // User selects between easyMode or hardMode
                chooseDifficulty();
                break;
            case 3:
                system("clear");
                printRules();
                break;
            case 4:
                // Displays statistics page
                xWins = readStats("x"); 
                oWins = readStats("o");
                showStatistics(xWins, oWins);
                break;
            case 5:
            // Exits program
                system("clear");
                return 0;
        }
        menu();
    }
    return 0;
}