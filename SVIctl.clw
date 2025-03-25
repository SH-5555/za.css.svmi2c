; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CSVIctlDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SVIctl.h"

ClassCount=5
Class1=CSVIctlApp
Class2=CSVIctlDlg

ResourceCount=4
Resource1=IDR_MAINFRAME
Class3=CDumpDialog
Resource2=IDD_SVICTL_DIALOG
Class4=CMsgDialog
Resource3=IDD_MSG_DIALOG
Class5=SVMSettingDlg
Resource4=IDD_SVMSTTING_DIALOG

[CLS:CSVIctlApp]
Type=0
HeaderFile=SVIctl.h
ImplementationFile=SVIctl.cpp
Filter=N

[CLS:CSVIctlDlg]
Type=0
HeaderFile=SVIctlDlg.h
ImplementationFile=SVIctlDlg.cpp
Filter=D
LastObject=ID_DPD
BaseClass=CDialog
VirtualFilter=dWC

[CLS:SVMSettingDlg]
Type=0
HeaderFile=SVMSettingDlg.h
ImplementationFile=SVMSettingDlg.cpp
Filter=D
LastObject=ID_DPD
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_SVICTL_DIALOG]
Type=1
Class=CSVIctlDlg
ControlCount=18
Control1=IDC_STATIC,static,1342308864
Control2=ID_SLAVE_ADDRESS,edit,1350631552
Control3=IDC_STATIC,static,1342308864
Control4=ID_SUB_ADDRESS,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=ID_VALUE,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=ID_READ_COUNTS,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=ID_DUMP_VALUE,edit,1353777348
Control11=ID_REALTIME,button,1342242819
Control12=ID_WORD_ADDRESS,button,1342251011
Control13=ID_INIT,button,1342242816
Control14=ID_WRITE,button,1342242816
Control15=ID_READ,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=ID_SEL_COMBO,combobox,1344339970
Control18=ID_SCAN,button,1342242816

[DLG:IDD_SVMSTTING_DIALOG]
Type=1
Class=SVMSettingDlg


[CLS:CDumpDialog]
Type=0
HeaderFile=DumpDialog.h
ImplementationFile=DumpDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_MSG_DIALOG]
Type=1
Class=CMsgDialog
ControlCount=1
Control1=IDC_MSG,static,1342308352

[CLS:CMsgDialog]
Type=0
HeaderFile=MsgDialog.h
ImplementationFile=MsgDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_MSGCANCEL
VirtualFilter=dWC

