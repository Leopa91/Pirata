
// Z90KeyKeyboard.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CZ90KeyKeyboardApp: 
// �йش����ʵ�֣������ Z90KeyKeyboard.cpp
//

class CZ90KeyKeyboardApp : public CWinApp
{
public:
	CZ90KeyKeyboardApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CZ90KeyKeyboardApp theApp;