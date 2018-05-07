/*
@title:GameDlg.cpp
@author:Frank Liu
@time:2017-6-7
*/

// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "Lianliankan.h"
#include "GameDlg.h"
#include "mmsystem.h"
#define  ProgCtrlMAX 120    //进度条最大值
#define  TimerOne    1      //定时器one

// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(int gModel, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_APP_ICON);
	EnableAutomation();

	m_ptGameTop.Offset(1, 45);   //游戏区起始顶点坐标
	m_sizeElem.SetSize(40, 40);   //设置游戏图片大小
	//根据游戏区起始顶点坐标和游戏图片元素大小计算，设置游戏区域边界
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.bottom = m_ptGameTop.y + m_sizeElem.cy * (CGameControl::s_nRows + 2);
	m_rtGameRect.right = m_ptGameTop.x + m_sizeElem.cx * (CGameControl::s_nCols + 2);
	m_bFirstPoint = true;    //bool初始化
	m_bPlaying = false;      //游戏未在进行状态
	nRerank = 3;			//重排剩余次数初始化为3次
	extraTime = ProgCtrlMAX;   //剩余时间初始化为120s
	gameModel = gModel;			//游戏模式位初始化，默认为“基本模式”
	level = 1;              //关卡等级初始化为1级
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnBnClickedBtnStart)
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_Rerank, &CGameDlg::OnBnClickedBtnRerank)
	ON_BN_CLICKED(IDC_BTN_Stop, &CGameDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_Tip, &CGameDlg::OnBnClickedBtnTip)
	ON_BN_CLICKED(IDB_BTN_HELP, &CGameDlg::OnBnClickedBtnHelp)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGameDlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IGameDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {F497B997-B536-44C5-830B-FD433615F5F0}
static const IID IID_IGameDlg =
{ 0xF497B997, 0xB536, 0x44C5, { 0x83, 0xB, 0xFD, 0x43, 0x36, 0x15, 0xF5, 0xF0 } };

BEGIN_INTERFACE_MAP(CGameDlg, CDialogEx)
	INTERFACE_PART(CGameDlg, IID_IGameDlg, Dispatch)
END_INTERFACE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::OnPaint()
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
		//CPaintDC dc(this);    // 创建 CPaintDC 对象           
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBG, 0, 0, SRCCOPY);   // 绘制背景图片
		if (m_bPlaying)    //如果游戏处于开始状态，则需要重绘游戏地图，主要是为了窗口最小化还原后可以自动重绘元素
			UpdateMap();    //如果是刚进入游戏界面，还没有点击“开始游戏”，则不需要加载游戏地图
		CDialogEx::OnPaint();   //原来自带的父类函数
	}
}

BOOL CGameDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);	    // 设置大图标
	SetIcon(m_hIcon, TRUE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	InitBackground();   //加载背景图片
	InitElement();     //初始化游戏图片元素
	// 初始化进度条
	pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS_TIME);
	pProgCtrl->SetRange(0, ProgCtrlMAX);    //设置进度条范围  
	//pProgCtrl->SetPos(ProgCtrlMAX);			//设置进度条当前位置为最大值
	//静态文本指针定位
	pStaticTime = (CStatic*)GetDlgItem(IDC_extraTimeText);	  
	pStaticLevel = (CStatic*)GetDlgItem(IDC_STATIC_Level);    
	CString title;    //对话框标题文本
	//休闲模式下隐藏时间进度条和时间提示文本,修改对话框标题
	if (gameModel == 1)
	{
		pProgCtrl->ShowWindow(SW_HIDE);
		pStaticTime->ShowWindow(SW_HIDE);
		title = "卡通连连看-休闲模式";
		SetWindowText(title);
	}
	else if (gameModel == 2)
	{
		title = "卡通连连看-关卡模式";
		SetWindowText(title);
		LevelModelSupt();	    //关卡模式的相关控制支持
	}
		
	return TRUE;    // 除非将焦点设置到控件，否则返回 TRUE
}

