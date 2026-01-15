#include <iostream>
#include <fstream>
const size_t MAX_SIZE = 15;
const size_t MAX_COMMAND_SIZE = 128;

struct Queen
{
    int x;
    int y;
    bool player;
};

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

bool isValidQueen(const Queen queens[], int x, int y, size_t& queenCount, int cols, int rows)
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

bool isWin(const Queen queens[], size_t& queenCount, int cols, int rows)
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

void addQueen(Queen queens[], int cols, int rows, size_t& queenCount)
{
    int x, y;
    std::cin >> x >> y;
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

void show(const Queen queens[], int cols, int rows, size_t queenCount)
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

void free(const Queen queens[], int cols, int rows, size_t queenCount)
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

void back(size_t& queenCount)
{
    queenCount--;
}

void turn(size_t& queenCount)
{
    if (queenCount%2==0)
    {
        std::cout << "Its P1's turn." << std::endl;
    }
    else
        std::cout << "Its P2's turn." << std::endl;
}

void history(Queen queens[], size_t queenCount)
{
    for (int i = 0;i < queenCount; i++)
    {
        if (queens[i].player)
            std::cout << "P1 -> x=" << queens[i].x << " y=" << queens[i].y << std::endl;
        else
            std::cout << "P2 -> x=" << queens[i].x << " y=" << queens[i].y << std::endl;
    }
}

void save(const Queen queens[], size_t queenCount, int n, int m,const char* filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error in saving game"<<std::endl;
        return;
    }
    file << n << " " << m << std::endl;
    for (int i = 0;i < queenCount;i++)
    {
        file << queens[i].x << " " << queens[i].y << " " << queens[i].player << std::endl;
    }
    file.close();
}

void load(Queen queens[], size_t& queenCount, int& n, int& m, const char* filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error inloading game" << std::endl;
        return;
    }
    file >> n >> m;
    while (!file.eof())
    {
        file >> queens[queenCount].x >> queens[queenCount].y >> queens[queenCount].player;
        queenCount++;
    }
    queenCount--;
    file.close();
}

void helpBeforeGame()
{
    std::cout << "Commands available before the start of a game:" << std::endl;
    std::cout << "new N M           --->    new game with NxM board" << std::endl;
    std::cout << "load file.txt     --->    load a game" << std::endl;
    std::cout << "help              --->    show this menu again" << std::endl;
    std::cout << "exit              --->    exit app" << std::endl << std::endl;
}

void helpDuringGame()
{
    std::cout << "Commands available during a game:" << std::endl;
    std::cout << "play x y          --->    place a queen on position (x,y)" << std::endl;
    std::cout << "show              --->    show the board" << std::endl;
    std::cout << "free              --->    show free spaces on the board" << std::endl;
    std::cout << "back              --->    undo last move" << std::endl;
    std::cout << "turn              --->    show whose turn it is" << std::endl;
    std::cout << "history           --->    history of moves" << std::endl;
    std::cout << "help              --->    show this menu again" << std::endl;
    std::cout << "save file.txt     --->    save current game" << std::endl;
    std::cout << "exit              --->    exit to menu without saving" << std::endl<<std::endl;
}

bool processCommand(Queen queens[], size_t& queenCount, int cols, int rows,const char* command)
{
    if (myStrCmp(command, "play") == 0)
        addQueen(queens, cols, rows, queenCount);
    else if (myStrCmp(command, "free") == 0)
        free(queens, cols, rows, queenCount);
    else if (myStrCmp(command, "show") == 0)
        show(queens, cols, rows, queenCount);
    else if (myStrCmp(command, "back") == 0)
        back(queenCount);
    else if (myStrCmp(command, "turn") == 0)
        turn(queenCount);
    else if (myStrCmp(command, "history") == 0)
        history(queens, queenCount);
    else if (myStrCmp(command, "exit") == 0)
        return false;
    else if (myStrCmp(command, "help") == 0)
        helpDuringGame();
    else if (myStrCmp(command, "save") == 0)
    {
        char filename[1024];
        std::cin >> filename;
        save(queens, queenCount, cols, rows, filename);
    }
    else
        std::cout << "Invalid command! Try again!" << std::endl;
    return true;
}

void runGame(Queen queens[],size_t& queenCount,int cols, int rows)
{
    char command[MAX_COMMAND_SIZE];
    bool reachedEnd = true;
    while (reachedEnd&&!isWin(queens, queenCount, cols, rows))
    {
        std::cin >> command;
        reachedEnd = processCommand(queens, queenCount, cols, rows, command);
    }
    if (reachedEnd)
    {
        std::cout << "Winner is player ";
        if (queens[queenCount - 1].player)
            std::cout << '1' << std::endl;
        else
            std::cout << '2' << std::endl;
    }
}

int main()
{
    helpBeforeGame();
    Queen queens[MAX_SIZE];   //n-cols
    int cols, rows;           //m-rows
    char command[MAX_COMMAND_SIZE];
    size_t queenCount = 0;
    while (true)
    {
        std::cin >> command;
        if (myStrCmp(command, "new") == 0)
        {
            std::cin >> cols >> rows;
            bool cancel = false;
            std::cout << "Game started!" << std::endl;
            helpDuringGame();
            runGame(queens, queenCount, cols, rows);
        }
        else if (myStrCmp(command, "load") == 0)
        {
            char filename[1024];
            std::cin >> filename;
            load(queens, queenCount, cols, rows,filename);
            runGame(queens, queenCount, cols, rows);
        }
        else if (myStrCmp(command, "help") == 0)
        {
            helpBeforeGame();
        }
        else if (myStrCmp(command, "exit") == 0)
            break;
        else
            std::cout << "Invalid command! Try again!" << std::endl;
    }
}
