// DumpDialog.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CDumpDialog �_�C�A���O


CDumpDialog::CDumpDialog(int *len ,CWnd* pParent /*=NULL*/)
	: CDialog(CDumpDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDumpDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
	m_len = len; 
}


void CDumpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDumpDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDumpDialog, CDialog)
	//{{AFX_MSG_MAP(CDumpDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpDialog ���b�Z�[�W �n���h��

void CDumpDialog::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
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
