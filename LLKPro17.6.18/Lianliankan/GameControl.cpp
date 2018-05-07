/*
@title:GameControl.cpp
@author:Frank Liu
@time:2017-6-7
*/

#include "stdafx.h"
#include "GameControl.h"


//静态成员变量初始化
int CGameControl::s_nRows = 10;
int CGameControl::s_nCols = 16;
int CGameControl::s_nPicNum = 20;

CGameControl::CGameControl()
{
	clearPic = 0;
}

CGameControl::~CGameControl()
{
	m_GameLogic.ReleaseMap(m_pGameMap);   //释放游戏地图数组指针
	//delete m_pGameMap; 
}

/*开始游戏*/
void CGameControl::StartGame(void)
{
	m_pGameMap = m_GameLogic.InitMap();    //初始化游戏地图

}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_pGameMap[nRow][nCol];   //返回游戏图片号
}

/* 重排地图元素 */
void CGameControl::Rerank()
{
	m_GameLogic.RerankGraph(m_pGameMap);    //对地图数组数据重排，并返回地址
}

/*设置第一个选中的点信息*/
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFst.row = nRow;
	m_svSelFst.col = nCol;
	m_svSelFst.info = m_pGameMap[nRow][nCol];
}

/*设置第二个选中的点信息*/
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
	m_svSelSec.info = m_pGameMap[nRow][nCol];
}

/*消子判断*/
bool CGameControl::Link(Vertex *avPath, int &nVexnum)
{
	// 判断是否同一张图片  
	if(m_svSelFst.row == m_svSelSec.row && m_svSelFst.col == m_svSelSec.col) 
	{  
		return false;  
	}  
	// 判断图片是否相同 
	if(m_pGameMap[m_svSelFst.row][m_svSelFst.col]!=m_pGameMap[m_svSelSec.row][m_svSelSec.col])
	{ 
		return false;  
	}  

	// 判断是否连通 
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec))
	{ 
		// 消子实现 
		m_GameLogic.Clear(m_pGameMap, m_svSelFst, m_svSelSec);
		clearPic += 2;     //以此消除2张图片，计数器加2
		// 返回路径顶点数  
		nVexnum = m_GameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

/* 寻找可消子的有效路径 */
bool CGameControl::SearchValidPath(Vertex *avPath, int &nVexnum)
{
	// 判断是否连通 
	if (m_GameLogic.IsLink(m_pGameMap, m_svSelFst, m_svSelSec))
	{
		nVexnum = m_GameLogic.GetVexPath(avPath);	 // 返回路径顶点数  
		return true;
	}
	return false;
}

/* 搜索可消除元素，返回是否可以生成提示 */
bool CGameControl::Help(Vertex *avPath, int &nVexnum)
{
	int x1, y1, x2, y2;
	for(x1 = 0; x1 < s_nRows; x1++)
		for (y1 = 0; y1 < s_nCols; y1++)
		{
			if (m_pGameMap[x1][y1] != BLANK)
			{
				SetFirstPoint(x1, y1);			  //设置第一个点
				for (x2 = x1; x2 < s_nRows; x2++)   //继续遍历剩余地图元素，寻找第二个点
					for (y2 = y1+1; y2 < s_nCols; y2++)
					{
						if (m_pGameMap[x2][y2] == m_pGameMap[x1][y1])  //如果两个点的图片相同
						{
							SetSecPoint(x2, y2);        //设置第二个点
							if (SearchValidPath(avPath, nVexnum))   //如果可以连通
								return true;
						}
					}
			}
		}

	return false;   //循环完成后还没找到可以消除的图片则返回false，由上一级做出判决
}

/*根据消除的图片数判定胜负*/
bool CGameControl::IsWin(void)
{
	/*如果消除的图片数与原有图片数相等，则判定玩家取胜；优化了每次遍历二维地图数组带来的时空复杂度*/
	if (clearPic == s_nRows*s_nCols)
	{
		clearPic = 0;   //重置计数器，为下一轮做准备
		return true;
	}
	else
		return false;
}
