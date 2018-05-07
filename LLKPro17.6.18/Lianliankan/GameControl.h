#pragma once
#include "GameLogic.h"


/* 保存游戏数据，统一协调和调用各逻辑类完成相应的功能 */
class CGameControl
{
private:
	int** m_pGameMap;		// 游戏地图数组指针 
    CGameLogic m_GameLogic;  // 游戏逻辑操作对象
	int clearPic;           //记录被消除的图片数，用于判断胜负

	Vertex m_svSelFst;     // 选中的第一个点
	Vertex m_svSelSec;     // 选中的第二个点
public:
	static int s_nRows;    // 游戏行数 
	static int s_nCols;    // 游戏列数 
	static int s_nPicNum;  // 图片数

	CGameControl();     //构造函数
	~CGameControl();    //析构函数，释放地图指针
	void StartGame(void);   // 开始游戏 
	int GetElement(int nRow, int nCol);   // 得到某一个元素
	void Rerank();		//对剩余图片元素重排
	void SetFirstPoint(int nRow, int nCol);     // 设置第一个点 
	void SetSecPoint(int nRow, int nCol);       // 设置第二个点
	bool Link(Vertex *avPath, int &nVexnum);   // 消子判断(路径暂定为4个顶点)
	bool SearchValidPath(Vertex *avPath, int &nVexnum); //寻找可消子的有效路径
	bool Help(Vertex *avPath, int &nVexnum);   //游戏消子提示
	bool IsWin(void);						  // 判断是否获胜
};
