// MsgDialog.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "SVIctl.h"
#include "MsgDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgDialog ダイアログ


CMsgDialog::CMsgDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CMsgDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgDialog)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgDialog, CDialog)
	//{{AFX_MSG_MAP(CMsgDialog)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgDialog メッセージ ハンドラ

void CMsgDialog::OnOK() 
{
//	return;
}
void CMsgDialog::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CMsgDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	SetDlgItemText(IDC_MSG,strMsg);	

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

int CMsgDialog::DoModal(UINT UID) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	strMsg.LoadString(UID);
	
	return (int)CDialog::DoModal();
}

void CMsgDialog::OnClose() 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	
	CDialog::OnClose();
}

BOOL CMsgDialog::SetMessge(UINT UID) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	strMsg.LoadString(UID);
	SetDlgItemText(IDC_MSG,strMsg);	
	
	return TRUE;
}