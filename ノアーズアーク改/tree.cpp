#include "tree.h"
#include "char.h"
#include "GameScene.h"
//木の位置
mob tree = { 700.f,400.f,true }; //木

mob tree2 = { 1100.f,400.f,true };
//一つ目
CUSTOMVERTEX drawtree[4];
//二つ目
CUSTOMVERTEX drawtree2[4];

void treedraw()
{
		//	木の頂点情報
		CUSTOMVERTEX  treevertex[4]
		{
			{ -TREE_W / 2, -TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
			{ TREE_W / 2, -TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
			{ TREE_W / 2,  TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
			{ -TREE_W / 2,  TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
		};
		//位置と頂点情報を代入
		for (int i = 0; i < 4; i++)
		{
			drawtree[i] = treevertex[i];
			drawtree[i].x += tree.x;
			drawtree[i].y += tree.y;
		}
		//	木の頂点情報
	CUSTOMVERTEX  treevertex2[4]
	{
		{ -TREE_W / 2, -TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 0.f, 0.f },
		{ TREE_W / 2, -TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 1.f, 0.f },
		{ TREE_W / 2,  TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 1.f, 1.f },
		{ -TREE_W / 2,  TREE_H / 2, 1.f, 1.f, 0xFFFFFFFF, 0.f, 1.f }
	};
	//位置と頂点情報を代入
	for (int i = 0; i < 4; i++)
	{
		drawtree2[i] = treevertex2[i];
		drawtree2[i].x += tree2.x;
		drawtree2[i].y += tree2.y;
	}
}