#ifndef ELEPHANT
#define ELEPHANT

#include "GameScene.h"
#include "char.h"

#define MOVESPEEDELEPHANT 2.f

#define ELEPHANT_W 104.f
#define ELEPHANT_H 104.f
//関数呼び出し
void elephantdraw(int time);

extern bool g_Moveelephant;

extern bool ElephantDeadFlg;

extern Animal elephant;
extern Animal elephant2;
extern Animal elephant3;
extern Animal elephant4;
extern Animal elephant5;

extern CUSTOMVERTEX drawelephant[4];
extern CUSTOMVERTEX drawelephant2[4];
extern CUSTOMVERTEX drawelephant3[4];
extern CUSTOMVERTEX drawelephant4[4];
extern CUSTOMVERTEX drawelephant5[4];

#endif 

