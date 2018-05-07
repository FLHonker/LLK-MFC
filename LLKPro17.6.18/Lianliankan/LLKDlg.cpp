/*
@title:LLK.cpp
@author:Frank Liu
@time:2017-6-7
*/

// LLKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "LLKDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "GameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg 对话框

IMPLEMENT_DYNAMIC(CLLKDlg, CDialogEx);

CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIANLIANKAN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_APP_ICON);
	m_pAutoProxy = NULL;

}

CLLKDlg::~CLLKDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
	// 如果非模态对话框已经创建则删除它   
	if (!m_pGameDlg)
	{
		// 删除非模态对话框对象   
		delete m_pGameDlg;
	}
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnBnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CLLKDlg::OnBnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &CLLKDlg::OnBnClickedBtnLevel)
	ON_BN_CLICKED(IDB_BTN_SETTING, &CLLKDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDB_BTN_HELP, &CLLKDlg::OnBnClickedBtnHelp)
	ON_BN_CLICKED(IDB_BTN_RANK, &CLLKDlg::OnBnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CLLKDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CLLKDlg 消息处理程序

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitBackground();       //加载背景图

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLLKDlg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{          
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);   // 绘制背景图片 

		CDialogEx::OnPaint();   //原来自带的父类函数
	}
}

// 初始化背景的方法，将位图选入位图内存。
void CLLKDlg::InitBackground()
{
	UpdateWindow();   //更新窗口大小和位置

	// 获得当前对话框的视频内存    
	CClientDC dc(this);
	// 创建与视频内存兼容的内存 DC     
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackgrd;
	bmpBackgrd.LoadBitmap(IDB_MAIN_BG0);
	// 将位图资源选入 DC    
	m_dcMem.SelectObject(bmpBackgrd);
	/*
	CRect rc;
	GetClientRect(&rc);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpPri = m_dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &m_dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	dc.SelectObject(pbmpPri);
	*/
}

void CLLKDlg::UpdateWindow(void)
{
	// 调整窗口大小    
	CRect rtWin;
	CRect rtClient;

	this->GetWindowRect(rtWin);       // 获得窗口大小     
	this->GetClientRect(rtClient);    // 获得客户区大小  

	// 标题栏和外边框的大小     
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();

	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);  // 设置窗口大小  
	CenterWindow();     // 设置对话框显示在桌面中央

}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。 这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CLLKDlg::OnClose()
{
	/*
	if (CanExit())
		CDialogEx::OnClose();
	*/
	if (CanExit() && MessageBox(_T("确实要退出吗？"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		CDialog::OnClose();
	}
}

void CLLKDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CLLKDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CLLKDlg::OnBnClickedBtnBasic()    //基本模式
{
	/*
	//模态game对话框显示
	CGameDlg gamedlg;  // 构造对话框类CTipDlg的实例
	INT_PTR nRes = gamedlg.DoModal();     // 弹出对话框，并保存DoModal函数的返回值 
	if (IDCANCEL == nRes)      // 判断对话框退出后返回值是否为IDCANCEL，如果是则 return，否则继续向下执行
		return;   
	//CWnd::ShowWindow(SW_HIDE);
	*/

	// 创建非模态对话框实例 
	m_pGameDlg = new CGameDlg(0, this);
	m_pGameDlg->Create(IDD_GAME_DIALOG, this);
	// 显示非模态对话框 
	m_pGameDlg->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedBtnRelax()  //休闲模式
{;
	// 创建非模态对话框实例 
	m_pGameDlg = new CGameDlg(1, this);     //模式位设为1（休闲模式）
	m_pGameDlg->Create(IDD_GAME_DIALOG, this);	
	// 显示非模态对话框 
	m_pGameDlg->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedBtnLevel()  //关卡模式
{
	// 创建非模态对话框实例 
	m_pGameDlg = new CGameDlg(2, this);	  //模式位设为2（关卡模式）
	m_pGameDlg->Create(IDD_GAME_DIALOG, this);

	//各种关卡模式下的界面调整和初始化

	// 显示非模态对话框 
	m_pGameDlg->ShowWindow(SW_SHOW);
}

void CLLKDlg::OnBnClickedBtnExit()  //退出游戏
{
	if (MessageBox(_T("确实要退出吗？"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		CDialog::OnCancel();
	}
}


void CLLKDlg::OnBnClickedBtnRank()  //排行榜按钮
{

}

void CLLKDlg::OnBnClickedBtnSetting()  //设置按钮
{

}

void CLLKDlg::OnBnClickedBtnHelp()   //帮助按钮
{
	//创建并模态显示“帮助”对话框
	CGameHelp gameHelpDlg;
	gameHelpDlg.DoModal();
}