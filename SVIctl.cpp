// SVIctl.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp �N���X�̍\�z

CSVIctlApp::CSVIctlApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSVIctlApp �I�u�W�F�N�g

CSVIctlApp* theApp;

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp �N���X�̏�����

BOOL CSVIctlApp::InitInstance()
{
	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	CSVIctlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �_�C�A���O�� <��ݾ�> �ŏ����ꂽ���̃R�[�h��
		//       �L�q���Ă��������B
	}else if (nResponse == 0)
	{
		MessageBox(NULL , "DoModal response = 0" , "Dialog error." , MB_OK);
	}else
	{
		MessageBox(NULL , "DoModat response = others" , "Dialog error." , MB_OK);
	}

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
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
// ------- �ǉ�
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
