/*
@title:LLK.h
@author:Frank Liu
@time:2017-6-7
*/

// LLKDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "GameDlg.h"

class CLianliankanDlgAutoProxy;


// CLLKDlg 对话框
class CLLKDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLLKDlg);
	friend class CLianliankanDlgAutoProxy;

// 构造
public:
	CLLKDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CLLKDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIANLIANKAN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CLianliankanDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	HCURSOR OnQueryDragIcon();

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP();
	CDC m_dcMem;   // 表示背景位图内存
public:
	afx_msg void OnBnClickedBtnBasic();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnBnClickedBtnRank();
	afx_msg void OnBnClickedBtnRelax();
	afx_msg void OnBnClickedBtnLevel();
private:
	CGameDlg *m_pGameDlg;    //游戏对话框
	void InitBackground();     // 初始化背景的方法，将位图选入位图内存。 
	void UpdateWindow(void);  // 更新界面
};