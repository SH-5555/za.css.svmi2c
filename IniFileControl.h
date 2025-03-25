// IniFileControl.h: CIniFileControl �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILECONTROL_H__9E5C66C3_4A02_4C0F_A97D_66396A4585E5__INCLUDED_)
#define AFX_INIFILECONTROL_H__9E5C66C3_4A02_4C0F_A97D_66396A4585E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//ini�t�@�C���𑀍삵�܂��B


class CIniFileControl
{
public:
	CIniFileControl(CString appName,CString iniFileName)
	{
		AppName = appName;
		IniFileName = iniFileName;
	};
	CString AppName;
	CString IniFileName;

	//int��ini�t�@�C���ɏ������݂܂�
	void SetInt(CString keyName,//�L�[��
				int value)//�Z�b�g����l
	{
		char work[MAX_PATH];
		WritePrivateProfileString(AppName,keyName,itoa(value,work,10),IniFileName);
	};
	void SetDouble(CString keyName,//�L�[��
				double value)//�Z�b�g����l
	{
		char work[MAX_PATH];
#if 1 // 2016.07.15 V2.4.5.0
		_gcvt_s(work,MAX_PATH,value,16);
#else
		_gcvt_s(work,MAX_PATH,value,8);
#endif // 2016.07.15 V2.4.5.0
		WritePrivateProfileString(AppName,keyName,work,IniFileName);
	};


	//float��ini�t�@�C���ɏ������݂܂�
	void SetFloat(CString keyName,//�L�[��
				float value)//�Z�b�g����l
	{
		char work[MAX_PATH];
		WritePrivateProfileString(AppName,keyName,_gcvt(value,8,work),IniFileName);
	};

	//bool��ini�t�@�C���ɏ������݂܂�
	void SetBool(CString keyName,//�L�[��
				bool value)//�Z�b�g����l
	{
		WritePrivateProfileString(AppName,keyName,value ? "true" : "false",IniFileName);
	};

	//CString��ini�t�@�C���ɏ������݂܂�
	void SetString(CString keyName,//�L�[��
				CString value)//�Z�b�g����l
	{
		WritePrivateProfileString(AppName,keyName,value,IniFileName);
	};

	//int��ini�t�@�C������ǂݍ���
	int GetInt(CString keyName,//�L�[��
				int defValue)//�f�t�H���g�l
	{
		return GetPrivateProfileInt(AppName,keyName,defValue,IniFileName);
	}
	double GetDouble(CString keyName,//�L�[��
				double defValue)//�f�t�H���g�l
	{
		char work1[MAX_PATH];
		char work2[MAX_PATH];
		_gcvt_s(work1,MAX_PATH,defValue,8);
		GetPrivateProfileString(AppName,keyName,work1,work2,MAX_PATH,IniFileName);
		return atof(work2);
	}

	//float��ini�t�@�C������ǂݍ���
	float GetFloat(CString keyName,//�L�[��
				float defValue)//�f�t�H���g�l
	{
		char work1[MAX_PATH];
		char work2[MAX_PATH];
		GetPrivateProfileString(AppName,keyName,_gcvt(defValue,8,work1),work2,MAX_PATH,IniFileName);
		return (float)atof(work2);
	}

	//bool��ini�t�@�C������ǂݍ���
	bool GetBool(CString keyName,//�L�[��
				bool defValue)//�f�t�H���g�l
	{
		char work[MAX_PATH];
		GetPrivateProfileString(AppName,keyName,(defValue?"true":"false"),work,MAX_PATH,IniFileName);
		CString TrueString("true");
		CString CheckString(work);
		return (TrueString == CheckString);
	}

	//CString��ini�t�@�C������ǂݍ���
	CString GetString(CString keyName,//�L�[��
				CString defValue)//�f�t�H���g�l
	{
		char work[MAX_PATH];
		GetPrivateProfileString(AppName,keyName,defValue,work,MAX_PATH,IniFileName);
		return CString(work);
	}


};

#endif // !defined(AFX_INIFILECONTROL_H__9E5C66C3_4A02_4C0F_A97D_66396A4585E5__INCLUDED_)
