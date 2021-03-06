
// StarfighterDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Player.h"
#include <vector>

// CStarfighterDlg dialog
class CStarfighterDlg : public CDialogEx
{
// Construction
public:
	CStarfighterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARFIGHTER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Key + Game Data
    bool keysPressed[4]; // left->up->right->down
    Player playerOne;
    std::vector<CStatic*> m_Statics;
    // try just one projHolder
    CStatic ProjHolder;
    CStatic staticA;
    int curID = 10000;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual BOOL PreTranslateMessage(MSG * pMsg);
    CStatic m_TriangleHolder;
    afx_msg void OnBnClickedStart();

    // Created functions for Dialog
    void MovePlayerDlg(int xChange, int yChange);
    void CreateProjDlg();
    void MoveEnemies(int xChange, int yChange);
    void MovePlayer();
    void AddEnemy();
    void RemoveEnemy(int index);
};
