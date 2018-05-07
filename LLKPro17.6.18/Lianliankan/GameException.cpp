/*
@title:GameException.cpp
@author:Frank Liu
@time:2017-6-7
*/
#include "stdafx.h"
#include "CString"
#include "GameException.h"

CGameException::CGameException(wchar_t *excp)
{
	info.Format(excp);
	MessageBox(NULL, info, _T("Error!"), MB_OK | MB_ICONERROR);   //输出异常信息
}


CGameException::~CGameException()
{
	delete info;   //释放指针
}
