/*
@title:GameException.h
@author:Frank Liu
@time:2017-6-7

*/#pragma once

/*游戏异常类，处理程序中的一些异常。程序中类是层层调用的，当下一层出现异常，
则可以抛出一个异常对象。在上一层，则使用 try{} catch{}语句来捕获异常。*/
class CGameException
{
private:
	CString info;
public:
	CGameException(wchar_t *excp);
	~CGameException();
};