/* 关闭对话框，弹出确认框 */
void CGameDlg::OnClose()
{
	if (MessageBox(_T("确实要退出吗？"), _T("提示"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
	{
		PlaySound(NULL, NULL, SND_FILENAME);    //停止播放背景音乐
		m_GameC.s_nPicNum = 20;     //退出游戏界面时完成地图默认数据恢复
		CDialog::OnClose();
	}
}

void CGameDlg::InitElement()
{
	// 获得当前对话框的视频内存     
	CClientDC dc(this);
	// 加载 BMP 图片资源     
	HANDLE hBmp = ::LoadImageW(NULL, _T("res\\theme\\picture\\animals_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC 
	m_dcElement.CreateCompatibleDC(&dc); 
	// 将位图资源选入 DC     
	m_dcElement.SelectObject(hBmp);

	// 加载掩码 BMP 图片资源   
	HANDLE hMask = ::LoadImageW(NULL, _T("res\\theme\\picture\\animals_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC     
	m_dcMask.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC     
	m_dcMask.SelectObject(hMask);
}

// 初始化背景的方法，将位图选入位图内存。
void CGameDlg::InitBackground()
{
	UpdateWindow();
	/* 静态加载游戏背景
	// 获得当前对话框的视频内存    
	CClientDC dc(this);
	// 创建与视频内存兼容的内存 DC     
	m_dcBG.CreateCompatibleDC(&dc);
	CBitmap bmpGameBG;
	bmpGameBG.LoadBitmap(IDB_GAME_BG1);
	// 将位图资源选入 DC    
	m_dcBG.SelectObject(bmpGameBG);
	*/

	//根据游戏模式选择加载的背景图片
	CString bkgPath("res\\theme\\gamebkg (2).bmp");
	if (gameModel == 1)
		bkgPath = "res\\theme\\gamebkg (5).bmp";
	else if (gameModel == 2)
		bkgPath = "res\\theme\\gamebkg (3).bmp";
	// 动态方法
	// 获得当前对话框的视频内存    
	CClientDC dc(this);
	// 动态方法加载游戏背景图片资源   
	HANDLE hBackG = ::LoadImageW(NULL, bkgPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 创建与视频内存兼容的内存 DC     
	m_dcBG.CreateCompatibleDC(&dc);
	// 将位图资源选入 DC     
	m_dcBG.SelectObject(hBackG);
}

/*重绘游戏区域背景，用于界面刷新*/
void CGameDlg::UpdateGameRect()
{
	// 获得当前对话框的视频内存    
	CClientDC dc(this);
	//重绘矩形游戏区域背景
	dc.StretchBlt(m_ptGameTop.x, m_ptGameTop.y, m_rtGameRect.right- m_rtGameRect.left, m_rtGameRect.bottom- m_rtGameRect.top, &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.right - m_rtGameRect.left, m_rtGameRect.bottom - m_rtGameRect.top, SRCCOPY);  
}

// 更新窗口
void CGameDlg::UpdateWindow()
{
	// 调整窗口大小     
	CRect rtWin;    
	CRect rtClient;     
	this->GetWindowRect(rtWin);       // 获得窗口大小 
	this->GetClientRect(rtClient);    // 获得客户区大小 

	// 标题栏和外边框的大小     
	int nSpanWidth = rtWin.Width() - rtClient.Width();     
	int nSpanHeight = rtWin.Height() - rtClient.Height(); 

	// 设置窗口大小     
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight); 

	// 设置对话框显示在 windows 窗口正中央。
	CenterWindow();
}

// 更新游戏地图
void CGameDlg::UpdateMap()
{
	UpdateGameRect();   //重绘矩形游戏区域背景

	// 获取地图行数、列数和图片数  
	int nRows = CGameControl::s_nRows;
	int nCols = CGameControl::s_nCols;
	int nPicNum = CGameControl::s_nPicNum;

	// 计算图片的顶点坐标与图片大小
	int nLeft = m_ptGameTop.x, nTop = m_ptGameTop.y;	 //游戏区起始顶点坐标
	int nElemW = m_sizeElem.cx, nElemH = m_sizeElem.cy;   //图片高度和宽度像素
	
	CClientDC dcGame(this);
	for (int i = 1; i < nRows + 1; i++) {
		for (int j = 1; j < nCols + 1; j++) {   
			// 得到图片编号的值   
			int nElemVal = m_GameC.GetElement(i, j); 
			if (nElemVal != BLANK)    //如果已被置为BLANK(-1)，则跳过
			{
				// 将背景与掩码相或，边保留，图像区域为 1            
				//dcGame.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, SRCPAINT); 
				dcGame.StretchBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nElemVal * nElemH, nElemW, nElemH, SRCPAINT);

				// 与元素图片相与，边保留，图像区域为元素图片           
				//dcGame.BitBlt(nLeft + j * nElemW, nTop + i * nElemH , nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, SRCAND);
				dcGame.StretchBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nElemVal * nElemH, nElemW, nElemH, SRCAND);
			}
		}
	} 
}

//鼠标左击事件
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_bPlaying)    //如果游戏未在进行，不响应鼠标事件
		return;
	// 判断鼠标点击的区域  
	if(point.y < m_rtGameRect.top + m_sizeElem.cy || point.y > m_rtGameRect.bottom - m_sizeElem.cy || point.x < m_rtGameRect.left + m_sizeElem.cx || point.x > m_rtGameRect.right - m_sizeElem.cx)
	{  
		return CDialogEx::OnLButtonUp(nFlags, point); 
	} 
	int nRow = (int)(point.y - m_rtGameRect.top) / m_sizeElem.cy;    //点击位置所在行号
	int nCol = (int)(point.x - m_rtGameRect.left) / m_sizeElem.cx;   //点击位置所在列号

	if (m_GameC.GetElement(nRow, nCol) != BLANK)   // 若未被消除则选中
	{
		if (m_bFirstPoint)  // 第一个点  
		{
			DrawTipFrame(nRow, nCol);     //绘制第一个矩形提示框
			m_GameC.SetFirstPoint(nRow, nCol);   //设置选中的第一个点的记录
			m_bFirstPoint = false;
		}
		else               // 第二个点
		{
			DrawTipFrame(nRow, nCol);     //绘制第二个矩形提示框
			m_GameC.SetSecPoint(nRow, nCol);   //设置选中的第二个点的记录

			// 连子判断  
			Vertex avPath[PathLen];
			int nVexnum = 0;
			bool bSuc = m_GameC.Link(avPath, nVexnum);
			if (bSuc == true)
			{
				DrawTipLine(avPath, nVexnum);    // 画提示线  
				Sleep(200);     //暂停200ms，避免一闪而过
				extraTime += 10;      //消除一对后剩余时间加10s
				//PlaySound(_T("res\\music\\cut2.wav"), NULL, SND_FILENAME | SND_ASYNC );   // 播放消除声音
				if (m_GameC.IsWin())
				{
					CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_START);   //按钮指针指向IDC_BTN_START这个按钮 
					pBtn->EnableWindow(TRUE);    // "开始游戏"按钮设为可用
					KillTimer(TimerOne);
					if(gameModel!=2)
						MessageBox(_T("You are the winner!!!"), _T("Successful"), MB_OK);   //弹窗提醒玩家胜利！
					else           
					{
						level++;      //关卡加1
						LevelModelSupt();      //完成下一关卡的准备工作
						//关卡模式下，弹窗提醒玩家继续！
						MessageBox(_T("You win in this level!\n Please go on!"), _T("Go on！"), MB_OK);
					}
				}
			}
			UpdateMap();      // 更新地图
			m_bFirstPoint = !m_bFirstPoint;   //重置
		}
	}
}

/*绘制矩形提示框 */
void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	int recX = nCol*m_sizeElem.cx + m_rtGameRect.left;   //矩形左上角X坐标
	int recY = nRow*m_sizeElem.cy + m_rtGameRect.top;    //矩形左上角Y坐标
	CPoint topLeft(recX, recY);     //绘制矩形的左上角坐标
	CPoint rightBottom(recX + m_sizeElem.cx, recY + m_sizeElem.cy);   //绘制矩形的右下角坐标
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(233, 43, 43));    //定义钢笔属性、颜色（红色）
	CPen *pOldPen = dc.SelectObject(&pen);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *pOldBrush = dc.SelectObject(pBrush);
	dc.Rectangle(CRect(topLeft, rightBottom));
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

/* 绘制提示Line */
void CGameDlg::DrawTipLine(Vertex asvPath[PathLen], int nVexnum)
{
	CClientDC dc(this);   //获得当前视频内存
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));   //定义画笔属性、颜色（浅绿色）
	CPen* pOldPen = dc.SelectObject(&penLine);   //将画笔选入视频内存

	dc.MoveTo(m_ptGameTop.x + asvPath[0].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);  //画笔定位

	for (int i = 1; i < nVexnum; i++)    // 从起始点逐个顶点画线连接至终点
	{
		dc.LineTo(m_ptGameTop.x + asvPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2, m_ptGameTop.y + asvPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

/*开始游戏按钮事件*/
void CGameDlg::OnBnClickedBtnStart()  
{
	m_GameC.StartGame();
	/*初始化游戏图片元素，不能放在这里！重复点击“开始游戏”按钮会重复
	 *加载CDC位图内存，触发中断。并不知道原因。 */
	UpdateMap();     //更新地图，加载游戏图片
	pProgCtrl->SetPos(extraTime);    //设置进度条初始位置
	m_bPlaying = true;                 //游戏进行状态
	if (gameModel != 1)             //只要不是休闲模式就设定定时器
		SetTimer(TimerOne, 1000, NULL);     //定时器，每1s触发一次OnTimer()
	nRerank = 3;                    //重排次数置为3次
	sndPlaySound(_T("res\\music\\gamemusic.wav"), SND_FILENAME | SND_ASYNC | SND_LOOP);  //异步播放背景音乐
	 //设置“开始游戏”按钮禁用
	CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_START);   //按钮指针指向IDC_BTN_START这个按钮 
	if (pBtn != NULL)
	{
		pBtn->EnableWindow(FALSE);  // True or False 
	}
}

/* “暂停/继续游戏”按钮事件 */
void CGameDlg::OnBnClickedBtnStop()
{
	m_bPlaying = !m_bPlaying;     //游戏状态切换
	CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_Stop);   //按钮指针指向IDC_BTN_Stop这个按钮 
	//根据游戏状态设置按钮上显示的文本
	if (m_bPlaying)
		pBtn->SetWindowTextW(_T("暂停游戏"));
	else
		pBtn->SetWindowTextW(_T("继续游戏"));
}

