#ifndef GAME
#define GAME

#define PLAYER1 1
#define PLAYER2 2
#define DRAW 3

class Piece {
  float width;
  float height;
  Color color;
  int code;
  
public:
  Piece(float width, float height)
  {
    this->width = width;
    this->height = height;
    color = WHITE;
    code = -1;
  }
  
  void changeColor(Color color){this->color = color;}
  void setCode(int arg){code = arg;}
  int getCode(){return code;}
  
  float getHeight(){return height;}
  float getWidth(){return width;} 
  
  void drawPiece(int i, int j) {DrawRectangle(j * (width + 3), (i * (width + 3)), width, width, color);}
};

void makeGrid(std::array<std::array<Piece*, 3>, 3> &board, float width)
{    
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[i].size(); j++) {
            Piece *block = new Piece(width, width);
            board[i][j] = block;
        }
    }
}


void drawBackground(float blockSize, std::array<std::array<Piece*, 3>, 3> &board)
{
    for(int i = 0; i < 3; i++) 
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j]->drawPiece(i, j);
        }
    }
}

void getPosition(int &x, int &y, float blockSize)
{
    x = (x / (blockSize + 1)) + 1;
    y = ((y / (blockSize + 1)) + 1);  
}

int checkBoard(std::array<std::array<Piece*, 3>, 3> board)
{
    int total = 0; 

    for(int i = 0; i < board.size(); i++)
    {
        total = 0;
        for(int j = 0; j < board[i].size(); j++)
                total += board[i][j]->getCode();
        
        if(total == 0)
            return PLAYER1;
        else if(total == 15)
            return PLAYER2;
    }

    for(int i = 0; i < board[0].size(); i++)
    {
        total = 0;
        for(int j = 0; j < board.size(); j++)
                total += board[j][i]->getCode();
        
        if(total == 0)
            return PLAYER1;
        else if(total == 15)
            return PLAYER2;
    }

    int diagSum = 0;
    int diagSum2 = 0;

    for(int i = 0; i < board.size(); i++)
        diagSum += board[i][i]->getCode();

    if(diagSum == 0)
        return PLAYER1;
    else if(diagSum == 15)
        return PLAYER2;


    for(int i = 0; i < board.size(); i++)
        diagSum2 += board[i][board.size() - i - 1]->getCode();
        
    if(diagSum2 == 0)
        return PLAYER1;
    else if(diagSum2 == 15)
        return PLAYER2;


    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            if(board[i][j]->getCode() == -1)
                return 0;
        }
    }

    return DRAW;
}

#endif