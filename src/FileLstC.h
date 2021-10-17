#if !defined(AFX_FILELSTC_H__7CBB19CA_39FE_491B_B08E_B2A98DC5CD76__INCLUDED_)
#define AFX_FILELSTC_H__7CBB19CA_39FE_491B_B08E_B2A98DC5CD76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileLstC.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl �E�B���h�E

class CFileListCtrl : public CListCtrl
{
// �R���X�g���N�V����
public:
	CFileListCtrl();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CFileListCtrl)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CFileListCtrl();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CFileListCtrl)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

public:
	CString m_RenStr;
	bool m_AddSubDir;
	CString m_AddExt;
	int m_CnvTrimPos;
	int m_CnvTrimLen;
	int m_CnvCutPos;
	int m_CnvCutLen;
	CString m_CnvRepBfr;
	CString m_CnvRepAft;
	enum
	{
		C_CASE_NONE = 0,
		C_CASE_LOW,
		C_CASE_UP
	}m_CnvCase;

public:
	enum
	{
		FL_NAME = 0,
		FL_NEWNAME,
		FL_DATE,
		FL_SIZE,
		FL_TYPE,
		FL_MAX
	};

	class CList
	{
	public:
		CString m_Item[FL_MAX];
	};

	int m_ListSerialNo;
	CMap<int, int, CList, CList&> m_Lists;

	CMapStringToPtr m_DupCheck;

	int m_SortCol;
	int m_SortCnd;

public:
	void Init();
	void AddDirFiles(CString DirName, bool Sorting = true);
	bool Add(CString FileName);
	void DelSel();
	void DelAll();
	void Rename();
	void Sort(int Col, int Cnd);
	CString CnvFileNameFilter(CString FileName);
	CString CnvComma(CString NumText);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_FILELSTC_H__7CBB19CA_39FE_491B_B08E_B2A98DC5CD76__INCLUDED_)
