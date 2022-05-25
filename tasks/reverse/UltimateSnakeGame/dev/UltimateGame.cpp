#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <time.h>

// correct flag is: Aero{68b05fb8a0a617c4771d76b7f0e6df63b4f728ef3966bf6a9a69f53c8d882eac}

bool win_flag = false;
int64_t win_points = 3133731337;

std::string trash("Aero{...nice try! do you dump it???(this is not a flag!)");
std::vector<std::string> fake_flags;

int8_t trash_in_memory1[4096];


int8_t enc_flag[70] = { 
        136, 203, 113, 157, 21, 253, 190, 164, 144, 2, 141, 31, 
        16, 89, 166, 255, 171, 118, 13, 15, 97, 31, 70, 45, 22, 
        181, 223, 76, 1, 8, 53, 89, 132, 131, 51, 5, 157, 241, 
        42, 239, 59, 83, 75, 69, 21, 239, 116, 41, 52, 65, 11, 
        104, 63, 25, 8, 51, 166, 219, 62, 152, 43, 207, 39, 44, 
        76, 196, 43, 27, 160, 210
};

int8_t trash_in_memory2[1024];

int8_t valid_xors[70] = { 
        67, 81, 199, 236, 118, 122, 19, 20, 148, 102, 88, 194, 40, 
        32, 205, 56, 55, 119, 33, 88, 138, 40, 63, 46, 249, 175, 
        144, 69, 124, 63, 37, 148, 115, 81, 105, 35, 183, 176, 219, 
        169, 60, 70, 158, 154, 85, 31, 230, 237, 29, 141, 235, 62, 
        202, 88, 122, 28, 32, 173, 189, 247, 18, 165, 87, 80, 116, 
        13, 245, 76, 74, 120
};

int8_t trash_in_memory3[512];

int8_t valid_idxs[70] = { 
        58, 57, 60, 24, 35, 14, 20, 8, 66, 0, 50, 23, 12, 15, 42, 43, 
        52, 7, 4, 34, 53, 21, 17, 67, 18, 2, 46, 64, 16, 51, 33, 29, 
        36, 3, 62, 69, 61, 31, 55, 49, 19, 9, 28, 32, 30, 38, 41, 68, 
        1, 13, 40, 63, 65, 56, 22, 44, 26, 47, 10, 25, 6, 39, 27, 45, 
        5, 59, 48, 54, 11, 37 
};

int8_t trash_in_memory4[1024];

void make_trash(void)
{
    for (int i = 0; i < 4096; i++)
        trash_in_memory1[i] = rand() % (255) + 1;
    for (int i = 0; i < 1024; i++)
        trash_in_memory2[i] = rand() % (255) + 1;
    for (int i = 0; i < 512; i++)
        trash_in_memory3[i] = rand() % (255) + 1;
    for (int i = 0; i < 1024; i++)
        trash_in_memory4[i] = rand() % (255) + 1;
}

