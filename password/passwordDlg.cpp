
// passwordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "password.h"
#include "passwordDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CpasswordDlg 对话框



CpasswordDlg::CpasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PASSWORD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CpasswordDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CpasswordDlg 消息处理程序

BOOL CpasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	capture = false;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CpasswordDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CpasswordDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CpasswordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CpasswordDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	::SetCapture(*this);
	capture = true;

	CDialog::OnLButtonDown(nFlags, point);
}


void CpasswordDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	::ReleaseCapture();
	capture = false;

	CDialog::OnLButtonUp(nFlags, point);
}


void CpasswordDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (capture)
	{
		POINT p;
		GetCursorPos(&p);
		HWND hwndPoint = ::WindowFromPoint(p);
		LONG dwStyle = GetWindowLong(hwndPoint, GWL_STYLE);//获取密码框原来样式
		if (dwStyle & ES_PASSWORD)
		{
			::SetWindowWord(hwndPoint, GWL_STYLE, 0);//取消所有样式
			::SetWindowLong(hwndPoint, GWL_STYLE, dwStyle & ~ES_PASSWORD);//去掉密码属性
		}
		//else
		{
			char szTitle[1024];
			::SendMessageA(hwndPoint, WM_GETTEXT, sizeof(szTitle), (LPARAM)szTitle);
			OutputDebugStringA(szTitle);
			OutputDebugStringA("\r\n");
			SetDlgItemTextA(*this, IDC_EDIT1, szTitle);
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}
