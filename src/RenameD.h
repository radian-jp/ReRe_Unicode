// RenameD.h : ヘッダー ファイル
//

#if !defined(AFX_RENAMED_H__2780A758_C508_4581_98EE_DE619F1493C8__INCLUDED_)
#define AFX_RENAMED_H__2780A758_C508_4581_98EE_DE619F1493C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
#include "FileLstC.h"
/////////////////////////////////////////////////////////////////////////////
// CRenameDlg ダイアログ

class CRenameDlg : public CDialog
{
// 構築
public:
	CRenameDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CRenameDlg)
	enum { IDD = IDD_RENAME_DIALOG };
	CSpinButtonCtrl	m_Spn_CnvTrimPos;
	CSpinButtonCtrl	m_Spn_CnvTrimLen;
	CSpinButtonCtrl	m_Spn_CnvCutPos;
	CSpinButtonCtrl	m_Spn_CnvCutLen;
	CEdit	m_Edt_CnvCutLen;
	CEdit	m_Edt_CnvCutPos;
	CListBox	m_Lst_RenList;
	CEdit	m_Edt_RenStr;
	CEdit	m_Edt_CnvTrimPos;
	CEdit	m_Edt_CnvTrimLen;
	CEdit	m_Edt_CnvRepBfr;
	CEdit	m_Edt_CnvRepAft;
	CEdit	m_Edt_AddExt;
	CButton	m_Chk_AddSubDir;
	CFileListCtrl	m_Lsc_File;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRenameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CRenameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnDelsel();
	afx_msg void OnBtnAdddir();
	afx_msg void OnItemchangedLscFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnBtnDelall();
	afx_msg void OnChkAddsubdir();
	afx_msg void OnChangeEdtAddext();
	afx_msg void OnChangeEdtCnvrepaft();
	afx_msg void OnChangeEdtCnvrepbfr();
	afx_msg void OnChangeEdtCnvtrimlen();
	afx_msg void OnChangeEdtCnvtrimpos();
	afx_msg void OnRdoCnvcasenone();
	afx_msg void OnRdoCnvcaselow();
	afx_msg void OnRdoCnvcaseup();
	afx_msg void OnChangeEdtRenstr();
	afx_msg void OnSelchangeLstRenlist();
	afx_msg void OnChangeEdtCnvcutlen();
	afx_msg void OnChangeEdtCnvcutpos();
	afx_msg void OnBtnUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CStatusBar m_StatusBar;
	CStringArray m_RenList;
	CStringArray m_SrcRenameFiles;
	CStringArray m_DstRenameFiles;

protected:
	void ReSize();
	void UpdateStatusBar();
	void SaveWindowPlacement(CWnd *pWnd, CString IniTitle);
	void LoadWindowPlacement(CWnd *pWnd, CString IniTitle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RENAMED_H__2780A758_C508_4581_98EE_DE619F1493C8__INCLUDED_)
