// Sim_Test_bnezliDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sim_Test_bnezli.h"
#include "Sim_Test_bnezliDlg.h"
#include "GraphBox.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSim_Test_bnezliDlg dialog

CSim_Test_bnezliDlg::CSim_Test_bnezliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSim_Test_bnezliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSim_Test_bnezliDlg)
	m_pathname = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSim_Test_bnezliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSim_Test_bnezliDlg)
	DDX_Text(pDX, IDC_EDIT1, m_pathname);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSim_Test_bnezliDlg, CDialog)
	//{{AFX_MSG_MAP(CSim_Test_bnezliDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_openfile, Onopenfile)
	ON_BN_CLICKED(IDC_drawspeed, Ondrawspeed)
	ON_BN_CLICKED(IDC_drawturn, Ondrawturn)
	ON_BN_CLICKED(IDC_drawrealspeed, Ondrawrealspeed)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(Button3, Ondrawzhongxian)
	ON_BN_CLICKED(IDC_BUTTON3, Ongetyuzhi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSim_Test_bnezliDlg message handlers

BOOL CSim_Test_bnezliDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	  flag1=4;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSim_Test_bnezliDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSim_Test_bnezliDlg::OnPaint() 
{
     draw();
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);

	}
	else
	{
		CDialog::OnPaint();
	}
	
}


