#ifndef LION
#define LION
#include "GameScene.h"
#include "char.h"

#define MOVESPEEDLION 3.f

#define LION_W 78.f
#define LION_H 78.f

extern bool LionDeadFlg;

extern bool g_MoveLion;

extern Animal lion;
//関数呼び出し
void liondraw();

extern CUSTOMVERTEX drawlion[4];


#endif

