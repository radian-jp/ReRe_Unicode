// Rename.h : RENAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_RENAME_H__4B7AB67F_CCC8_4273_9DFE_4B73E2D8DAE6__INCLUDED_)
#define AFX_RENAME_H__4B7AB67F_CCC8_4273_9DFE_4B73E2D8DAE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "common.h"

/////////////////////////////////////////////////////////////////////////////
// CRenameApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� Rename.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CRenameApp : public CWinApp
{
public:
	CRenameApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRenameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CRenameApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RENAME_H__4B7AB67F_CCC8_4273_9DFE_4B73E2D8DAE6__INCLUDED_)