void CSim_Test_bnezliDlg::draw()
{
	CPaintDC pDc(this);
    CRect JzModelWnd(200,10,1300,250);
	pDc.Rectangle(JzModelWnd);
    long JzLeft  =  JzModelWnd.left;
    long JzTop   =  JzModelWnd.top;
	long JzWidth =  JzModelWnd.Width();
	long JzHeight=  JzModelWnd.Height();
	pDc.FillSolidRect(JzModelWnd,crBlack );
	CPen JzNewPen(PS_SOLID,1,crGray);
	CPen *JzOldPen =pDc.SelectObject(&JzNewPen);
	CPoint JzPoint;
	for(int i=0;i<=12;i++)            //绘制坐标网格
	{
		JzPoint.x = JzLeft;
		JzPoint.y = JzTop + i*JzHeight/12;
		pDc.MoveTo(JzPoint);
		JzPoint.x = JzLeft + JzWidth;
		pDc.LineTo(JzPoint);
	}
	for(i=0;i<=10;i++)
	{
		JzPoint.x = JzLeft + i*JzWidth/10;
		JzPoint.y = JzTop;
		pDc.MoveTo(JzPoint);
		JzPoint.y = JzTop  + JzHeight;
		pDc.LineTo(JzPoint);
	  }
	pDc.SetTextColor(crBlack);	//设置坐标字体的颜色
    long JzTemp;
	CString JzTitle;
    JzShowFont(&pDc,JzLeft-95,JzTop,16,0,"速度曲线");
	for( i=0;i<=12;i++)      //标注xy周的坐标点
	{
		JzTemp =  JzTop - 10 + i*JzHeight/12+5; 
		JzTitle.Format("%d",140-i*10);
        JzShowFont(&pDc,JzLeft-35,JzTemp,16,0,JzTitle);
	}
	for(i=0;i<=10;i++)
	{
		JzTemp = JzLeft -10 + i*JzWidth/10;
		JzTitle.Format("%2d",i*30);
        JzShowFont(&pDc,JzTemp,JzTop+JzHeight+10,16,0,JzTitle);
	}


	CRect JModelWnd(200,300,1300,540);
	pDc.Rectangle(JModelWnd);
     JzLeft  =  JModelWnd.left;
     JzTop   =  JModelWnd.top;
	 JzWidth =  JModelWnd.Width();
	 JzHeight=  JModelWnd.Height();
	pDc.FillSolidRect(JModelWnd,crBlack );
	 CPen JNewPen(PS_SOLID,1,crGray);
	 JzOldPen =pDc.SelectObject(&JNewPen);
	 JzPoint;
	for( i=0;i<=12;i++)            //绘制坐标网格
	{
		JzPoint.x = JzLeft;
		JzPoint.y = JzTop + i*JzHeight/12;
		pDc.MoveTo(JzPoint);
		JzPoint.x = JzLeft + JzWidth;
		pDc.LineTo(JzPoint);
	}
	for(i=0;i<=10;i++)
	{
		JzPoint.x = JzLeft + i*JzWidth/10;
		JzPoint.y = JzTop;
		pDc.MoveTo(JzPoint);
		JzPoint.y = JzTop  + JzHeight;
		pDc.LineTo(JzPoint);
	}
	pDc.SetTextColor(crBlack);	//设置坐标字体的颜色

    JzShowFont(&pDc,JzLeft-105,JzTop,16,0,"舵机曲线");
	for( i=0;i<=12;i++)      //标注xy周的坐标点
	{
		JzTemp =  JzTop - 10 + i*JzHeight/12+5; 
		JzTitle.Format("%d",11940-i*310);
        JzShowFont(&pDc,JzLeft-45,JzTemp,16,0,JzTitle);
	}
	for(i=0;i<=10;i++)
	{
		JzTemp = JzLeft -10 + i*JzWidth/10;
		JzTitle.Format("%2d",i*30);
        JzShowFont(&pDc,JzTemp,JzTop+JzHeight+10,16,0,JzTitle);
	}

//@@@@@@@@@@@@@@@@@@@@@@绘制椭圆

	CPen JzPenColor;
    CBrush JzBrushColor;
    CBrush *JzOldBrush;

        JzBrushColor.CreateSolidBrush(crRed);//理想速度  
        JzPenColor.CreatePen(PS_SOLID | PS_COSMETIC, 1, crRed);
        JzOldPen = pDc.SelectObject(&JzPenColor);
        JzOldBrush = pDc.SelectObject(&JzBrushColor);
		pDc.Ellipse(20,30,40,50);
        pDc.TextOut(40,30,"理想速度");
		JzPenColor.DeleteObject();
        JzBrushColor.DeleteObject();


		JzBrushColor.CreateSolidBrush(crGreen);//实际速度  
        JzPenColor.CreatePen(PS_SOLID | PS_COSMETIC, 1, crGreen);
        JzOldPen = pDc.SelectObject(&JzPenColor);
        JzOldBrush = pDc.SelectObject(&JzBrushColor);
		pDc.Ellipse(20,70,40,90);
        pDc.TextOut(40,70,"实际速度");
        JzPenColor.DeleteObject();
        JzBrushColor.DeleteObject();


		JzBrushColor.CreateSolidBrush(crBlue);//控制舵机
        JzPenColor.CreatePen(PS_SOLID | PS_COSMETIC, 1, crBlue);
        JzOldPen = pDc.SelectObject(&JzPenColor);
        JzOldBrush = pDc.SelectObject(&JzBrushColor);
		pDc.Ellipse(20,110,40,130);
        pDc.TextOut(40,110,"转向量");
        JzPenColor.DeleteObject();
        JzBrushColor.DeleteObject();

	
	 


}
void CSim_Test_bnezliDlg::JzShowFont(CDC *pDc, int xPos, int yPos, int nHeight, int nWidth, CString strText)
{
	TEXTMETRIC JzTM;
	CFont      JzFont;//字体由CFont类进行管理
	
    JzFont.CreateFont(-nHeight,nWidth,0,0,400,false,false,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"Arial");
	
	pDc->GetTextMetrics(&JzTM);
	pDc->SetBkMode(TRANSPARENT);
    pDc->TextOut(xPos,yPos,strText);
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSim_Test_bnezliDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSim_Test_bnezliDlg::Onopenfile() 
{
	CFileDialog dlg(TRUE);
	if(IDOK==dlg.DoModal())
	{
		m_pathname=dlg.GetPathName();
	}
	UpdateData(false);
	
}

void CSim_Test_bnezliDlg::Ondrawspeed() 
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,crRed);
	CPen *oldpen;
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(200,130);
	UpdateData(false);
	HANDLE hRead;
	DWORD  filesize=0;
	DWORD  rfile;
	DWORD  err;
	char  cerr[64];
	LPCTSTR rFileName;
	rFileName=m_pathname.GetBuffer(255);
	hRead=CreateFile(rFileName,
		       GENERIC_READ,
			   FILE_SHARE_READ,
			   NULL,
			   OPEN_ALWAYS,
			   FILE_ATTRIBUTE_NORMAL,
			   NULL
			   );
	if(INVALID_HANDLE_VALUE==hRead)
	{
		err=GetLastError();
			sprintf(cerr,"打开文件失败:%d",err);
		this->MessageBox(cerr);
		return ;
	}
	
	filesize=GetFileSize(hRead,NULL);
	char buff;//[2]={0};   
	BYTE yoffset=0;    
	int i=0;//x轴递增
	unsigned  int k=0;
	int  bufft[6]={0};
	int ss=0;
    while(filesize)
	{       ss=0;
		    k=0;
			filesize--;
			ReadFile(hRead,&buff,1,&rfile,NULL);
			if(buff=='=')
			{
			ReadFile(hRead,&buff,1,&rfile,NULL);
			filesize--;
		 	while(buff!=',')
			{
			filesize--;
		 	bufft[k]=buff-48;k++;
		   	ReadFile(hRead,&buff,1,&rfile,NULL);
			}
				yoffset=bufft[0]*10+bufft[1];
                   ss=1;		
			}


			if(buff=='+')
			{
				ReadFile(hRead,&buff,1,&rfile,NULL);
				filesize--;
				while(buff!=',')
				{
					filesize--;
					bufft[k]=buff-48;k++;
					ReadFile(hRead,&buff,1,&rfile,NULL);
			}
			yoffset=bufft[0]*100+bufft[1]*10+bufft[2];
			ss=1;
			}
           
			if(ss==1)
			{
				yoffset=(yoffset-20)*2;
			 if(yoffset>240)
				 yoffset=240;
			 if(yoffset<0)
				 yoffset=0;
		     dc.LineTo(200+i,250-yoffset);
			
			 i=i+flag1;
			}
			
		
	}

