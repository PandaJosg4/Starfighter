
// StarfighterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Starfighter.h"
#include "StarfighterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStarfighterDlg dialog



CStarfighterDlg::CStarfighterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARFIGHTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStarfighterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDB_TRIANGLE, m_TriangleHolder);
}

BEGIN_MESSAGE_MAP(CStarfighterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_START, &CStarfighterDlg::OnBnClickedStart)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CStarfighterDlg message handlers

BOOL CStarfighterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here



    /*
    Code to stretch image (low quality)
    *** Try to use source image size whenever possible ***

    // Handle to destination device context
    HDC hDC = CImg.GetDC();
    //CImg.StretchBlt(hDC, CRect(130, 260, 370, 500));
    CImg.StretchBlt(hDC, CRect(120, 120, 360, 360));

    CImg.ReleaseDC();

    CBmp.Detach();
    CBmp.Attach(CImg.Detach());

    */


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStarfighterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStarfighterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStarfighterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// Moves the Player Dialog (triangle) on screen
void CStarfighterDlg::MovePlayerDlg(int xChange, int yChange)
{
    CRect rect;
    CWnd *pWnd = this->GetDlgItem(IDB_TRIANGLE);
    pWnd->GetWindowRect(&rect);
    this->ScreenToClient(&rect);
    m_TriangleHolder.MoveWindow(rect.left + xChange, rect.top + yChange, rect.Width(), rect.Height());
}

/*
virtual BOOL Create(
LPCTSTR lpszClassName,
LPCTSTR lpszWindowName,
DWORD dwStyle,
Const RECT& rect,
CWnd* pParentWnd,
UINT nID,
CCreateContext* pContext = NULL
);*/


void CStarfighterDlg::MovePlayer()
{

}



/*
// Code for loading bmp from resouce
IStream* CreateStreamOnResource(LPCTSTR lpName, LPCTSTR lpType)
{
IStream * ipStream = NULL;

HRSRC hrsrc = FindResource(NULL, lpName, lpType);
if (hrsrc == NULL)
goto Return;

DWORD dwResourceSize = SizeofResource(NULL, hrsrc);
HGLOBAL hglbImage = LoadResource(NULL, hrsrc);
if (hglbImage == NULL)
goto Return;

LPVOID pvSourceResourceData = LockResource(hglbImage);
if (pvSourceResourceData == NULL)
goto Return;

HGLOBAL hgblResourceData = GlobalAlloc(GMEM_MOVEABLE, dwResourceSize);
if (hgblResourceData == NULL)
goto Return;

LPVOID pvResourceData = GlobalLock(hgblResourceData);

if (pvResourceData == NULL)
goto FreeData;

CopyMemory(pvResourceData, pvSourceResourceData, dwResourceSize);

GlobalUnlock(hgblResourceData);

if (SUCCEEDED(CreateStreamOnHGlobal(hgblResourceData, TRUE, &ipStream)))
goto Return;

FreeData:
GlobalFree(hgblResourceData);

Return:
return ipStream;
}
*/



void CStarfighterDlg::AddEnemy()
{
    CImage CImg;

    CStatic* temp = new CStatic;

    // Create a child bitmap static control and load it from a CImage object.
    temp->Create(_T("A bitmap static control (A)"),
        WS_CHILD | WS_BORDER | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(130, 100, 370, 340),
        this);




	/*
	IStream *pStream = CreateStreamOnResource(MAKEINTRESOURCE(uPNGResourceID), _T("PNG"));
	if (pStream != nullptr)
	{
		rImage.Load(pStream);
		rImage.SetHasAlphaChannel(true);
		pStream->Release();
	}
	*/

	CBitmap bitmap;
	CPngImage image;
	//image.Load(AfxGetInstanceHandle(), IDB_THINKING);
	image.Load(IDB_THINKING);
	bitmap.Attach(image.Detach());

	if (temp->GetBitmap() == NULL)
		temp->SetBitmap(bitmap);


	// This line loads a PNG from a directory, won't work w/ executable
    //CImg.Load(_T("./res/ThinkingSmall.png"));


    //if (temp->GetBitmap() == NULL)
    //temp->SetBitmap(HBITMAP(CImg));

    m_Statics.push_back(temp);

    int i = 0;
}

void CStarfighterDlg::MoveEnemies(int xChange, int yChange)
{
    int i = 0;
    // Iterate through vector of enemies, move each
    for (CStatic* s : m_Statics)
    {
        // Get Rect of new Enemy location
        CRect rect;
        CWnd *pWnd = s;
        pWnd->GetWindowRect(&rect);
        this->ScreenToClient(&rect);

        /*
        // Will add detection on when to delete enemies soon


        // Off-screen detection
        int l = rect.left + xChange;
        int r = rect.right + xChange;
        int t = rect.top + yChange;
        int b = rect.bottom + yChange;

        if (r < 0 || b < 0)
        {
            RemoveEnemy(i);
        }
        */
        s->MoveWindow(rect.left + xChange, rect.top + yChange, rect.Width(), rect.Height());
        i++;
    }


}


void CStarfighterDlg::RemoveEnemy(int index)
{

}


