/*
@title:Lianliankan.h
@author:Frank Liu
@time:2017-6-7
*/

// Lianliankan.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CLianliankanApp: 
// 有关此类的实现，请参阅 Lianliankan.cpp
//

class CLianliankanApp : public CWinApp
{
public:
	CLianliankanApp();

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CLianliankanApp theApp;