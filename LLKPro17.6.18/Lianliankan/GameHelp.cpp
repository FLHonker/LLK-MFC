// GameHelp.cpp : 实现文件
//

#include "stdafx.h"
#include "Lianliankan.h"
#include "GameHelp.h"
#include "afxdialogex.h"


// CGameHelp 对话框

IMPLEMENT_DYNAMIC(CGameHelp, CDialogEx)

CGameHelp::CGameHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Help_DIALOG, pParent)
{

	EnableAutomation();

}

CGameHelp::~CGameHelp()
{
}

void CGameHelp::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CGameHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameHelp, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGameHelp, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IGameHelp 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {8D810658-D053-4FF9-AA10-AE6AEE92AC9F}
static const IID IID_IGameHelp =
{ 0x8D810658, 0xD053, 0x4FF9, { 0xAA, 0x10, 0xAE, 0x6A, 0xEE, 0x92, 0xAC, 0x9F } };

BEGIN_INTERFACE_MAP(CGameHelp, CDialogEx)
	INTERFACE_PART(CGameHelp, IID_IGameHelp, Dispatch)
END_INTERFACE_MAP()


// CGameHelp 消息处理程序
