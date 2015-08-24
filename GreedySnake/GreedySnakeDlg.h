
// GreedySnakeDlg.h : ͷ�ļ�
//

#pragma once


// CGreedySnakeDlg �Ի���
class CGreedySnakeDlg : public CDialogEx
{
// ����
public:
	CGreedySnakeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GREEDYSNAKE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

private:
	void initGameFrame();
public:
	afx_msg void OnStart();
	afx_msg void OnPause();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnContinue();
	afx_msg void OnExit();
	bool m_init;
private:
	void init();
public:
	afx_msg void OnAbout();
private:
	int m_GameLevel;
};
