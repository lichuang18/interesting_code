#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define SNAKE_MAX_LENGTH (WIDTH * HEIGHT)

int main()
{
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    int x, y;
    int snakeX[SNAKE_MAX_LENGTH];
    int snakeY[SNAKE_MAX_LENGTH];
    int snakeLength = 1;
    char direction = 'R';
    int foodX, foodY;

    for (int i = 0; i < SNAKE_MAX_LENGTH; i++)
    {
        snakeX[i] = -1;
        snakeY[i] = -1;
    }

    x = WIDTH / 4;
    y = HEIGHT / 2;

    snakeX[0] = x;
    snakeY[0] = y;

    foodX = WIDTH / 2;
    foodY = HEIGHT / 2;

    while (1)
    {
        clear();

        mvprintw(foodY, foodX, "@");

        if (direction == 'U')
            y--;
        if (direction == 'D')
            y++;
        if (direction == 'L')
            x--;
        if (direction == 'R')
            x++;

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        {
            mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Game Over!");
            refresh();
            getch();
            break;
        }

        for (int i = snakeLength - 1; i > 0; i--)
        {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        snakeX[0] = x;
        snakeY[0] = y;

        for (int i = 1; i < snakeLength; i++)
        {
            if (x == snakeX[i] && y == snakeY[i])
            {
                mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Game Over!");
                refresh();
                getch();
                endwin();
                return 0;
            }
        }

        if (x == foodX && y == foodY)
        {
            snakeLength++;
            foodX = rand() % WIDTH;
            foodY = rand() % HEIGHT;
        }

        mvprintw(y, x, "O");

        refresh();
        usleep(100000);

        int ch = getch();
        if (ch != ERR)
        {
            if ((ch == 'w' || ch == 'W') && direction != 'D')
                direction = 'U';
            if ((ch == 's' || ch == 'S') && direction != 'U')
                direction = 'D';
            if ((ch == 'a' || ch == 'A') && direction != 'R')
                direction = 'L';
            if ((ch == 'd' || ch == 'D') && direction != 'L')
                direction = 'R';
        }
    }

    endwin();
    return 0;
}
