
// Z90CPUtest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZ90CPUtestApp: 
// �йش����ʵ�֣������ Z90CPUtest.cpp
//

class CZ90CPUtestApp : public CWinApp
{
public:
	CZ90CPUtestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZ90CPUtestApp theApp;