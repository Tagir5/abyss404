#include <stdio.h>

void frame(int rocket1, int rocket2, int ball_x, int ball_y, int count_l, int count_r) {
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < 80; j++) {
            if (i == 0 || i == 26) {
                printf("*");
            } else if (i == ball_y && j == ball_x) {
                putchar('O');
            } else if (j == 0 && (i == rocket1 - 1 || i == rocket1 || i == rocket1 + 1)) {
                printf("|");
            } else if (j == 79 && (i == rocket2 - 1 || i == rocket2 || i == rocket2 + 1)) {
                printf("|");
            } else if (j == 40) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("LEFT COUNT = %d | RIGHT COUNT = %d \n", count_l, count_r);
}

char Input_Left() {
    char input;
    char next_char;
    while (1) {
        if (scanf("%c", &input) != 1) {
            while (getchar() != '\n');
            continue;
        }
        if (input == '\n') {
            continue;
        }

        next_char = getchar();
        if (next_char != '\n') {
            while (getchar() != '\n');
            continue;
        }
        if (input == 'm' || input == 'k' || input == 'a' || input == 'z' || input == ' ') {
            return input;
        }
    }
}

void print_gol_ascii(int x) {
    printf("\033[H\033[J");

    printf("\n\n\n\n\n\n\n");
    printf("                                                              \n");
    printf("                                                              \n");
    printf("                             GOAL                             \n");
    if (x == 1) {
        printf("                             RIGHT                             \n");

    } else {
        printf("                             LEFT                             \n");
    }
    printf("                                                              \n");
    printf("                                                              \n");
    printf("                                                              \n");
    printf("\n\n\n\n\n\n\n");
}

void game_over(int count_l) {
    printf("\n\n\n\n\n\n\n");
    printf("                                                              \n");
    printf("                                                              \n");
    printf("                          GAME OVER                            \n");
    if (count_l == 2) {
        printf("       CONGRATULATIONS TO THE PLAYER ON THE LEFT!           \n");

    } else {
        printf("       CONGRATULATIONS TO THE PLAYER ON THE RIGHT!         \n");
    }
    printf("                                                              \n");
    printf("                                                              \n");
    printf("                                                              \n");
    printf("\n\n\n\n\n\n\n");
}

int moove_ball(int count_l, int count_r) {
    int rok1 = 13, rok2 = 13, b_x = 40, b_y = 13;
    int flag_gol = 0, b_potolok = 0, b_pol = 0, b_stena_left = 0, b_stena_right = 0;
    int flag = 0;
    while (!flag_gol) {
        char f = Input_Left();
        if ((f == 'A' || f == 'a') && rok1 > 2) rok1--;
        if ((f == 'Z' || f == 'z') && rok1 < 24) rok1++;
        if ((f == 'K' || f == 'k') && rok2 > 2) rok2--;
        if ((f == 'M' || f == 'm') && rok2 < 24) rok2++;
        if (b_y == 1) {
            b_potolok = 1;
            b_pol = 0;
        }
        if (b_y == 25) {
            b_pol = 1;
            b_potolok = 0;
        }
        if ((b_y == rok1 || b_y == rok1 + 1 || b_y == rok1 - 1) && b_x == 1) {
            b_stena_left = 1;
            b_stena_right = 0;
        } else if ((b_y == rok2 || b_y == rok2 + 1 || b_y == rok2 - 1) && b_x == 78) {
            b_stena_right = 1;
            b_stena_left = 0;
        } else if (b_x == 0) {
            flag_gol = 1;
            print_gol_ascii(1);
            continue;
        } else if (b_x == 79) {
            flag_gol = 1;
            flag = 1;
            print_gol_ascii(0);
            continue;
        }
        b_y += (b_pol) ? -1 : (b_potolok) ? 1 : -1;
        b_x += (b_stena_right) ? -1 : (b_stena_left) ? 1 : -1;
        printf("\033[H\033[J");
        frame(rok1, rok2, b_x, b_y, count_l, count_r);
    }
    return flag;
}

int main() {
    int count_l = 0, count_r = 0;
    while (count_l != 2 && count_r != 2) {
        int flag = moove_ball(count_l, count_r);
        if (flag == 1) {
            count_l++;
        } else {
            count_r++;
        }
    }
    printf("\033[H\033[J");
    game_over(count_l);
}
