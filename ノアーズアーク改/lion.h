#ifndef LION
#define LION
#include "GameScene.h"
#include "char.h"

#define MOVESPEEDLION 1.f
#define PLUSMOVESPEED 0.5f

#define LION_W 78.f
#define LION_H 78.f

extern Animal lion;

//関数呼び出し
void liondraw();

extern CUSTOMVERTEX drawlion[4];
void initStage6lion();
void initStage7lion();

#endif