// Starts game
void CStarfighterDlg::OnBnClickedStart()
{
    // Set initial coordinates for Player
    CRect rect;
    CWnd *pWnd = this->GetDlgItem(IDB_TRIANGLE);
    pWnd->GetWindowRect(&rect);
    this->ScreenToClient(&rect);
    playerOne.SetCoordinates(rect.left, rect.top);

    SetTimer(1, 30, NULL);
}



// Timer where game events happen every tick
void CStarfighterDlg::OnTimer(UINT_PTR nIDEvent)
{

    // Handle Player movement
    int xChange = 0,
        yChange = 0;

    // Check which keys are down -> find which direction to move Player 
    if (keysPressed[0] == true) // left
        xChange--;
    if (keysPressed[1] == true) // up
        yChange--;
    if (keysPressed[2] == true) // right
        xChange++;
    if (keysPressed[3] == true) // down
        yChange++;

    // Update Player coordinates + reflect this on dialog
    xChange = xChange * playerOne.speed;
    yChange = yChange * playerOne.speed;
    MovePlayerDlg(xChange, yChange);
    playerOne.Move(xChange, yChange);
    Point coord = playerOne.Coordinates();

    // Update enemies coordinates
    MoveEnemies(xChange, yChange);

    // Update UserPos Text Control with coordinates of Player
    // ### Only include for debugging ###
    CWnd *UserWnd = this->GetDlgItem(IDC_USERPOS);
    CString up;
    up.Format(_T("User Position: %d, %d"), coord.x, coord.y);
    SetDlgItemText(IDC_USERPOS, up);

    CDialogEx::OnTimer(nIDEvent);
}



/*
    Need to override PreTranslateMessage function to get key input
    - pMsg holds info on what type of ->message was called (WM_KEYDOWN, WM_KEYUP, etc)
    - pMsg also holds additional info through ->wParam (which key was pressed)
    - pMsg also has access to cursor location relative to screen through ->pt
*/
BOOL CStarfighterDlg::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN) // Has a key been pressed? (->message == 256)
    {
        // Check for arrow keys, change keysPressed accordingly

        switch (pMsg->wParam)
        {
        case 32:	// Shoot projectiles with space key
            playerOne.Shoot();
            break;
        case 37:    // kP[0] for left arrow
            keysPressed[0] = true;
            break;
        case 38:    // kP[1] for up arrow
            keysPressed[1] = true;
            break;
        case 39:    // kP[2] for right arrow
            keysPressed[2] = true;
            break;
        case 40:    // kP[3] for down arrow
            keysPressed[3] = true;
            break;
        case 80:    // 'P'
            AddEnemy();
            break;
        }


        // Update KeyPress Text Control with pMsg info
        // ### Only include for debugging ###
        CWnd *UserWnd = this->GetDlgItem(IDC_KEYPRESS);
        CString lkp;
        lkp.Format(_T("Last Key Pressed: \n message: %d \n wParam: %d \n CursorCoord: %d, %d"),
            pMsg->message, pMsg->wParam, pMsg->pt.x, pMsg->pt.y);
        SetDlgItemText(IDC_KEYPRESS, lkp);
    }

    else if (pMsg->message == WM_KEYUP) // Has a key been released? (->message == 257)
    {
        // Check for arrow keys, update keysPressed accordingly
        switch (pMsg->wParam)
        {
        case 37:    // Timer 1 for left arrow
            keysPressed[0] = false;
            break;
        case 38:    // Timer 2 for up arrow
            keysPressed[1] = false;
            break;
        case 39:    // Timer 3 for right arrow
            keysPressed[2] = false;
            break;
        case 40:    // Timer 4 for down arrow
            keysPressed[3] = false;
            break;
        }


        // Update KeyPress Text Control with pMsg info
        // ### Only include for debugging ###
        CWnd *UserWnd = this->GetDlgItem(IDC_KEYPRESS);
        CString lkp;
        lkp.Format(_T("Last Key Pressed: \n message: %d \n wParam: %d \n CursorCoord: %d, %d"),
            pMsg->message, pMsg->wParam, pMsg->pt.x, pMsg->pt.y);
        SetDlgItemText(IDC_KEYPRESS, lkp);
    }

    return CDialog::PreTranslateMessage(pMsg);
}







/*
// Old code to create dialog
// Can probably delete
void CMFCApplication1Dlg::CreateProjDlg()
{

    CStatic* projStatic;
    m_ProjHolders.push_back(projStatic);
    CString classname, windowname;
    classname.Format(_T("Projectile"));
    CRect projRect(5, 5, 10, 10);

    (*projStatic).Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, projRect, this, 10000);

    HBITMAP bmp = LoadBitmap(NULL, _T("Shot.bmp"));
    (*projStatic).SetBitmap(bmp);




        /*
    CStatic* projStatic;
    m_ProjHolders.push_back(projStatic);
    CString classname, windowname;
    classname.Format(_T("Projectile"));
    CRect projRect(5, 5, 10, 10);

    (*projStatic).Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, projRect, this, 10000);

    HBITMAP bmp = LoadBitmap(NULL, _T("Shot.bmp"));
    (*projStatic).SetBitmap(bmp);
    */