//	Invalidate();
	CloseHandle(hRead);
	UpdateData(false);

}

void CSim_Test_bnezliDlg::Ondrawturn() 
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,crBlue);
	CPen *oldpen;
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(200,420);
	UpdateData(false);
	HANDLE hRead;
	DWORD  filesize=0;
	DWORD  rfile;
	DWORD  err;
	char  cerr[64];
	LPCTSTR rFileName;
	rFileName=m_pathname.GetBuffer(255);
	hRead=CreateFile(rFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(INVALID_HANDLE_VALUE==hRead)
	{
		err=GetLastError();
		sprintf(cerr,"打开文件失败:%d",err);
		this->MessageBox(cerr);
		return ;
	}
	
	filesize=GetFileSize(hRead,NULL);
	char buff;//[2]={0};   
	int yoffset=0;    
	int i=0;//x轴递增
	unsigned  int k=0 ;
	int  bufft[10]={0};
	int  sss=0;
    while(filesize)
	{   sss=0;
		k=0;
		filesize--;
		ReadFile(hRead,&buff,1,&rfile,NULL);
		if(buff=='t')
		{
			ReadFile(hRead,&buff,1,&rfile,NULL);
			filesize--;
			while(buff!=',')
			{
				filesize--;
				bufft[k]=buff-48;k++;
				ReadFile(hRead,&buff,1,&rfile,NULL);
			} 
			yoffset=bufft[0]*10000+bufft[1]*1000+bufft[2]*100+bufft[3]*10+bufft[4];
             sss=1;	
		}
		if(buff=='r')
		{
			ReadFile(hRead,&buff,1,&rfile,NULL);
			filesize--;
			while(buff!=',')
			{
				filesize--;
				bufft[k]=buff-48;k++;
				ReadFile(hRead,&buff,1,&rfile,NULL);
			} 
		  yoffset=bufft[0]*1000+bufft[1]*100+bufft[2]*10+bufft[3];
               sss=1;		
		}
	       
	       if(sss==1)
		   {
			   yoffset=(11940-yoffset)*2/31;
			if(yoffset<=0)           
				yoffset=0;
			if(yoffset>=240)
				yoffset=240;
            dc.LineTo(200+i, 300+yoffset); 
			
			i=i+flag1;
		   }
		
	}
	
	//	Invalidate();
	CloseHandle(hRead);
	UpdateData(false);
	

}

