// SVIctl.h : SVICTL �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SVICTL_H__2251D3D9_7FCC_4835_B4BC_F13CABF1F903__INCLUDED_)
#define AFX_SVICTL_H__2251D3D9_7FCC_4835_B4BC_F13CABF1F903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSVIctlApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� SVIctl.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSVIctlApp : public CWinApp
{
public:
	CSVIctlApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSVIctlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CSVIctlApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SVICTL_H__2251D3D9_7FCC_4835_B4BC_F13CABF1F903__INCLUDED_)
