// SelBoardDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SVIctl.h"
#include "SelBoardDlg.h"


// CSelBoardDlg ダイアログ

IMPLEMENT_DYNAMIC(CSelBoardDlg, CDialog)

CSelBoardDlg::CSelBoardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelBoardDlg::IDD, pParent)
{

	m_maxBoardName = 0;
	m_curBoardIdx = 0;
}

CSelBoardDlg::~CSelBoardDlg()
{
}

void CSelBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
}


BEGIN_MESSAGE_MAP(CSelBoardDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSelBoardDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelBoardDlg メッセージ ハンドラ

BOOL CSelBoardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	int i;
	for(i=0; i<m_maxBoardName; i++){
		m_combo1.AddString(m_boardName[i]);
	}
	m_combo1.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CSelBoardDlg::OnBnClickedOk()
{
	m_curBoardIdx = m_combo1.GetCurSel();

	OnOK();
}
