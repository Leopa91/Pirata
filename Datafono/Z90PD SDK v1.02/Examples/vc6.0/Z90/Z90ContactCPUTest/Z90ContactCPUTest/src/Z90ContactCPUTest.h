
// Z90ContactCPUTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZ90ContactCPUTestApp: 
// �йش����ʵ�֣������ Z90ContactCPUTest.cpp
//

class CZ90ContactCPUTestApp : public CWinApp
{
public:
	CZ90ContactCPUTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZ90ContactCPUTestApp theApp;