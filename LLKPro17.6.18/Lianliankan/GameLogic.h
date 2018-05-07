/*
@title:GameLogic.h
@author:Frank Liu
@time:2017-6-7
*/
#pragma once
#include "global.h"
#include "GameException.h"
#define PathLen 4

/*根据不同的数据结构，完成数据逻辑的判断功能*/
class CGameLogic
{
private: 
	Vertex m_avPath[PathLen];  // 保存在进行连接判断时所经过的关键顶点
	int m_nVexNum;       // 顶点数
protected:
	bool LinkInRow(int** pGameMap, Vertex v1, Vertex v2);	 // 判断横向是否连通 
	bool LinkInCol(int** pGameMap, Vertex v1, Vertex v2);	 // 判断纵向是否连通
	bool OneCornerLink(int** pGameMap, Vertex v1, Vertex v2);    // 一个拐点2条线连通判断
	bool TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2);    // 2个拐点3条直线消子判断
	bool LineX(int** pGameMap, int nRow, int nCol1, int nCol2);  // 直线连通 X 轴
	bool LineY(int** pGameMap, int nRow1, int nRow2, int nCol);  // 直线连通 Y 轴
	void PushVertex(Vertex v);		// 添加一个路径顶点 
	Vertex PopVertex();			    // 取出一个顶点
	void ClearStack();				// 清除栈
public:
	CGameLogic();
	~CGameLogic();
	int** InitMap();         // 初始化游戏地图 
	void ReleaseMap(int** &pGameMap);  // 释放地图
	void RerankGraph(int** pGameMap);         //重排地图元素数据
	bool IsLink(int** pGameMap, Vertex v1, Vertex v2);  // 判断是否连通
	void Clear(int** pGameMap, Vertex v1, Vertex v2);   // 消子 
	int GetVexPath(Vertex avPath[PathLen]);		 // 得到路径，返回的是顶点数
	//bool IsBlank(int** pGameMap);              // 判断图中顶点是不是全为空，需要遍历二维地图数组，效率低
};