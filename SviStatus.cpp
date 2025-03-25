// SviStatus.cpp: CSviStatus �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SviStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

//�f�t�H���g�R���X�g���N�^
CSviStatus::CSviStatus()
{

}

//SVI�n�[�h�E�G�A�X�e�[�^�X�������ɂƂ�R���X�g���N�^
CSviStatus::CSviStatus(GET_STATUS &status)
{
	setStatus(status);
}


CSviStatus::~CSviStatus()
{

}

//SVI�n�[�h�E�G�A�X�e�[�^�X��ݒ肵�܂�
void CSviStatus::setStatus(GET_STATUS &status)
{
	//�����������o�ϐ��ɃR�s�[
	memcpy(&SviStatus, &status, sizeof(GET_STATUS));
}

//SVI�n�[�h�E�G�A�X�e�[�^�X�̂�����{�X�e�[�^�X�݂̂�ݒ肵�܂�
void CSviStatus::setBaseStatus(ULONG status)
{
	SviStatus.ulBasicStatus = status;
}

//��{�X�e�[�^�X������I�����ǂ���
bool CSviStatus::IsSuccess(void)
{
	switch(SviStatus.ulBasicStatus)
	{
	case SVI_STS_SUCCESS:
	case SVI_STS_FRAMEPENDING:
	case SVI_STS_CAPCANCELED:
		return true;
	default:
		break;
	}
	return false;
}
//��{�X�e�[�^�X���𕶎��񉻂��܂��B
CString getBasicStatusString(ULONG basicStatus)
{
	CString outputString;
	switch(basicStatus)
	{
	case SVI_STS_SUCCESS:  
		outputString = " ����I��";
		break;
	case SVI_STS_FRAMEPENDING:  
		outputString = " ����I�� (�ۗ��t���[��/�f�[�^����)";
		break;
	case SVI_STS_CAPCANCELED    :  
		outputString = " ����I�� (�L���v�`�������~���ꂽ)";
		break;
	case SVI_STS_BUSY           :  
		outputString = " �r�W�[�ŃR�}���h�����s�ł��܂���";
		break;
	case SVI_STS_RECOVERYMODE   :  
		outputString = " ���J�o���[���[�h�̂��߃R�}���h�����s�ł��܂���";
		break;
	case SVI_STS_I2CACTIVE      :  
		outputString = " I2C�R���g���[���A�N�e�B�u";
		break;
	case SVI_STS_CMD_INVALID    :  
		outputString = " �R�}���h���s���ł�";
		break;
	case SVI_STS_PRM_INVALID    :  
		outputString = " �p�����[�^���s���ł�";
		break;
	case SVI_STS_SEQ_INVALID    :  
		outputString = " �p�P�b�g�̔��s�V�[�P���X���s���ł�";
		break;
	case SVI_STS_I2C_ACKTIMEOUT :  
		outputString = " I2C�ŃX���[�u�����ACK����M�ł����^�C���A�E�g���������܂���";
		break;
	case SVI_STS_I2C_PRETIMEOUT :  
		outputString = " I2C�Ńv���^�C���A�E�g���������܂���";
		break;
	case SVI_STS_I2C_POSTTIMEOUT: 
		outputString = " I2C�Ń|�X�g�^�C���A�E�g���������܂���";
		break;
	case SVI_STS_USB_ERROR      :  
		outputString = " USB�ʐM���ɃG���[���������܂���";
		break;
	case SVI_STS_UPDATE_INVALID :  
		outputString = " ���W���[���f�[�^���s���ł�";
		break;
	case SVI_STS_FROMERS_ERROR  :  
		outputString = " �t���b�V���������[�̏����Ɏ��s���܂���";
		break;
	case SVI_STS_FROMWT_ERROR   :  
		outputString = " �t���b�V���������[�̏������݂Ɏ��s���܂���";
		break;
	case SVI_STS_INTERNAL_ERROR :  
		outputString = " �����G���[���������܂���";
		break;
	case SVI_STS_RESOURCE_ERROR :  
		outputString = " �������\�[�X���s�����ď��������s�ł��܂���";
		break;
	default:
		outputString = "�G���[������ł��܂���";
		break;
	}
	return outputString;
}
