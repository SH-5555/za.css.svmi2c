#if !defined(AFX_MSGDIALOG_H__FCFFC12B_77FF_46C9_B212_EC338AADA5D6__INCLUDED_)
#define AFX_MSGDIALOG_H__FCFFC12B_77FF_46C9_B212_EC338AADA5D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgDialog.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMsgDialog �_�C�A���O

class CMsgDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CMsgDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CMsgDialog)
	enum { IDD = IDD_MSG_DIALOG };
		// ����: ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMsgDialog)
	public:
	virtual int DoModal(UINT UID);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	CString strMsg;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CMsgDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL SetMessge(UINT UID);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MSGDIALOG_H__FCFFC12B_77FF_46C9_B212_EC338AADA5D6__INCLUDED_)
