// 1604A.h : main header file for the 1604A application
//

#if !defined(AFX_1604A_H__6DB3682C_3A57_4AC2_A16A_49CAA953D6CF__INCLUDED_)
#define AFX_1604A_H__6DB3682C_3A57_4AC2_A16A_49CAA953D6CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy1604AApp:
// See 1604A.cpp for the implementation of this class
//

class CMy1604AApp : public CWinApp
{
public:
	CMy1604AApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1604AApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy1604AApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1604A_H__6DB3682C_3A57_4AC2_A16A_49CAA953D6CF__INCLUDED_)
