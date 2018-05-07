#pragma once


// CGameHelp 对话框

class CGameHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CGameHelp)

public:
	CGameHelp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameHelp();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Help_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
