#ifndef ELEPHANT
#define ELEPHANT

#include "GameScene.h"
#include "char.h"

#define MOVESPEEDELEPHANT 1.f

#define ELEPHANT_W 104.f
#define ELEPHANT_H 104.f
//関数呼び出し
void elephantdraw();

extern bool g_Moveelephant;

extern bool ElephantDeadFlg;

extern Animal elephant;

extern CUSTOMVERTEX drawelephant[4];

#endif 

