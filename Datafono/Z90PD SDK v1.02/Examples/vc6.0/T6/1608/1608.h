// 1608.h : main header file for the 1608 application
//

#if !defined(AFX_1608_H__99630CC7_2C22_462A_82B0_530CC56746B2__INCLUDED_)
#define AFX_1608_H__99630CC7_2C22_462A_82B0_530CC56746B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy1608App:
// See 1608.cpp for the implementation of this class
//

class CMy1608App : public CWinApp
{
public:
	CMy1608App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1608App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy1608App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1608_H__99630CC7_2C22_462A_82B0_530CC56746B2__INCLUDED_)
