#pragma once

//////////////////////////////////////////////////////////////////////////
// DlgTask.h : header file
// ʵ������Ի���
// ������: �˷�
// ��������: 2008-8-31
/////////////////////////////////////////////////////////////////////////////

class CDlgTask : public CDialog
{
// Construction
public:
	CDlgTask(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTask)
	enum { IDD = IDD_DLG_TASK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTask)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTask)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// ʵ������
	void SetTask( CString task );

private:
	// ʵ������
	CString _task;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.