void CSim_Test_bnezliDlg::Ondrawrealspeed() 
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,crGreen);
	CPen *oldpen;
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(200,130);
	UpdateData(false);
	HANDLE hRead;
	DWORD  filesize=0;
	DWORD  rfile;
	DWORD  err;
	char  cerr[64];
	LPCTSTR rFileName;
	rFileName=m_pathname.GetBuffer(255);
	hRead=CreateFile(rFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(INVALID_HANDLE_VALUE==hRead)
	{
		err=GetLastError();
		sprintf(cerr,"打开文件失败:%d",err);
		this->MessageBox(cerr);
		return ;
	}
	
	filesize=GetFileSize(hRead,NULL);
	char buff ;   
	BYTE yoffset=0;    
	int i=0;//x轴递增
	unsigned  int k=0  ;
	int  bufft[6]={0};
    int ssss=0;
    while(filesize)
	{
		ssss=0;
		k=0;
		filesize--;
		ReadFile(hRead,&buff,1,&rfile,NULL);
		if(buff=='s')
		{
			ReadFile(hRead,&buff,1,&rfile,NULL);
			filesize--;
		////////////
			while(buff!=',')
			{
				filesize--;
				bufft[k]=buff-48;k++;
				ReadFile(hRead,&buff,1,&rfile,NULL);
			} 
			yoffset= bufft[0]*10+bufft[1];
			ssss=1;
		}
		
	       if(buff=='l')
		   {
			   
			   ReadFile(hRead,&buff,1,&rfile,NULL);
			   filesize--;
			   ////////////
			   while(buff!=',')
			   {
				   filesize--;
				   bufft[k]=buff-48;k++;
				   ReadFile(hRead,&buff,1,&rfile,NULL);
			   } 
			yoffset= bufft[0]*100+bufft[1]*10+bufft[2];
                 ssss=1;
		   }
            if(ssss==1)
			{
		    yoffset=(yoffset-20)*2;
			if(yoffset>240)
				yoffset=240;
			if(yoffset<0)
				 yoffset=0;
			dc.LineTo(200+i,250-yoffset); 
			// bufft[3]='a';bufft[2]='a';bufft[1]='a';
			
			i=i+flag1;
			}	
		
	}
	
	//	Invalidate();
	CloseHandle(hRead);
	UpdateData(false);
	
}

void CSim_Test_bnezliDlg::OnButton1() 
{
	Invalidate();
    flag1++;
	
}

void CSim_Test_bnezliDlg::OnButton2() 
{
   flag1--;
   	Invalidate();
	
}

