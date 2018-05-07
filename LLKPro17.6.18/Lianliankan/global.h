/*
@title:global.h
@author:Frank Liu
@time:2017-6-7
*/
#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#define BLANK -1

/*结构体，保存游戏地图中每一个图片元素的行号、列号和值信息*/
typedef struct tagVertex {
	int row;        // 行号
	int col;        // 列号
	int info;       // 值信息
}Vertex; 

#endif // !_GLOBAL_H_

