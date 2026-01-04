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

int myStrCmp(const char* str1, const char* str2)
{
    if (str1 == nullptr || str2 == nullptr)
        return 0;
    while (*str1 && *str2 && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

bool isValidQueen(const Queen queens[], int x, int y, int& queenCount, int cols, int rows)
{
    if (x<0 || x>=cols || y<0 || y>=rows)
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

bool isWin(const Queen queens[], int& queenCount, int cols, int rows)
{
    if (queenCount == 0)
        return false;
    for (int i = 0;i < rows;i++)
    {
        for (int j = 0;j < cols;j++)
        {
            if (isValidQueen(queens, j, i, queenCount, cols, rows))
                return false;
        }
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

void back(int& queenCount)
{
    queenCount--;
}

int main()
{
    std::cout << "Commands available before the start of a game:" << std::endl;
    std::cout << "new N M           --->    new game with NxM board" << std::endl;
    std::cout << "load file.txt     --->    load a game" << std::endl;
    std::cout << "help              --->    show this menu again" << std::endl;
    Queen queens[MAX_SIZE];   //n-cols
    int cols, rows;           //m-rows
    char command[128];
    while (true)
    {
        std::cin >> command;
        if (myStrCmp(command, "new") == 0)
        {
            std::cin >> cols >> rows;
            //int minimal = cols < rows ? cols : rows;
            int queenCount = 0;
            bool cancel = false;
            std::cout << "Game started!" << std::endl;
            std::cout << "Commands available during a game:" << std::endl;
            std::cout << "play x y          --->    place a queen on position (x,y)" << std::endl;
            std::cout << "show              --->    show the board" << std::endl;
            std::cout << "free              --->    show free spaces on the board" << std::endl;
            std::cout << "back              --->    undo last move" << std::endl;
            std::cout << "turn              --->    show whose turn it is" << std::endl;
            std::cout << "help              --->    show this menu again" << std::endl;
            std::cout << "save file.txt     --->    save current game" << std::endl;
            std::cout << "exit              --->    exit current game without saving" << std::endl;
            while (!isWin(queens, queenCount, cols, rows))
            {
                std::cin >> command;
                if (myStrCmp(command, "play") == 0)
                {
                    addQueen(queens, cols, rows, queenCount);
                }
                else if (myStrCmp(command, "free") == 0)
                {
                    free(queens, cols, rows, queenCount);
                }
                else if (myStrCmp(command, "show") == 0)
                {
                    show(queens, cols, rows, queenCount);
                }
                else if (myStrCmp(command, "back") == 0)
                {
                    back(queenCount);
                }
                else if (myStrCmp(command, "exit") == 0)
                {
                    cancel = true;
                    break;
                }
                else if (myStrCmp(command, "help") == 0)
                {
                    std::cout << "Commands available during a game:" << std::endl;
                    std::cout << "play x y          --->    place a queen on position (x,y)" << std::endl;
                    std::cout << "show              --->    show the board" << std::endl;
                    std::cout << "free              --->    show free spaces on the board" << std::endl;
                    std::cout << "back              --->    undo last move" << std::endl;
                    std::cout << "turn              --->    show whose turn it is" << std::endl;
                    std::cout << "help              --->    show this menu again" << std::endl;
                    std::cout << "save file.txt     --->    save current game" << std::endl;
                    std::cout << "exit              --->    exit current game without saving" << std::endl;
                }
                else
                {
                    std::cout << "Invalid command! Try again!" << std::endl;
                }
            }
            if (!cancel)
            {
                std::cout << "Winner is player ";
                if (queens[queenCount - 1].player)
                    std::cout << '1' << std::endl;
                else
                    std::cout << '2' << std::endl;
            }
        }
        else if (myStrCmp(command, "exit") == 0)
            break;
        else if (myStrCmp(command,"help")==0)
        {
            std::cout << "Commands before start of game:" << std::endl;
            std::cout << "new N M           --->    new game with NxM board" << std::endl;
            std::cout << "load file.txt     --->    load a game" << std::endl;
            std::cout << "help              --->    show this menu again" << std::endl;
        }
        else
            std::cout << "Invalid command! Try again!" << std::endl;
    }
}