void CSim_Test_bnezliDlg::Ondrawzhongxian() 
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,crBlue);
	CPen *oldpen;
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(200,130);
	UpdateData(false);
	HANDLE hRead;
	DWORD  filesize=0;
	DWORD  rfile;
	DWORD  err;
	char  cerr[64];
	LPCTSTR rFileName;
	rFileName=m_pathname.GetBuffer(255);
	hRead=CreateFile(rFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(INVALID_HANDLE_VALUE==hRead)
	{
		err=GetLastError();
		sprintf(cerr,"打开文件失败:%d",err);
		this->MessageBox(cerr);
		return ;
	}
	
	filesize=GetFileSize(hRead,NULL);
	char buff ;   
	BYTE yoffset=0;    
	int i=0;//x轴递增
	unsigned  int k=0  ;
	int  bufft[6]={0};
    int sssss=0;
    while(filesize)
	{
		sssss=0;
		k=0;
		filesize--;
		ReadFile(hRead,&buff,1,&rfile,NULL);
		if(buff=='z')
		{
			ReadFile(hRead,&buff,1,&rfile,NULL);
			filesize--;
			////////////
			while(buff!=',')
			{
				filesize--;
				bufft[k]=buff-48;k++;
				ReadFile(hRead,&buff,1,&rfile,NULL);
			} 
			if(k==2)
			yoffset= bufft[0]*10+bufft[1];
	/*		if(k==1)
             yoffset= bufft[0];
			if(k==3)
			yoffset= bufft[0]*100+bufft[1]*10+bufft[2];*/
			sssss=1;
		}
		   if(sssss==1)
		   {
			   yoffset=(yoffset-20)*2;
			   if(yoffset>240)
				   yoffset=240;
			   if(yoffset<0)
				   yoffset=0;
			   dc.LineTo(200+i,250-yoffset); 
			   // bufft[3]='a';bufft[2]='a';bufft[1]='a';
			   
			   i=i+flag1;
		   }	
		   
	}
	
	//	Invalidate();
	CloseHandle(hRead);
	UpdateData(false);
	
}

void CSim_Test_bnezliDlg::Ongetyuzhi() 
{
	CClientDC dc(this);
	CPen pen(PS_SOLID,1,crWhite);
	CPen *oldpen;
	oldpen=dc.SelectObject(&pen);
	dc.MoveTo(200,130);
	UpdateData(false);
	HANDLE hRead;
	DWORD  filesize=0;
	DWORD  rfile;
	DWORD  err;
	char  cerr[64];
	LPCTSTR rFileName;
	rFileName=m_pathname.GetBuffer(255);
	hRead=CreateFile(rFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if(INVALID_HANDLE_VALUE==hRead)
	{
		err=GetLastError();
		sprintf(cerr,"打开文件失败:%d",err);
		this->MessageBox(cerr);
		return ;
	}
	
	filesize=GetFileSize(hRead,NULL);
	char buff ;   
	BYTE yoffset=0;    
	int i=0;//x轴递增
	unsigned  int k=0  ;
	int  bufft[6]={0};
    int bb=0;
    while(filesize)
	{
		bb=0;
		k=0;
		filesize--;
		ReadFile(hRead,&buff,1,&rfile,NULL);
		if(buff=='x')
		{
			ReadFile(hRead,&buff,1,&rfile,NULL);
			filesize--;
			////////////
			while(buff!=',')
			{
				filesize--;
				bufft[k]=buff-48;k++;
				ReadFile(hRead,&buff,1,&rfile,NULL);
			} 
			yoffset= bufft[0]*10+bufft[1];
			bb=1;
		}
		
	       if(buff=='d')
		   {
			   
			   ReadFile(hRead,&buff,1,&rfile,NULL);
			   filesize--;
			   ////////////
			   while(buff!=',')
			   {
				   filesize--;
				   bufft[k]=buff-48;k++;
				   ReadFile(hRead,&buff,1,&rfile,NULL);
			   } 
			   yoffset= bufft[0]*100+bufft[1]*10+bufft[2];
			   bb=1;
		   }
		   if(bb==1)
		   {
			   yoffset=(yoffset-20)*2;
			   if(yoffset>240)
				   yoffset=240;
			   if(yoffset<0)
				   yoffset=0;
			   dc.LineTo(200+i,250-yoffset); 
			   // bufft[3]='a';bufft[2]='a';bufft[1]='a';
			   
			   i=i+flag1;
		   }	
		   
	}
	
	//	Invalidate();
	CloseHandle(hRead);
	UpdateData(false);	
}
