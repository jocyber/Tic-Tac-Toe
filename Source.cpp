#include <raylib.h>
#include <iostream>
#include <cstdlib>
#include <array>
#include <unistd.h>
#include "game.h"

int main()
{
    int turn = 1;
    const int WindowWidth = 597;
    const float blockSize {WindowWidth / 3};
    std::array<std::array<Piece*, 3>, 3> board;
    makeGrid(board, blockSize);
    
    InitWindow(WindowWidth, WindowWidth, "Player 1's Turn");
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{BLACK});
        
        drawBackground(blockSize, board);
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int col = GetMouseX();
            int row = GetMouseY();
            getPosition(col, row, blockSize);
            
            if(turn == 1) {
                if(board[row - 1][col - 1]->getCode() == -1) {
                    
                    board[row - 1][col - 1]->changeColor(BLUE);
                    board[row - 1][col - 1]->setCode(0);
                    
                    if(checkBoard(board) == 1) {
                        SetWindowTitle("Player 1 Wins!");
                        DisableCursor();
                    }else if(checkBoard(board) == 3) {
                        SetWindowTitle("It's a Draw!");
                        DisableCursor();
                    }
                    else turn = 2; SetWindowTitle("Player 2's Turn");
                }
            }else if(turn == 2) {
                if(board[row - 1][col - 1]->getCode() == -1) {
                    board[row - 1][col - 1]->changeColor(RED);
                    board[row - 1][col - 1]->setCode(5);
                    if(checkBoard(board) == 2) {
                        SetWindowTitle("Player 2 Wins!");
                        DisableCursor();
                    }else if(checkBoard(board) == 3) {
                        SetWindowTitle("It's a Draw!");
                        DisableCursor();
                    }
                    else turn = 1; SetWindowTitle("Player 1's Turn");
                }
            }
        }
     
        
        EndDrawing();
    }
    
    CloseWindow();
    return EXIT_SUCCESS;
}