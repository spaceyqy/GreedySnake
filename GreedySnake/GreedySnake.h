
// GreedySnake.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGreedySnakeApp: 
// �йش����ʵ�֣������ GreedySnake.cpp
//

class CGreedySnakeApp : public CWinApp
{
public:
	CGreedySnakeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGreedySnakeApp theApp;