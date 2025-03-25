// SelectDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SVIctl.h"
#include "SelectDialog.h"


// CSelectDialog ダイアログ

IMPLEMENT_DYNAMIC(CSelectDialog, CDialog)

CSelectDialog::CSelectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDialog::IDD, pParent)
	, m_boardID(0)
{

}

CSelectDialog::~CSelectDialog()
{
}

void CSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}


BEGIN_MESSAGE_MAP(CSelectDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CSelectDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelectDialog メッセージ ハンドラ

void CSelectDialog::OnBnClickedOk()
{
	m_boardID = m_list1.GetCurSel();

	OnOK();
}

BOOL CSelectDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	int i;
	for(i=0; i<m_boardList.size(); i++){
		m_list1.AddString(m_boardList[i]);
	}
	m_list1.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