/* “提示”按钮事件，寻找可消子，绘制提示框和提示线 */
void CGameDlg::OnBnClickedBtnTip()
{
	if (!m_bPlaying)   //游戏进行时才有效
		return;
	Vertex avPath[PathLen];
	int nVexnum = 0;
	bool bSuc = m_GameC.Help(avPath, nVexnum);   
	if (bSuc == true)    	//如果可以生成提示
	{
		extraTime -= 30;         //规则：成功使用一次提示剩余时间减30s
		DrawTipLine(avPath, nVexnum);    // 画提示线，1遍 
		Sleep(300);     //暂停300ms，让玩家观察
		UpdateMap();    //刷新地图
		Sleep(300);     //暂停300ms，让玩家观察
		DrawTipLine(avPath, nVexnum);    // 画提示线，2遍
		Sleep(300);     //暂停300ms，让玩家观察
		UpdateMap();    //刷新地图
	}
	else
	{
		MessageBox(_T("Sorry,there are not links! \n May you have failured!"));   //弹窗提示找不到可消除的图片
	}
}

/* “重排”按钮事件，执行剩余地图元素的重排并刷新地图 */
void CGameDlg::OnBnClickedBtnRerank()
{
	if (m_bPlaying && nRerank > 0)   //只有游戏开始后有重排次数前提下才能重排
	{
		m_GameC.Rerank();   //重排地图元素
		UpdateMap();		//刷新地图
		nRerank--;          //重排次数减1
		CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_Rerank);   //按钮指针指向IDC_BTN_Rerank这个按钮 
		CString rankStr;
		rankStr.Format(_T("重 排 %d"), nRerank);
		pBtn->SetWindowTextW(rankStr);    //设置“重排”按钮文本
	}
}

