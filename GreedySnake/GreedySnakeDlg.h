
// GreedySnakeDlg.h : 头文件
//

#pragma once


// CGreedySnakeDlg 对话框
class CGreedySnakeDlg : public CDialogEx
{
// 构造
public:
	CGreedySnakeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GREEDYSNAKE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
