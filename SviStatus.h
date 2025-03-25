// SviStatus.h: CSviStatus �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVISTATUS_H__4F331F97_EB6B_48BA_BFEF_048081F36895__INCLUDED_)
#define AFX_SVISTATUS_H__4F331F97_EB6B_48BA_BFEF_048081F36895__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SVI05API.h"

//SVI�n�[�h�E�G�A�X�e�[�^�X��ێ�����N���X
class CSviStatus  
{
public:
	CSviStatus();
	CSviStatus(GET_STATUS &status);
	virtual ~CSviStatus();

	//GET_STATUS�ɃL���X�g
	operator GET_STATUS(){return getStatus();};

	//SVI�n�[�h�E�G�A�X�e�[�^�X��ݒ肵�܂�
	void setStatus(GET_STATUS &status);

	//SVI�n�[�h�E�G�A�X�e�[�^�X��Ԃ��܂�
	GET_STATUS getStatus(void){return SviStatus;};

	//SVI�n�[�h�E�G�A�X�e�[�^�X�̂�����{�X�e�[�^�X�݂̂�ݒ肵�܂�
	void setBaseStatus(ULONG status);

	//SVI�n�[�h�E�G�A�X�e�[�^�X�̂�����{�X�e�[�^�X�݂̂�Ԃ��܂�
	ULONG getBasicStatus(void){return SviStatus.ulBasicStatus;};

	//��{�X�e�[�^�X������I�����ǂ���
	bool IsSuccess(void);

	//��{�X�e�[�^�X���𕶎��񉻂��܂��B
	CString getBasicStatusString(ULONG basicStatus);

	//�A�C�h����Ԃ��m�F
	bool IsIdle(void){return (SviStatus.ulOPStatus==0);};

	//���j�^�����O��Ԃ��m�F
	bool IsMonitring(void){return (SviStatus.ulOPStatus==1);};

	//���R�[�f�B���O��Ԃ��m�F
	bool IsRecording(void){return (SviStatus.ulOPStatus==2);};

	//�A�b�v�f�[�g�����m�F
	bool IsUpdating(void){return (SviStatus.ulOPStatus==8);};

	//�ۗ��t���[���E�f�[�^�����邩�m�F
	bool IsFramePending(void){return (SviStatus.ulBasicStatus==SVI_STS_FRAMEPENDING);};



private:
	//SVI�n�[�h�E�G�A�X�e�[�^�X
	GET_STATUS SviStatus;
};

#endif // !defined(AFX_SVISTATUS_H__4F331F97_EB6B_48BA_BFEF_048081F36895__INCLUDED_)
