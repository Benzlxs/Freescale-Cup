#if !defined(AFX_GRAPHBOX_H__335B15DD_D44B_484B_B98F_791C87C9B0BD__INCLUDED_)
#define AFX_GRAPHBOX_H__335B15DD_D44B_484B_B98F_791C87C9B0BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphBox.h : header file
//

#define crLightGray              RGB (0xC0, 0xC0, 0xC0) 
#define crDarkGray               RGB (0x40, 0x40, 0x40)  
#define crGray                   RGB (0x80, 0x80, 0x80) 
#define crRed                    RGB (0xFF, 0x00, 0x00) 
#define crGreen                  RGB (0x00, 0xFF, 0x00) 
#define crBlue                   RGB (0x00, 0x00, 0xFF) 
#define crBlack                  RGB (0x00, 0x00, 0x00) 
#define crWhite                  RGB (0xFF, 0xFF, 0xFF)

/////////////////////////////////////////////////////////////////////////////
// CGraphBox window

class CGraphBox : public CStatic
{
	// Construction
public:
	CGraphBox();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphBox)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
/*	bool m_JzFlagPoint[20];
	CDC *m_pWinDC;
	bool m_FlagPaint;
	CDC m_MemDC;
	CBitmap *m_GridBitmap;
	void DrawPoints(int nMaxPoints, CPoint pPoints[], COLORREF crColors[]);
	CString  JzLabel[20];
	COLORREF JzColor[20];
	CRect JzPlotWnd;
	CRect JzModelWnd;
	long JzLeft,JzTop,JzHeight,JzWidth;
	void JzDrawGrid(CDC *pDC);
	void JzShowFont(CDC *pDC, int xPos,int yPos, int nHeight, int nWidth, CString strText);
	virtual ~CGraphBox();
*/	
	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphBox)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHBOX_H__335B15DD_D44B_484B_B98F_791C87C9B0BD__INCLUDED_)
