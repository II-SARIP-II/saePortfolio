#ifndef __ACTION__H__
#define __ACTION__H__

#define WIDTH 10
#define HEIGHT 10
#define EMPTY ' '
#define MAINCARACTERE 'T'
#define FINISH 'F'
#define WALL '9'
#define BORDER '0'

typedef struct {
    char map[HEIGHT][WIDTH];
} terrain;

extern terrain map;

// Prototypes des fonctions avec un pointeur vers un tableau `terrain`
int goUp(int pY);
int goDown(int pY);
int goRight(int pX);
int goLeft(int pX);
void printMap(terrain *t);
terrain* returnMap(void);
int random(int x);
char moveCarac(terrain *t, int x, int y, char action);
void setCarac(terrain *t, int type);
int getCaracX(terrain *t);
int getCaracY(terrain *t);


#endif // __ACTION__H__
