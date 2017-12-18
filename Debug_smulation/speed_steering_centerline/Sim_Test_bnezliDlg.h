// Sim_Test_bnezliDlg.h : header file
//

#if !defined(AFX_SIM_TEST_BNEZLIDLG_H__35334792_AEF0_4283_8C86_B9829CB0E624__INCLUDED_)
#define AFX_SIM_TEST_BNEZLIDLG_H__35334792_AEF0_4283_8C86_B9829CB0E624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GraphBox.h"

/////////////////////////////////////////////////////////////////////////////
// CSim_Test_bnezliDlg dialog

class CSim_Test_bnezliDlg : public CDialog
{
// Construction
public:
    int  flag1;
	CSim_Test_bnezliDlg(CWnd* pParent = NULL);	// standard constructor
    void draw();
	void JzShowFont(CDC *pDC, int xPos,int yPos, int nHeight, int nWidth, CString strText);
// Dialog Data
	//{{AFX_DATA(CSim_Test_bnezliDlg)
	enum { IDD = IDD_SIM_TEST_BNEZLI_DIALOG };
	CString	m_pathname;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSim_Test_bnezliDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSim_Test_bnezliDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onopenfile();
	afx_msg void Ondrawspeed();
	afx_msg void Ondrawturn();
	afx_msg void Ondrawrealspeed();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void Ondrawzhongxian();
	afx_msg void Ongetyuzhi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIM_TEST_BNEZLIDLG_H__35334792_AEF0_4283_8C86_B9829CB0E624__INCLUDED_)
