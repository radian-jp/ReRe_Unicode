// Rename.h : RENAME アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_RENAME_H__4B7AB67F_CCC8_4273_9DFE_4B73E2D8DAE6__INCLUDED_)
#define AFX_RENAME_H__4B7AB67F_CCC8_4273_9DFE_4B73E2D8DAE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "common.h"

/////////////////////////////////////////////////////////////////////////////
// CRenameApp:
// このクラスの動作の定義に関しては Rename.cpp ファイルを参照してください。
//

class CRenameApp : public CWinApp
{
public:
	CRenameApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CRenameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CRenameApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_RENAME_H__4B7AB67F_CCC8_4273_9DFE_4B73E2D8DAE6__INCLUDED_)
