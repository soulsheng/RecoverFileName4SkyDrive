
// rf4sd-mfcdlgDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// Crf4sdmfcdlgDlg 对话框
class Crf4sdmfcdlgDlg : public CDialogEx
{
// 构造
public:
	Crf4sdmfcdlgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RF4SDMFCDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void RecoverFileName4SkyDrive();
	CString * SplitString(CString str, char split, int& iSubStrs);
	void Convert(const char* strIn,char* strOut, int sourceCodepage, int targetCodepage) ;
public:
	// 文件名列表
	CListBox m_fileNameList;
};
