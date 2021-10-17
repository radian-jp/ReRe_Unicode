// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__1AE01978_905B_493A_B03C_B68ACDC8C6B6__INCLUDED_)
#define AFX_STDAFX_H__1AE01978_905B_493A_B03C_B68ACDC8C6B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WIN32_WINNT _WIN32_WINNT_WIN7
#define _CRT_SECURE_NO_WARNINGS

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <io.h>
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#include <afxtempl.h>
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__1AE01978_905B_493A_B03C_B68ACDC8C6B6__INCLUDED_)
