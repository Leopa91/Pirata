
// Z90GetPassword.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZ90GetPasswordApp: 
// �йش����ʵ�֣������ Z90GetPassword.cpp
//

class CZ90GetPasswordApp : public CWinApp
{
public:
	CZ90GetPasswordApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZ90GetPasswordApp theApp;