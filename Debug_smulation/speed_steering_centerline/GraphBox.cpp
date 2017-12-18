// GraphBox.cpp : implementation file
//

#include "stdafx.h"
#include "Sim_Test_bnezli.h"
#include "GraphBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphBox

CGraphBox::CGraphBox()
{
	JzColor[0] = RGB(0xff,0x00,0x00);  JzColor[10] = RGB(0xff,0x80,0x00);
    JzColor[1] = RGB(0x00,0xff,0x00);  JzColor[11] = RGB(0xff,0x80,0x80);
    JzColor[3] = RGB(0x00,0x00,0xff);  JzColor[12] = RGB(0xC0,0xff,0x00);
    JzColor[2] = RGB(0xff,0xff,0x00);  JzColor[13] = RGB(0x80,0xff,0xc0);
    JzColor[4] = RGB(0xff,0x00,0xff);  JzColor[14] = RGB(0x80,0xc0,0xff);
    JzColor[5] = RGB(0x00,0xff,0xff);  JzColor[15] = RGB(0x00,0x80,0xff);
    JzColor[6] = RGB(0xff,0xff,0xff);  JzColor[16] = RGB(0xff,0xc0,0xc0);
    JzColor[7] = RGB(0x80,0x00,0x00);  JzColor[17] = RGB(0xff,0xc0,0xff);
    JzColor[8] = RGB(0x00,0x80,0x00);  JzColor[18] = RGB(0xc0,0xff,0xff);
    JzColor[9] = RGB(0xc0,0x00,0xc0);  JzColor[19] = RGB(0x80,0x80,0x00);

	for(int i=0; i<20;i++) m_JzFlagPoint[i] = true;

	m_GridBitmap = NULL;
//	m_MemDC = NULL;
	m_FlagPaint = true;

}

CGraphBox::~CGraphBox()
{
	if(m_GridBitmap!=NULL) delete m_GridBitmap;
	if(m_MemDC!=NULL) m_MemDC.DeleteDC();
}


BEGIN_MESSAGE_MAP(CGraphBox, CStatic)
	//{{AFX_MSG_MAP(CGraphBox)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphBox message handlers

void CGraphBox::OnPaint() 
{
    CPaintDC pDC(this); // device context for painting

    GetClientRect(&JzModelWnd);//只想要绘制曲线的窗口的句柄即指针
    JzLeft  =  JzModelWnd.left+60;
    JzTop   =  JzModelWnd.top+85;
	JzWidth =  JzModelWnd.Width()-70;
	JzHeight=  JzModelWnd.Height()-120;
	JzPlotWnd = CRect(JzLeft,JzTop,JzLeft+JzWidth,JzTop+JzHeight);

	// do label
    CString JzTitle = CString("实时仿真系统");
	pDC.SetTextColor(crBlue);//设置实时仿真系统的颜色	
    JzShowFont(&pDC,JzLeft+40,JzTop-80 ,40,0,JzTitle);//设置字体和显示字体

	pDC.SetTextColor(crBlack);	//设置坐标字体的颜色
    long JzTemp;
	for(int i=0;i<=12;i++)      //标注xy周的坐标点
	{
	 	JzTemp =  JzTop - 10 + i*JzHeight/12; 
		JzTitle.Format("%2.1f",1.2-i/10.0);
        JzShowFont(&pDC,JzLeft-35,JzTemp,16,0,JzTitle);
	}
	for(i=0;i<=10;i++)
	{
		JzTemp = JzLeft -10 + i*JzWidth/10;
		JzTitle.Format("%2d",i*5);
        JzShowFont(&pDC,JzTemp,JzTop+JzHeight+10,16,0,JzTitle);
	}

 
	
    

}

void CGraphBox::OnDestroy() 
{
	CStatic::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
void CGraphBox::JzShowFont(CDC *pDC, int xPos, int yPos, int nHeight, int nWidth, CString strText)
{
  TEXTMETRIC JzTM;
  CFont      JzFont;//字体由CFont类进行管理

    JzFont.CreateFont(-nHeight,nWidth,0,0,400,false,false,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"Arial");

	CFont *JzOldFont = (CFont*)pDC->SelectObject(&JzFont);

	pDC->GetTextMetrics(&JzTM);
	pDC->SetBkMode(TRANSPARENT);
    pDC->TextOut(xPos,yPos,strText);
	pDC->SelectObject(JzOldFont);
}

void CGraphBox::JzDrawGrid(CDC *pDC)
{
	if(m_FlagPaint)
	{	
	  m_FlagPaint = false;

      pDC->Rectangle(&JzPlotWnd);
      pDC->FillSolidRect(JzPlotWnd,crBlack);
	  CPen JzNewPen(PS_SOLID,1,crGray);
	  CPen *JzOldPen = pDC->SelectObject(&JzNewPen);
	  CPoint JzPoint;
	  for(int i=0;i<=12;i++)            //绘制坐标网格
	  {
		JzPoint.x = JzLeft;
		JzPoint.y = JzTop + i*JzHeight/12;
		pDC->MoveTo(JzPoint);
		JzPoint.x = JzLeft + JzWidth;
		pDC->LineTo(JzPoint);
	  }
	  for(i=0;i<=10;i++)
	  {
		JzPoint.x = JzLeft + i*JzWidth/10;
		JzPoint.y = JzTop;
		pDC->MoveTo(JzPoint);
		JzPoint.y = JzTop  + JzHeight;
		pDC->LineTo(JzPoint);
	  }
	  pDC->SelectObject(JzOldPen);

	  //save grid to  bitmap in memory
	  m_GridBitmap = new CBitmap;
      m_MemDC.CreateCompatibleDC(pDC);
	  m_GridBitmap->CreateCompatibleBitmap(pDC,JzWidth,JzHeight); 
	  m_MemDC.SelectObject(m_GridBitmap);
	  m_MemDC.BitBlt(0,0,JzWidth,JzHeight,pDC,JzLeft,JzTop,SRCCOPY);
	}
	else
	  pDC->BitBlt(JzLeft,JzTop,JzWidth,JzHeight,&m_MemDC,0,0,SRCCOPY);//函数对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境
}

void CGraphBox::DrawPoints(int nMaxPoints, CPoint pPoints[], COLORREF crColors[])
{
	static bool FlagFirstExecute = true;
	if(FlagFirstExecute) m_pWinDC = GetDC();
    FlagFirstExecute = false;
	if(nMaxPoints>18) nMaxPoints = 18;
    for(int i=0;i<nMaxPoints;i++)
	{
	    if(m_JzFlagPoint[i]) m_pWinDC->SetPixel(pPoints[i],crColors[i]);
		if(pPoints[i].x>=JzLeft+JzWidth-1) 
		{
	        m_pWinDC->BitBlt(JzLeft,JzTop,JzWidth,JzHeight,&m_MemDC,0,0,SRCCOPY);
		}
	}
}
