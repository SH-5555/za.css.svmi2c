// IniFileControl.h: CIniFileControl クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILECONTROL_H__9E5C66C3_4A02_4C0F_A97D_66396A4585E5__INCLUDED_)
#define AFX_INIFILECONTROL_H__9E5C66C3_4A02_4C0F_A97D_66396A4585E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//iniファイルを操作します。


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

	//intをiniファイルに書き込みます
	void SetInt(CString keyName,//キー名
				int value)//セットする値
	{
		char work[MAX_PATH];
		WritePrivateProfileString(AppName,keyName,itoa(value,work,10),IniFileName);
	};
	void SetDouble(CString keyName,//キー名
				double value)//セットする値
	{
		char work[MAX_PATH];
#if 1 // 2016.07.15 V2.4.5.0
		_gcvt_s(work,MAX_PATH,value,16);
#else
		_gcvt_s(work,MAX_PATH,value,8);
#endif // 2016.07.15 V2.4.5.0
		WritePrivateProfileString(AppName,keyName,work,IniFileName);
	};


	//floatをiniファイルに書き込みます
	void SetFloat(CString keyName,//キー名
				float value)//セットする値
	{
		char work[MAX_PATH];
		WritePrivateProfileString(AppName,keyName,_gcvt(value,8,work),IniFileName);
	};

	//boolをiniファイルに書き込みます
	void SetBool(CString keyName,//キー名
				bool value)//セットする値
	{
		WritePrivateProfileString(AppName,keyName,value ? "true" : "false",IniFileName);
	};

	//CStringをiniファイルに書き込みます
	void SetString(CString keyName,//キー名
				CString value)//セットする値
	{
		WritePrivateProfileString(AppName,keyName,value,IniFileName);
	};

	//intをiniファイルから読み込む
	int GetInt(CString keyName,//キー名
				int defValue)//デフォルト値
	{
		return GetPrivateProfileInt(AppName,keyName,defValue,IniFileName);
	}
	double GetDouble(CString keyName,//キー名
				double defValue)//デフォルト値
	{
		char work1[MAX_PATH];
		char work2[MAX_PATH];
		_gcvt_s(work1,MAX_PATH,defValue,8);
		GetPrivateProfileString(AppName,keyName,work1,work2,MAX_PATH,IniFileName);
		return atof(work2);
	}

	//floatをiniファイルから読み込む
	float GetFloat(CString keyName,//キー名
				float defValue)//デフォルト値
	{
		char work1[MAX_PATH];
		char work2[MAX_PATH];
		GetPrivateProfileString(AppName,keyName,_gcvt(defValue,8,work1),work2,MAX_PATH,IniFileName);
		return (float)atof(work2);
	}

	//boolをiniファイルから読み込む
	bool GetBool(CString keyName,//キー名
				bool defValue)//デフォルト値
	{
		char work[MAX_PATH];
		GetPrivateProfileString(AppName,keyName,(defValue?"true":"false"),work,MAX_PATH,IniFileName);
		CString TrueString("true");
		CString CheckString(work);
		return (TrueString == CheckString);
	}

	//CStringをiniファイルから読み込む
	CString GetString(CString keyName,//キー名
				CString defValue)//デフォルト値
	{
		char work[MAX_PATH];
		GetPrivateProfileString(AppName,keyName,defValue,work,MAX_PATH,IniFileName);
		return CString(work);
	}


};

#endif // !defined(AFX_INIFILECONTROL_H__9E5C66C3_4A02_4C0F_A97D_66396A4585E5__INCLUDED_)
