
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "DlgProxy.h"
#include "LLKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLianliankanDlgAutoProxy

IMPLEMENT_DYNCREATE(CLianliankanDlgAutoProxy, CCmdTarget)

CLianliankanDlgAutoProxy::CLianliankanDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CLLKDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CLLKDlg)))
		{
			m_pDialog = reinterpret_cast<CLLKDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CLianliankanDlgAutoProxy::~CLianliankanDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CLianliankanDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLianliankanDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLianliankanDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_ILianliankan 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {2FFE508F-46E5-49AC-AFCE-245C24812F75}
static const IID IID_ILianliankan =
{ 0x2FFE508F, 0x46E5, 0x49AC, { 0xAF, 0xCE, 0x24, 0x5C, 0x24, 0x81, 0x2F, 0x75 } };

BEGIN_INTERFACE_MAP(CLianliankanDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLianliankanDlgAutoProxy, IID_ILianliankan, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {BDC3A4DA-E97E-49F0-9184-F8A386CFBF52}
IMPLEMENT_OLECREATE2(CLianliankanDlgAutoProxy, "Lianliankan.Application", 0xbdc3a4da, 0xe97e, 0x49f0, 0x91, 0x84, 0xf8, 0xa3, 0x86, 0xcf, 0xbf, 0x52)


// CLianliankanDlgAutoProxy 消息处理程序