/*定时器事件处理*/
void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bPlaying)    //如果游戏处于停止状态，则不进行进度条操作
		return;
	int m_nStep = 1;      //步长
	//extraTime = pProgCtrl->StepIt();		//取得更新前位置,即当前剩余时间 
	extraTime -= m_nStep;         //剩余时间递减
	pProgCtrl->SetPos(extraTime);    //更新进度位置
	CString timeStr;              //剩余时间字符串对象
	timeStr.Format(_T("剩余时间:%ds"), extraTime);   //格式化修改静态文本
	pStaticTime->SetWindowTextW(timeStr);       //设置静态文本内容

	if (extraTime <= 0)
	{
		KillTimer(TimerOne);      //卸载定时器
		CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_START);   //按钮指针指向IDC_BTN_START这个按钮 
		pBtn->EnableWindow(TRUE);    // "开始游戏"按钮设为可用
		if (MessageBox(_T("There is no time! \n Please again."), _T("Failure"), MB_OK) == IDOK)   //弹窗提醒玩家超时！
		{
			m_bPlaying = false;    //游戏置为停止状态
			level = 1;            //重置关卡等级
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

/* 关卡模式控制支持 */
void CGameDlg::LevelModelSupt()
{
	// 关卡文本显示控制
	pStaticLevel->ShowWindow(SW_SHOW);    //显示关卡静态文本
	CString levelStr;            //关卡字符串对象
	levelStr.Format(_T("关卡:%d"), level);   //格式化修改静态文本
	pStaticLevel->SetWindowTextW(levelStr);       //设置静态文本内容

	// 根据关卡设定进度条显示控制
	//根据关卡设置进度条时间
	if (ProgCtrlMAX - level * 5 > 24)
		extraTime = ProgCtrlMAX - level * 5;
	else
		extraTime = 24;
	pProgCtrl->SetRange(0, extraTime);    //设置进度条范围
	
	// 根据关卡设定游戏地图图片数量
	/*
	if (level == 1)
	{
		m_GameC.s_nRows = 5;
		m_GameC.s_nCols = 6;
		m_GameC.s_nPicNum = 3;
	}
	else if (level <= 9)
	{
		if (level % 2 == 1 || level % 4 == 0)
			m_GameC.s_nRows = 6 + level / 2;
		else
			m_GameC.s_nRows = 7 + level / 2;
		m_GameC.s_nCols = 6 + level;
		m_GameC.s_nPicNum = level + 6;
	}
	else if(level == 15)
	{
		m_GameC.s_nRows = 10;
		m_GameC.s_nCols = 16;
		m_GameC.s_nPicNum = 20;
	}
		//其余默认即可...
	*/
	if (level == 1 || level == 2)
		m_GameC.s_nPicNum = 2;
	else if (level >= 3 || level <= 5)
		m_GameC.s_nPicNum = 4;
	else if (level >= 6 || level <= 9)
		m_GameC.s_nPicNum = 8;
	else if (level >= 10 || level <= 12)
		m_GameC.s_nPicNum = 10;
	else if (level >= 13 || level <= 15)
		m_GameC.s_nPicNum = 16;
	else
		m_GameC.s_nPicNum = 20;
}

/* “帮助”按钮事件，弹出帮助对话框 */
void CGameDlg::OnBnClickedBtnHelp()
{
	//创建并模态显示“版主”对话框
	CGameHelp gameHelpDlg;
	gameHelpDlg.DoModal();
}
