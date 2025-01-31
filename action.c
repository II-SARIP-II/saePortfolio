#include "action.h"
#include <stdio.h>
#include <stdlib.h>
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

terrain map = {{
                       {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
                       {'0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
                       {'0', ' ', '9', '9', '9', '9', '9', '9', ' ', '0'},
                       {'0', ' ', ' ', '9', ' ', ' ', ' ', ' ', ' ', '0'},
                       {'0', '9', ' ', '9', '9', ' ', '9', '9', '9', '0'},
                       {'0', ' ', ' ', '9', ' ', ' ', ' ', ' ', ' ', '0'},
                       {'0', '9', '9', '9', '9', '9', '9', ' ', ' ', '0'},
                       {'0', ' ', ' ', ' ', '9', ' ', '9', ' ', ' ', '0'},
                       {'0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
                       {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
               }};

terrain *returnMap(void) {
    return &map;
}

int random(int x) {
    return rand() % x;
}

int getCaracX(terrain *t) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (t->map[i][j] == MAINCARACTERE)
                return j;
        }
    }
    return -1;
}

int getCaracY(terrain *t) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (t->map[i][j] == MAINCARACTERE)
                return i;
        }
    }
    return -1;
}

void setCarac(terrain *t, int type) {
    int y, x;
    do {
        x = random(WIDTH - 2) + 1;
        y = random(HEIGHT - 2) + 1;
        printf("Tentative [%d, %d]\n", x, y);
    } while (t->map[y][x] == WALL || t->map[y][x] == BORDER || t->map[y][x] == MAINCARACTERE || t->map[y][x] == FINISH);

    if (type == 0)
        t->map[y][x] = MAINCARACTERE;
    else
        t->map[y][x] = FINISH;

    printf("Personnage placé en [%d, %d]\n", x, y);
}

char moveCarac(terrain *t, int x, int y, char action) {
    int newY = y;
    int newX = x;
    printf("X & Y are [%d, %d]\n", x, y);

    switch (action) {
        case 'z':
            newY = goUp(y);
            break;
        case 's':
            newY = goDown(y);
            break;
        case 'q':
            newX = goLeft(x);
            break;
        case 'd':
            newX = goRight(x);
            break;
        default:
            printf("Action non reconnue : %c\n", action);
            break;
    }
    printf("Trying to move from [%d, %d] to [%d, %d]\n", x, y, newX, newY);

    if (t->map[newY][newX] == EMPTY) {
        t->map[y][x] = EMPTY;
        t->map[newY][newX] = MAINCARACTERE;
        return ' ';
    }
    if (t->map[newY][newX] == FINISH) {
        printf("-------------------------------------------------------------------"
               "\n\n\n\n"
               "YOU WIN"
               "\n\n\n\n"
               "-------------------------------------------------------------------");
        fflush(stdout);
        return 'l';
    }
    if (t->map[newY][newX] == WALL || t->map[newY][newX] == BORDER) {
        printf("Cannot Move [%d,%d] 'cause %c\n", newX, newY, t->map[newY][newX]);
        fflush(stdout);
        return ' ';
    }
}

void printMap(terrain *t) {
//    for (int i = 0; i < 10; ++i) {   //color avec git bash
//        for (int j = 0; j < 10; ++j) {
//            if (t->map[i][j] == BORDER)
//                printf(RED "[%c]" RESET, t->map[i][j]);
//            else if (t->map[i][j] == WALL)
//                printf(BLUE "[%c]" RESET, t->map[i][j]);
//            else if (t->map[i][j] == MAINCARACTERE)
//                printf(YELLOW "[%c]" RESET, t->map[i][j]);
//            else if (t->map[i][j] == FINISH)
//                printf(GREEN "[%c]" RESET, t->map[i][j]);
//            else
//                printf("[%c]", t->map[i][j]);
//        }
//        printf("\n");
//        fflush(stdout);
//    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (t->map[i][j] == BORDER)
                printf("[%c]", t->map[i][j]);
            else if (t->map[i][j] == WALL)
                printf("[%c]", t->map[i][j]);
            else if (t->map[i][j] == MAINCARACTERE)
                printf("[%c]", t->map[i][j]);
            else if (t->map[i][j] == FINISH)
                printf("[%c]", t->map[i][j]);
            else
                printf("[%c]", t->map[i][j]);
        }
        printf("\n");
        fflush(stdout);
    }
}

int goUp(int pY) {
    return pY - 1;
}

int goDown(int pY) {
    return pY + 1;
}

int goRight(int pX) {
    return pX + 1;
}

int goLeft(int pX) {
    return pX - 1;
}
