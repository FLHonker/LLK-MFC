/*
@title:GameDlg.h
@author:Frank Liu
@time:2017-6-7
*/
#pragma once
#include "afxwin.h"
#include "GameControl.h"
#include "GameHelp.h"


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(int gModel, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	HICON m_hIcon;       // 对话框图标
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();        // WM_PAINT 消息函数 
	virtual BOOL OnInitDialog();   // 窗口初始化函数 
	void InitElement(void);        // 初始化元素图片与DC
	void DrawTipFrame(int nRow, int nCol);   // 绘制矩形提示框
	void DrawTipLine(Vertex asvPath[PathLen], int nVexnum);   //绘制提示Line

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CDC m_dcMem;         // 内存DC
	CDC m_dcBG;          // 背景DC
	CDC m_dcElement;     // 元素内存DC
	CDC m_dcMask;        // 掩码内存DC
	CPoint m_ptGameTop;   // 游戏区起始点（游戏第一张图片的顶点坐标, 坐标相对于窗口客户区） 
	CSize m_sizeElem;     // 元素图片的大小
	CRect m_rtGameRect;     // 游戏区域大小(该区域为游戏更新区域大小，考虑到后面画的线，可能会超出图片区域一定范围)
	CGameControl m_GameC;   // 游戏控制类对象
	CProgressCtrl *pProgCtrl;   //进度条指针
	CStatic *pStaticTime;       // "剩余时间"静态文本指针
	CStatic *pStaticLevel;      // "当前关卡"静态文本指针
	bool m_bFirstPoint;     // 是否是第一个选中的点
	bool m_bPlaying;		// 游戏状态标识
	int nRerank;			// 重排次数
	int extraTime;          // 游戏剩余时间
	int gameModel;          // 游戏模式位，0=基本模式，1=休闲模式，2=关卡模式
	int level;				//关卡等级

	void InitBackground();  // 初始化窗口背景
	void UpdateGameRect();     //更新游戏区域背景
	void UpdateWindow();    // 更新界面
	void UpdateMap();       // 更新游戏地图
	void LevelModelSupt();  // 关卡模式控制支持
public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnTip();
	afx_msg void OnBnClickedBtnRerank();
	afx_msg void OnBnClickedBtnHelp();
};
