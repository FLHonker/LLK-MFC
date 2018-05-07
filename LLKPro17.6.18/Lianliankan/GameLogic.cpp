/*
@title:GameLogic.cpp
@author:Frank Liu
@time:2017-6-7
*/

#include "stdafx.h"
#include "GameLogic.h"
#include "GameControl.h"

CGameLogic::CGameLogic()
{
	m_nVexNum = 0;
}


CGameLogic::~CGameLogic()
{
}

/* 初始化游戏地图 */
int** CGameLogic::InitMap()
{
	// 获取地图大小和花色  
	int nRows = CGameControl::s_nRows; 
	int nCols = CGameControl::s_nCols;  
	int nPicNum = CGameControl::s_nPicNum; 

	// 游戏地图开辟内存空间   
	int** pGameMap = new int*[nRows + 2];  
	if(NULL == pGameMap)  
	{   
		throw new CGameException(_T("内存操作异常！"));  
	} 
	else  
	{
		for (int i = 0; i < nRows + 2; i++)   
		{    
			pGameMap[i] = new int[nCols + 2]; 
			if(NULL == pGameMap) 
			{     
				throw new CGameException(_T("内存操作异常！"));   
			}   
			memset(pGameMap[i], BLANK, sizeof(int) * (nCols + 2));  //初始化数组为BLANK(-1)
		}  
	}
	
	// 多少花色, 根据花色的种类计算出每种花色的图片的平均个数，依次给数组赋值。   
	if ((nRows * nCols) % (nPicNum * 2) != 0)  
	{  
		ReleaseMap(pGameMap);   
		throw new CGameException(_T("游戏花色与游戏地图大小不匹配！"));
	}  
	int nRepeatNum = nRows * nCols / nPicNum;
	int nCount = 0; 
	for(int i = 0; i < nPicNum; i++) 
	{   
		for(int j = 0; j < nRepeatNum; j++)  // 重复数
		{    
			pGameMap[nCount / nCols + 1][nCount % nCols + 1] = i;   
			nCount++; 
		}
	} 

	/* 随机找到两个位置的图片，进行交换 */

	srand((int)time(NULL));   // 设置种子  

	// 随机任意交换两个数字  
	int nVertexNum = nRows * nCols;  
	for(int i = 0; i < nVertexNum; i++)  
	{  
		// 随机得到两个坐标  
		int nIndex1 = rand() % nVertexNum; 
	    int nIndex2 = rand() % nVertexNum;

		// 交换两个数值   
		int nTmp = pGameMap[nIndex1 / nCols + 1][nIndex1 % nCols + 1];   
		pGameMap[nIndex1 / nCols + 1][nIndex1 % nCols + 1] = pGameMap[nIndex2 / nCols + 1][nIndex2 % nCols + 1];  
		pGameMap[nIndex2 / nCols + 1][nIndex2 % nCols + 1] = nTmp;  
	} 

	return pGameMap;
}

/* 释放游戏地图指针 */
void CGameLogic::ReleaseMap(int**& pGameMap)
{ 
	for (int i = 0; i < CGameControl::s_nRows + 2; i++) 
	{ 
			delete[] pGameMap[i]; 
	} 
	delete[] pGameMap;
	
	//delete pGameMap;
}

/* 重排游戏地图数据，交换任意两个非空的地图元素100次 */
void CGameLogic::RerankGraph(int** pGameMap)
{
	// 获取地图大小
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;

	/* 随机找到两个位置的图片，进行交换 */

	srand((int)time(NULL));   // 设置种子  

	// 随机任意交换两个数字  
	int nVertexNum = nRows * nCols;
	for (int i = 0; i < 100; i++)     //交换100次
	{
		int x1, y1, x2, y2;     //x,y坐标
		/*
		do {
			// 随机得到第一个坐标  
			int nIndex1 = rand() % nVertexNum;
			x1 = nIndex1 / nCols; y1 = nIndex1 % nCols;
		} while (pGameMap[x1][y1] != BLANK);   //直到第一个元素数据不为空
		
		do {
			// 随机得到第二个坐标  
			int nIndex2 = rand() % nVertexNum;
			x2 = nIndex2 / nCols; y2 = nIndex2 % nCols;
		} while (pGameMap[x2][y2] != BLANK);	//直到第二个元素数据不为空
		*/
		//随机生成2个地图元素坐标
		int nIndex1 = rand() % nVertexNum;
		int nIndex2 = rand() % nVertexNum;
		x1 = nIndex1 / nCols + 1; y1 = nIndex1 % nCols + 1;
		x2 = nIndex2 / nCols + 1; y2 = nIndex2 % nCols + 1;

		int nTmp = pGameMap[x1][y1];
		pGameMap[x1][y1] = pGameMap[x2][y2];
		pGameMap[x2][y2] = nTmp;
	}
}

