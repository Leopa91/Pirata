// 102.h : main header file for the 102 application
//

#if !defined(AFX_102_H__BF1DDC6E_3CE2_40B6_8E3E_8F5452858538__INCLUDED_)
#define AFX_102_H__BF1DDC6E_3CE2_40B6_8E3E_8F5452858538__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy102App:
// See 102.cpp for the implementation of this class
//

class CMy102App : public CWinApp
{
public:
	CMy102App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy102App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy102App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_102_H__BF1DDC6E_3CE2_40B6_8E3E_8F5452858538__INCLUDED_)
