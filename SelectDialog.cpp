// SelectDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "SVIctl.h"
#include "SelectDialog.h"


// CSelectDialog �_�C�A���O

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


// CSelectDialog ���b�Z�[�W �n���h��

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
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