/*关键点入栈*/
void CGameLogic::PushVertex(Vertex v)
{
	if(m_nVexNum <= PathLen)
		m_avPath[m_nVexNum++] = v;
}

/*关键点出栈*/
Vertex CGameLogic::PopVertex()
{
	Vertex retPop = { BLANK,BLANK,BLANK };
	if (m_nVexNum > 0)
	{
		retPop = m_avPath[m_nVexNum];
		m_avPath[m_nVexNum--] = { BLANK,BLANK,BLANK };
	}
	return retPop;
}

/*清空栈*/
void CGameLogic::ClearStack()
{
	for (; m_nVexNum > 0; m_nVexNum--)
	{
		m_avPath[m_nVexNum - 1] = { BLANK,BLANK,BLANK };
	}
}

/* 行号相同时，判断横向是否连通
 * 算法：从 nCol1 + 1 遍历到 nCol2，判断这条直线上是否都为空白区域。如果全为空白区域，则横向连通。
*/
bool CGameLogic::LinkInRow(int **pGameMap, Vertex v1, Vertex v2)
{
	int nCol1 = v1.col; 
	int nCol2 = v2.col; 
	int nRow = v1.row;
	//如果两元素处在边缘行，则可以直接消除，无需判断是否可以直通
	//if (nRow == 0 || nRow == CGameControl::s_nRows-1)
		//return true;
	//保证 nCol1 的值小于 nCol2 
	if(nCol1 > nCol2) 
	{   //数据交换   
		int nTemp = nCol1;   
		nCol1 = nCol2;  
		nCol2 = nTemp; 
	} 
	 //直通   
	for(int i = nCol1 + 1; i <= nCol2; i++)  
	{  
		if(i == nCol2) 
			return true;  
		if(pGameMap[nRow][i] != BLANK)  
			break;  
	}
	return false;
}

/* 列号相同时，判断能否纵向连通
 * 算法：从 nRow1 + 1 遍历到 nRow2，判断这条直线上是否全为空白区域。如果全为空白 区域，则纵向连通。 
 */
bool CGameLogic::LinkInCol(int** pGameMap, Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row; 
	int nCol = v1.col; 
	//如果两元素处在边缘列，则可以直接消除，无需判断是否可以直通
	//if (nCol == 0 || nCol == CGameControl::s_nCols-1)
		//return true;
	//保证nRow1的值小于nRow2
	if (nRow1 > nRow2)
	{ 
		int nTemp = nRow1;  
		nRow1 = nRow2;  
		nRow2 = nTemp; 
	} 
	//直通  
	for(int i = nRow1+1; i <= nRow2; i++)
	{   
		if(i == nRow2)  
			return true;
		if(pGameMap[i][nCol] != BLANK)
			break;  
	} 
	return false;
}

/*判断横向是否连通*/
bool CGameLogic::LineX(int** pGameMap, int nRow, int nCol1, int nCol2)
{
	//保证 nCol1 的值小于 nCol2 
	if (nCol1 > nCol2)
	{   //数据交换   
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}
	//直通   
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
			return true;
		if (pGameMap[nRow][i] != BLANK)
			break;
	}
	return false;
}

bool CGameLogic::LineY(int** pGameMap, int nRow1, int nRow2, int nCol)
{
	//保证 nRow1 的值小于 nRow2 
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	//直通  
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (pGameMap[i][nCol] != BLANK)
			break;
	}
	return false;
}

