// SVIctl.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "SVIctl.h"
#include "SVIctlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp

BEGIN_MESSAGE_MAP(CSVIctlApp, CWinApp)
	//{{AFX_MSG_MAP(CSVIctlApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp クラスの構築

CSVIctlApp::CSVIctlApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CSVIctlApp オブジェクト

CSVIctlApp* theApp;

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp クラスの初期化

BOOL CSVIctlApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	CSVIctlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//       記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
		//       記述してください。
	}else if (nResponse == 0)
	{
		MessageBox(NULL , "DoModal response = 0" , "Dialog error." , MB_OK);
	}else
	{
		MessageBox(NULL , "DoModat response = others" , "Dialog error." , MB_OK);
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

//extern "C" HINSTANCE _hdllInstance = NULL;
//
//HINSTANCE GetInstance()
//{
//    return _hdllInstance;
//}
//
//BOOL APIENTRY DllMain(
//    HINSTANCE hInstance, 
//    DWORD dwReason, 
//    LPVOID pReserved)
//{
//	switch(dwReason)
//	{
//	case DLL_PROCESS_ATTACH:
//		_hdllInstance = hInstance;
//		break;
//	default:
//		break;
//	}
//}


//#include "SelBoardDlg.h"
// ------- 追加
void WINAPI ShowSettingDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CSVIctlDlg dlg;
	int nResponse = dlg.DoModal();
}

int WINAPI SendSettingFile(char *filePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CSVIctlDlg *dlg;
	dlg = new CSVIctlDlg();

	BOOL ret = dlg->Create(IDD_SVICTL_DIALOG, NULL);
	if (!ret) //Create failed.
	{
		AfxMessageBox(_T("Error creating Dialog"));
		return -1;
	}

	dlg->ShowWindow(SW_HIDE/*SW_SHOW*/);
	dlg->SettingFileWrite(filePath);
	dlg->CloseWindow();

	return 0;
}
