
// Z90LCDTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZ90LCDTestApp: 
// �йش����ʵ�֣������ Z90LCDTest.cpp
//

class CZ90LCDTestApp : public CWinApp
{
public:
	CZ90LCDTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZ90LCDTestApp theApp;