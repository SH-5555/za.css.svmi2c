// DumpDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SVIctl.h"
#include "DumpDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog ダイアログ


CDumpDialog::CDumpDialog(int *len ,CWnd* pParent /*=NULL*/)
	: CDialog(CDumpDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDumpDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
	m_len = len; 
}


void CDumpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDumpDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpDialog, CDialog)
	//{{AFX_MSG_MAP(CDumpDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog メッセージ ハンドラ

void CDumpDialog::OnOK() 
{
	// TODO: この位置にその他の検証用のコードを追加してください
	CEdit *pedit = (CEdit*)this->GetDlgItem(ID_BYTE_LENGTH);
	CString str;
	pedit->GetWindowText(str);
	*m_len = _ttoi(str);
	if(*m_len > 0 && *m_len <= 20)
		TRACE("m_len = %d\n",*m_len);
	else
		*m_len = 0;

	CDialog::OnOK();
}