void make_fake_flags(void)
{
    std::string fake_flag("Aero{ this is a fake flag! dont dump memory!(this is not a flag!)");

    for (int i = 0; i < 13370; i++)
    {
        fake_flags.push_back(fake_flag);
    }
};

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (size == 0)
    {
        size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void decrypt_flag(void)
{
    
    std::vector<int8_t> flag;
    
    for (int i = 0; i < 70; i++) flag.push_back(i);
    for (int i = 0; i < 70; i++) flag[valid_idxs[i]] = enc_flag[i];
    for (int i = 0; i < 70; i++) flag[i] ^= valid_xors[i];

    for (auto i : flag) std::cout << (char)i;

    std::cout << std::endl;

}
void clear_console(void)
{
    system("cls");
}

class SnakePart {
    private:
        int32_t x;
        int32_t y;
    public:
        SnakePart() { };
        SnakePart(int32_t _x, int32_t _y) { x = _x; y = _y; };
        
        int32_t get_x() { return x; };
        int32_t get_y() { return y; };

        void set_x(int32_t _x) { x = _x; };
        void set_y(int32_t _y) { y = _y; };
};

class Game {
    private:
        int32_t x_max_size;
        int32_t y_max_size;
        
        int32_t x_point;
        int32_t y_point;

        int64_t CurrentPoints;
    
        std::vector<SnakePart> GameSnake;
    
        enum { UP, DOWN, LEFT, RIGHT } direction;

    public:
        Game( int32_t x_max, int32_t y_max )
        { 
            x_max_size = x_max;
            y_max_size = y_max;

            srand( time(NULL) + x_max + y_max );

            gen_point();

            CurrentPoints = 0;

            GameSnake.push_back(SnakePart(14, 9));
            direction = UP;
        };

        void gen_point()
        {
            x_point = rand() % (x_max_size-2)+1;
            y_point = rand() % (y_max_size-2)+1;
        }

        void show()
        {
            clear_console();

            for (int y = 0; y < y_max_size; y++)
            {
                for (int x = 0; x < x_max_size; x++)
                {
                    // print borders
                    if (y == 0) { std::cout << "#"; continue; }
                    if (x == 0) { std::cout << "#"; continue; }
                    if (y == (y_max_size - 1)) { std::cout << "#"; continue; }
                    if (x == (x_max_size - 1)) { std::cout << "#"; continue; }
                    
                    // print point 
                    if (x == x_point && y == y_point) { std::cout << "P"; continue; }

                    bool is_snake = false;
                    // print snake
                    for (auto elem : GameSnake)
                    {
                        if (x == elem.get_x() && y == elem.get_y())
                        {
                            std::cout << "*";
                            is_snake = true;
                        }
                    }

                    if (!is_snake) std::cout << " ";
                }
                std::cout << std::endl;
            }

            std::cout << "Points: " << CurrentPoints << "/" << win_points << std::endl;
            std::cout << "Point_x: " << x_point << " Point_y: " << y_point << std::endl;
        }
        
        void get_input()
        {
            if (_kbhit())
            {
                char sym;
                sym = _getch();
                sym = tolower(sym);

                switch (sym)
                {
                    case 'w':
                    {
                        direction = UP;
                        break;
                    }
                    case 'a':
                    {
                        direction = LEFT;
                        break;
                    }
                    case 's':
                    {
                        direction = DOWN;
                        break;
                    }
                    case 'd':
                    {
                        direction = RIGHT;
                        break;
                    }
                
                    default:
                    {
                        direction = direction;
                        break;
                    }
                }
            }
        }

        void proceed()
        {
            // proceed game win
            if (CurrentPoints == win_points)
            {
                clear_console();
                std::cout << "You win!" << std::endl;
                decrypt_flag();

                getchar();
                exit(-1);
            }

            int32_t snake_headx = GameSnake[0].get_x();
            int32_t snake_heady = GameSnake[0].get_y();

            if (snake_headx == x_point && snake_heady == y_point)
            {
                CurrentPoints++;
                gen_point();

                int32_t last_x = GameSnake[GameSnake.size() - 1].get_x();
                int32_t last_y = GameSnake[GameSnake.size() - 1].get_y();

                switch (direction)
                {
                    case UP:
                    {
                        GameSnake.push_back(SnakePart(last_x,last_y+1));
                        break;
                    }
                    case DOWN:
                    {
                        GameSnake.push_back(SnakePart(last_x,last_y-1));
                        break;
                    }
                    case LEFT:
                    {
                        GameSnake.push_back(SnakePart(last_x+1,last_y));
                        break;
                    }
                    case RIGHT:
                    {
                        GameSnake.push_back(SnakePart(last_x-1,last_y));
                        break;
                    }
                }
            }

            for (auto elem : GameSnake)
            {
                int32_t x = elem.get_x();
                int32_t y = elem.get_y();

                if (x == 0 || y == 0 || x == (x_max_size - 1) || y == (y_max_size - 1))
                {
                    clear_console();
                    std::cout << "You lose!" << std::endl;
                    getchar();
                    exit(-1);
                }
            }


            for (int i = 0; i < GameSnake.size(); i++ )
            {
                switch (direction)
                {
                    case UP:
                    {
                        int32_t x_border = GameSnake[0].get_x();

                        if (GameSnake[i].get_x() != x_border)
                        {
                            int32_t x = GameSnake[i].get_x();

                            if ( (x_border - x) > 0 )
                                GameSnake[i].set_x(GameSnake[i].get_x() + 1);
                            else
                                GameSnake[i].set_x(GameSnake[i].get_x() - 1);
                        }
                        else
                            GameSnake[i].set_y(GameSnake[i].get_y() - 1);
                        break;
                    }

                    case DOWN:
                    {
                        int32_t x_border = GameSnake[0].get_x();

                        if (GameSnake[i].get_x() != x_border)
                        {
                            int32_t x = GameSnake[i].get_x();

                            if ((x_border - x) > 0)
                                GameSnake[i].set_x(GameSnake[i].get_x() + 1);
                            else
                                GameSnake[i].set_x(GameSnake[i].get_x() - 1);
                        }
                        else
                            GameSnake[i].set_y(GameSnake[i].get_y() + 1);
                        break;
                    }

                    case LEFT:
                    {
                        int32_t y_border = GameSnake[0].get_y();

                        if (GameSnake[i].get_y() != y_border)
                        {
                            int32_t y = GameSnake[i].get_y();

                            if ((y_border - y) > 0)
                                GameSnake[i].set_y(GameSnake[i].get_y() + 1);
                            else
                                GameSnake[i].set_y(GameSnake[i].get_y() - 1);
                        }
                        else
                            GameSnake[i].set_x(GameSnake[i].get_x() - 1);
                        break;
                    }

                    case RIGHT:
                    {
                        int32_t y_border = GameSnake[0].get_y();

                        if (GameSnake[i].get_y() != y_border)
                        {
                            int32_t y = GameSnake[i].get_y();

                            if ((y_border - y) > 0)
                                GameSnake[i].set_y(GameSnake[i].get_y() + 1);
                            else
                                GameSnake[i].set_y(GameSnake[i].get_y() - 1);
                        }
                        else
                            GameSnake[i].set_x(GameSnake[i].get_x() + 1);
                        break;
                    }
                }
            }
        }
};

void print_game_banner(int64_t PointsToWin)
{
    std::cout << "---- Ultimate snake game ----" << std::endl;
    std::cout << "*********** Rules ***********" << std::endl;
    std::cout << "1. You can use only WASD to control snake!" << std::endl;
    std::cout << "2. To win you need to get " << PointsToWin << " points!" << std::endl;
    std::cout << "3. The snake moves not standard!" << std::endl;
    std::cout << "4. Do not try to hack the game!!!" << std::endl;
}

int main()
{
    make_fake_flags();
    make_trash();

    int64_t TotalNumberOfFreeBytes;

    BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceExA(
        NULL,
        NULL,
        NULL,
        (PULARGE_INTEGER)&TotalNumberOfFreeBytes
    );

    print_game_banner(TotalNumberOfFreeBytes);

    win_points = TotalNumberOfFreeBytes;
    std::cout << "Enter any character to start: ";
    getchar();

    clear_console();
    setcursor(0, 0);

    Game game = Game(30, 20);

    while (!win_flag)
    {
        Sleep(50);

        game.show();
        game.get_input();
        game.proceed();
    }

    return 0;
}
