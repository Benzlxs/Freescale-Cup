// Sim_Test_bnezli.h : main header file for the SIM_TEST_BNEZLI application
//

#if !defined(AFX_SIM_TEST_BNEZLI_H__49B8FA28_6603_4FAA_9E6A_67EC40E1DFE7__INCLUDED_)
#define AFX_SIM_TEST_BNEZLI_H__49B8FA28_6603_4FAA_9E6A_67EC40E1DFE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSim_Test_bnezliApp:
// See Sim_Test_bnezli.cpp for the implementation of this class
//

class CSim_Test_bnezliApp : public CWinApp
{
public:
	CSim_Test_bnezliApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSim_Test_bnezliApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSim_Test_bnezliApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIM_TEST_BNEZLI_H__49B8FA28_6603_4FAA_9E6A_67EC40E1DFE7__INCLUDED_)
