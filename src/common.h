#ifndef __COMMON_H__
#define __COMMON_H__
/////////////////////////////////////////////////////////////////////////////
class CCommon
{
public:
	// トレース
	static void Trace(const wchar_t *Format, ...);

	// フォーマット
	static CString FmtStr(		// フォーマット文字
		const wchar_t *Format,		// フォーマット
		...);

	// リソース文字
	static CString ResStr(
		int ID);				// ID

	// 大文字変換
	static CString ToUpper(		// 変換後
		CString Str);			// 変換前

	// 小文字変換
	static CString ToLower(		// 変換後
		CString Str);			// 変換前

	// 文字置換
	static CString ReplaceStr(		// 変換後
		CString Str,				// 変換前
		CString KeyNRep[][2],		// 置換キー & 置換文字
		int Num);					// 置換数

	// 設定ファイルディレクトリ変更
	static CString ChgDirProfile(		// 設定ファイル名
		const wchar_t *ProfileName = 0,	// 設定ファイル名称(0の場合は自動)
		bool ExeDir = true);			// = true EXEファイルのディレクトリに変更, = false カレントディレクトリに変更

	// バージョン獲得
	static CString GetVersion(			// バージョン文字（0.0.0.0形式）
		const wchar_t *FileName = 0);		// ファイル名（0の場合は自分）

	// 実行ファイル名獲得
	static CString GetModuleFileName();

	// ディレクトリ選択
	static CString CCommon::SelectDirectory(	// 選択ディレクトリ
		HWND hWnd,								// ウインドウ
		bool OnlyLocal = false,					// ローカルのみ
		CString DefaltDir = "",					// デフォルトディレクトリ
		CString Title = "");					// タイトル
};
/////////////////////////////////////////////////////////////////////////////
#endif
