#include <iostream>
#include <string.h>
#include <array>
#include <cstdlib>

using namespace std;

#define PLAYER1 1
#define PLAYER2 2
#define DRAW 3

void fillboard(array<array<int, 3>, 3> &board)
{
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
            board[i][j] = -1;
    }
}

void display(array<array<int, 3>, 3> &board) {

    cout << "\033[2J\033[1;1H" << endl;
    cout << "-------------" << endl;
    for(int i = 0; i < board.size(); i++)
    {
        cout << "|";
        for(int j = 0; j < board[i].size(); j++)
        {
            if(board[i][j] == -1)
                cout << "   |";
            else if(board[i][j] == 0)
                cout << " X |";
            else if(board[i][j] == 5)
                cout << " O |";
        }

        cout << "\n-------------" << endl;
    }

    cout << endl;
}

int playerInput(array<array<int, 3>, 3> &board, int row, int column, int playerNum)
{
    if(board[row - 1][column - 1] != -1)
        return -1;
    else {
        board[row - 1][column - 1] = playerNum;
        return 0;
    }
}

int checkBoard(array<array<int, 3>, 3> board)
{ 
    int total = 0; 

    for(int i = 0; i < board.size(); i++)
    {
        total = 0;
        for(int j = 0; j < board[i].size(); j++)
                total += board[i][j];
        
        if(total == 0)
            return PLAYER1;
        else if(total == 15)
            return PLAYER2;
    }

    for(int i = 0; i < board[0].size(); i++)
    {
        total = 0;
        for(int j = 0; j < board.size(); j++)
                total += board[j][i];
        
        if(total == 0)
            return PLAYER1;
        else if(total == 15)
            return PLAYER2;
    }

    int diagSum = 0;
    int diagSum2 = 0;

    for(int i = 0; i < board.size(); i++)
        diagSum += board[i][i];

    if(diagSum == 0)
        return PLAYER1;
    else if(diagSum == 15)
        return PLAYER2;


    for(int i = 0; i < board.size(); i++)
        diagSum2 += board[i][board.size() - i - 1];
        
    if(diagSum2 == 0)
        return PLAYER1;
    else if(diagSum2 == 15)
        return PLAYER2;


    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            if(board[i][j] == -1)
                return 0;
        }
    }

    return DRAW;
}



int main(int argc, char *argv[])
{
    array<array<int, 3>, 3> board;
    fillboard(board);
    display(board);

    int turn = 1;
    int row, column = 0;

    while(true)
    {
        switch(turn) { 

            case 1:
                try { 
                    cout << "Player 1's turn!" << endl;
                    cout << "Enter the row # -> ";
                    cin >> row;
                    cin.ignore();

                    if(row > 3 || row < 1)
                        throw "Row doesn't exist. Try rows between 1 and 3.";

                    cout << "Enter the column # -> ";
                    cin >> column;
                    cin.ignore();

                    if(column > 3 || column < 1)
                        throw "Column doesn't exist. Try columns between 1 and 3.";

                    if(playerInput(board, row, column, 0) == -1)
                        throw "Spot is taken. Try another one.";
                    else {
                        display(board);
                    }

                    turn++;
                    break;

                }catch(const char* e) {
                    cerr << e << endl;
                    break;
                }catch(...) {
                    cerr << "There was an unknown error." << endl;
                    break;
                }

            case 2:
                try { 
                    cout << "Player 2's turn!" << endl;
                    cout << "Enter the row # -> ";
                    cin >> row;
                    cin.ignore();
                    
                    if(row > 3 || row < 1)
                        throw "Row doesn't exist. Try rows between 1 and 3.";

                    cout << "Enter the column # -> ";
                    cin >> column;
                    cin.ignore();

                    if(column > 3 || column < 1)
                        throw "Column doesn't exist. Try columns between 1 and 3.";

                    if(playerInput(board, row, column, 5) == -1)
                        throw "Spot is taken. Try another one.";
                    else {
                        display(board);
                    }

                    turn--;
                    break;

                }catch(const char* e) {
                    cerr << e << endl;
                    break;
                }catch(...) {
                    cerr << "There was an unknown error." << endl;
                    break;
                }

            default:
                cerr << "Something went wrong. Try restarting the program." << endl;
                break;
        }

        int winCondition = checkBoard(board);

        if(winCondition == PLAYER1) {
            cout << "Player 1 wins!" << endl;
            break;
        }else if(winCondition == PLAYER2) {
            cout << "Player 2 wins!" << endl;
            break;
        }else if(winCondition == DRAW) {
            cout << "The match was a draw!" << endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}

