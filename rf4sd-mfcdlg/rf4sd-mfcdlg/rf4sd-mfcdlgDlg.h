
// rf4sd-mfcdlgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Crf4sdmfcdlgDlg �Ի���
class Crf4sdmfcdlgDlg : public CDialogEx
{
// ����
public:
	Crf4sdmfcdlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RF4SDMFCDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void RecoverFileName4SkyDrive();
	CString * SplitString(CString str, char split, int& iSubStrs);
	void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage) ;
public:
	// �ļ����б�
	CListBox m_fileNameList;
};
