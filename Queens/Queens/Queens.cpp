#include <iostream>
const size_t MAX_SIZE = 15;

struct Queen
{
    int x;
    int y;
    bool player;
};

int abs(int num)
{
    return num > 0 ? num : -num;
}

bool isValidQueen(const Queen queens[], int x, int y, int& queenCount, int cols, int rows)
{
    if (x<0 || x>cols || y<0 || y>rows)
    {
        return false;
    }
    for (int i = 0;i < queenCount;i++)
    {
        if (queens[i].x == x)return false;
        if (queens[i].y == y)return false;
        if (abs(queens[i].x - x) == abs(queens[i].y - y)) return false;
    }
    return true;
}

void addQueen(Queen queens[], int cols, int rows, int& queenCount)
{
    int x, y;
    std::cin >> x >> y;
    //std::cout << "Invalid queen";
    if (isValidQueen(queens, x, y, queenCount, cols, rows))
    {
        queens[queenCount].x = x;
        queens[queenCount].y = y;
        queens[queenCount].player = queenCount % 2 == 0 ? true : false;
        queenCount++;
    }
    else
    {
        std::cout << "Invalid move" << std::endl;
    }
}

void show(const Queen queens[], int cols, int rows, int queenCount)
{
    bool board[MAX_SIZE][MAX_SIZE] = { false };
    for (int i = 0;i < queenCount;i++)
    {
        board[queens[i].y][queens[i].x] = true;
    }
    for (int i = 0;i < rows;i++)
    {
        for (int j = 0;j < cols;j++)
        {
            if (board[i][j])
            {
                std::cout << "[Q] ";
            }
            else
            {
                std::cout << "[ ] ";
            }

        }
        std::cout << std::endl;
    }
}

void free(const Queen queens[], int cols, int rows, int queenCount)
{
    std::cout << "Free spaces are marked with \'~\'" << std::endl;
    for (int i = 0;i < rows;i++)
    {
        for (int j = 0;j < cols;j++)
        {
            if (isValidQueen(queens, j, i, queenCount, cols, rows))
            {
                std::cout << "[~] ";
            }
            else
            {
                std::cout << "[ ] ";
            }

        }
        std::cout << std::endl;
    }
}

int main()
{

    Queen queens[MAX_SIZE];   //n-cols
    int cols, rows;           //m-rows
    std::cin >> cols >> rows;
    int minimal = cols < rows ? cols : rows;
    int queenCount = 0;
    while (queenCount < minimal)
    {
        addQueen(queens, cols, rows, queenCount);
        free(queens, cols, rows, queenCount);
        //show(queens, cols, rows, queenCount);
    }
}
