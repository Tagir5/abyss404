#include <ncurses.h>
#include <stdio.h>

#define X 80
#define Y 25
#define LIFE 1
#define DEAD 0

void Frame(int gener);
int Default_Life(char life[Y][X]);
void Out_Put_New(char life[Y][X]);
int Count(char life[Y][X], int x, int y);
void New_Life(char life[Y][X]);
void User_Input(int *speed, int *running);
void Ncurs();

int main(void) {
    Ncurs();
    char life[Y][X];
    int speed = 100;
    int gener = 1;
    int running = 1;
    Default_Life(life);
    (void)freopen("/dev/tty", "r", stdin);
    while (running) {
        Frame(gener);
        Out_Put_New(life);
        New_Life(life);
        User_Input(&speed, &running);
        napms(speed);
        gener++;
    }
    nodelay(stdscr, 0);
    curs_set(1);
    return 0;
}

void Ncurs() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, 1);
}

void Frame(int gener) {
    for (int y = 0; y < Y; y++) {
        mvprintw(y, X, "|");
    }
    for (int i = 0; i < X + 1; i++) {
        mvprintw(Y, i, "*");
    }
    mvprintw(Y + 1, X - 80, "Press A to increase speed or Z to decrease speed");
    mvprintw(Y + 2, X - 80, "Press 'Space bar' to exit (or ctrl+z)            | GENERATION: %d", gener);
}

int Default_Life(char life[Y][X]) {
    char buffer[X + 2];
    int y = 0;
    while (y < Y && fgets(buffer, sizeof(buffer), stdin)) {
        for (int x = 0; x < X; x++) {
            life[y][x] = (buffer[x] == '0') ? LIFE : DEAD;
        }
        y++;
    }
}

void Out_Put_New(char life[Y][X]) {
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            mvaddch(y, x, life[y][x] ? '0' : ' ');
        }
    }
}

int Count(char life[Y][X], int x, int y) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int ny = (y + dy + Y) % Y;
            int nx = (x + dx + X) % X;

            if (life[ny][nx] == LIFE) {
                count++;
            }
        }
    }
    return count;
}

void New_Life(char life[Y][X]) {
    char new_life[Y][X];
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            new_life[y][x] = DEAD;
        }
    }
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            int ncol_live = Count(life, x, y);
            if (life[y][x] == LIFE) {
                new_life[y][x] = (ncol_live == 2 || ncol_live == 3) ? LIFE : DEAD;
            } else {
                new_life[y][x] = (ncol_live == 3) ? LIFE : DEAD;
            }
        }
    }
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            life[y][x] = new_life[y][x];
        }
    }
}

void User_Input(int *speed, int *running) {
    char user = getch();
    if (user != ERR) {
        if (user == 'A' || user == 'a') {
            *speed = (*speed - 10 < 10) ? 10 : (*speed - 10);
        }
        if (user == 'Z' || user == 'z') {
            *speed = (*speed + 10 > 1000) ? 1000 : (*speed + 10);
        }
        *running = (user == ' ') ? 0 : 1;
    }
    flushinp();
}