/*一个拐点，2条线实消子判断*/
bool CGameLogic::OneCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	// 直角能够消子，那么顶点一定在与两个点的行和列相交的点，只有这两个点为空，才有可能实现二条直线消子 
	if (pGameMap[v1.row][v2.col] == BLANK)
	{ 
		if (LineY(pGameMap, v1.row, v2.row, v2.col) && LineX(pGameMap, v1.row, v1.col, v2.col))
		{
			Vertex v = { v1.row, v2.col, BLANK };   
			PushVertex(v);   
			return true; 
		}
	}    
	if (pGameMap[v2.row][v1.col] == BLANK)
	{
		if (LineY(pGameMap, v1.row, v2.row, v1.col) && LineX(pGameMap, v2.row, v1.col, v2.col))
		{
			Vertex v = { v2.row, v1.col, BLANK };  
			PushVertex(v);  
			return true;
		}
	}
	return false;
}

/*2个拐点，3条线消子判断*/
bool CGameLogic::TwoCornerLink(int** pGameMap, Vertex v1, Vertex v2)
{
	for (int nCol = 0; nCol < CGameControl::s_nCols + 2; nCol++)
	{
		// 找到一条与 Y 轴平行的连通线段  
		if (pGameMap[v1.row][nCol] == BLANK && pGameMap[v2.row][nCol] == BLANK)
		{
			if (LineY(pGameMap, v1.row, v2.row, nCol))
			{
				if (LineX(pGameMap, v1.row, v1.col, nCol) && LineX(pGameMap, v2.row, v2.col, nCol))
				{
					// 保存节点     
					Vertex vx1 = { v1.row, nCol, BLANK };
					Vertex vx2 = { v2.row, nCol, BLANK };
					PushVertex(vx1);
					PushVertex(vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < CGameControl::s_nRows + 2; nRow++)
	{  
		// 找到一条与 X 轴平行的连通线段  
		if(pGameMap[nRow][v1.col] == BLANK && pGameMap[nRow][v2.col] == BLANK)  
		{ 
			if(LineX(pGameMap, nRow, v1.col, v2.col))  
			{  
				if(LineY(pGameMap, nRow, v1.row, v1.col) && LineY(pGameMap, nRow, v2.row, v2.col)) 
				{   
					// 保存节点      
					Vertex vx1 = { nRow, v1.col, BLANK };
					Vertex vx2 = { nRow, v2.col, BLANK };
					PushVertex(vx1);    
					PushVertex(vx2);    
					return true;    
				}  
			}  
		} 
	} 
	return false;
}

/* 判断是否可以连接 */
bool CGameLogic::IsLink(int** pGameMap, Vertex v1, Vertex v2)
{
	ClearStack();	// 清空栈
	PushVertex(v1);

	bool isLink = false;
	if (v1.row == v2.row)
	{
		if (LinkInRow(pGameMap, v1, v2))  // X 直连方式  
			isLink = true;
		else if (TwoCornerLink(pGameMap, v1, v2))
			isLink = true;
	}
	else if (v1.col == v2.col)  // Y 直连方式 
	{
		if (LinkInCol(pGameMap, v1, v2))
			isLink = true;
		else if (TwoCornerLink(pGameMap, v1, v2))
			isLink = true;
	}
	else if (OneCornerLink(pGameMap, v1, v2))   //一拐点，2条线
	{
		isLink = true;
	}
	else if (TwoCornerLink(pGameMap, v1, v2))   //2拐点，3条线
	{
		isLink = true;
	}
	PushVertex(v2);
	return isLink;
}

/* 消子，将地图数组对应点置为BLANK（-1）*/
void CGameLogic::Clear(int** pGameMap, Vertex v1, Vertex v2)
{
	pGameMap[v1.row][v1.col] = BLANK;
	pGameMap[v2.row][v2.col] = BLANK;
}

/* 获取连接路径：通过参数返回路径，通过返回值返回数组中实际元素个数 */
int CGameLogic::GetVexPath(Vertex avPath[PathLen])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}
