
// GreedySnakeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GreedySnake.h"
#include "GreedySnakeDlg.h"
#include "afxdialogex.h"
#include "Snake.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//蛇与食物全局变量
Snake snake[50];
Food food;

// CGreedySnakeDlg 对话框



CGreedySnakeDlg::CGreedySnakeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGreedySnakeDlg::IDD, pParent)
	, m_init(false)
	, m_GameLevel(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGreedySnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATUS, m_status);
}

BEGIN_MESSAGE_MAP(CGreedySnakeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_COMMAND(IDM_START, &CGreedySnakeDlg::OnStart)
	ON_COMMAND(IDM_PAUSE, &CGreedySnakeDlg::OnPause)

	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(IDM_CONTINUE, &CGreedySnakeDlg::OnContinue)
	ON_COMMAND(IDM_EXIT, &CGreedySnakeDlg::OnExit)
	ON_COMMAND(ID_ABOUT, &CGreedySnakeDlg::OnAbout)
END_MESSAGE_MAP()


// CGreedySnakeDlg 消息处理程序

BOOL CGreedySnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//精确控制绘图区域大小为324*324
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	pWnd->SetWindowPos(NULL, 0, 0, 324, 324, SWP_NOZORDER | SWP_NOMOVE);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGreedySnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		initGameFrame();
		CDialogEx::OnPaint();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGreedySnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//绘制贪吃蛇边框外景
void CGreedySnakeDlg::initGameFrame()
{
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	CDC *pDC = pWnd->GetDC();//获取画布区域
	CBrush DrawBrush,*pOldBrush;//画刷对象
	DrawBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldBrush = pDC->SelectObject(&DrawBrush);//把对象画刷选入到设备描述表中
	for (int i = 0; i <= snake[0].len - 1; i++)
		pDC->Rectangle(snake[i].x*20 , snake[i].y*20, (snake[i].x+1)*20, (snake[i].y + 1)*20);
	pDC->SelectObject(pOldBrush);//将原来的画刷放回去
	DrawBrush.DeleteObject();//释放不用的画刷
}


BOOL CGreedySnakeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		//MessageBox(L"按键按下！");
		switch (pMsg->wParam)
		{
		case VK_UP://direction “上下左右”分别为 “1234”
			//MessageBox(L"按了下键！");
			if (snake[0].direction != 2)
				snake[0].direction = 1;//当蛇方向不为“下”时才能将蛇头方向调整为“上”，否则忽略
				return TRUE;
			break;
		case VK_DOWN:
			if (snake[0].direction != 1)
				snake[0].direction = 2;
				return TRUE;
			break;
		case VK_LEFT:
			if (snake[0].direction != 4)
				snake[0].direction = 3;
				return TRUE;
			break;
		case VK_RIGHT:
			if (snake[0].direction != 3)
				snake[0].direction = 4;
				return TRUE;
			break;
		default:
			return TRUE;
			break;
		}
	} 

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CGreedySnakeDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CString str;
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	//注意getClientRect的rect不包括位置，因此top与left必然为0
	pWnd->GetWindowRect(&rect);//得到相对windows区域控件大小
	ScreenToClient(&rect); //转到client
	CPoint rtOrigin = rect.TopLeft();
	if (TRUE == PtInRect(&rect, point))
	{
		str.Format(L"鼠标位置：%d,%d", point.x-rtOrigin.x, point.y-rtOrigin.y);
		AfxMessageBox(str);
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CGreedySnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CString score;
	//根据蛇长度逐渐增加难度，即分别在370ms，270ms,200ms,100ms进行一次新移动
	if (snake[0].len == 3){
		SetTimer(1, 370, NULL);
		m_GameLevel = 1;
	}
	else if (snake[0].len == 6){
		SetTimer(1, 270, NULL);
		m_GameLevel = 2;
	}
	else if (snake[0].len == 9){
		SetTimer(1, 250, NULL);
		m_GameLevel = 3;
	}
	else if (snake[0].len == 12){
		SetTimer(1, 200, NULL);
		m_GameLevel = 4;
	}
	else if (snake[0].len == 15){
		SetTimer(1, 150, NULL);
		m_GameLevel = 5;
	}
	else if (snake[0].len == 20){
		SetTimer(1, 100, NULL);	
		m_GameLevel = 6;
	}
	else if (snake[0].len == 25){
		KillTimer(1);
		AfxMessageBox(L"你赢了！");
	}

	score.Format(L"得分:%d!", (snake[0].len - 3) * 10);
	//撞界判断
	int gameLeftBorder = 0, gameRightBorder = 324;
	if (snake[0].x*20  > gameRightBorder || snake[0].y*20  > gameRightBorder || snake[0].x*20 < gameLeftBorder || snake[0].y*20 < gameLeftBorder){
		KillTimer(1);
		score = CString(L"撞到边界，") + score;
		AfxMessageBox(score);
		Invalidate(TRUE);
		m_init = false;
	}
	//蛇身相撞判断
	if (snake[0].len>3)//至少得有4节蛇才可能相撞
	for (int sn = snake[0].len - 1; sn>0; sn--)
	{
		if (snake[0].x * 20 == snake[sn].x * 20 && snake[0].y * 20 == snake[sn].y * 20)//看蛇头和蛇身是否重合判断是否相撞
		{
			KillTimer(1);
			score = CString(L"蛇身相撞，") + score;
			AfxMessageBox(score);
			Invalidate(TRUE);
			m_init = false;
		}
	}

	//---------------绘制图形---------------
	CWnd *pWndLen = GetDlgItem(IDC_STATUS);
	CString str;
	str.Format(L"贪吃蛇长度： %d ", snake[0].len);
	pWndLen->SetWindowTextW(str);
	CWnd *pWndLevel = GetDlgItem(IDC_LEVEL);
	str.Format(L"当前等级： %d ", m_GameLevel);
	pWndLevel->SetWindowTextW(str);

	CWnd *pWnd = GetDlgItem(IDC_GAMEAREA);
	CDC *pDC = pWnd->GetDC();
	COLORREF bgColor = GetSysColor(COLOR_BTNFACE);//获取对话框默认背景底色，将蛇尾重绘为背景色以达到消除蛇尾的效果
	//pDC->SetBkColor(bgColor);//与GetBKColor一样，仅仅得到/修改字体的背景颜色

	CBrush newBrush1,*oldBrush1;
	newBrush1.CreateSolidBrush(bgColor);
	oldBrush1 = pDC->SelectObject(&newBrush1);
	CRect rect(snake[snake[0].len - 1].x * 20, snake[snake[0].len - 1].y * 20, (snake[snake[0].len - 1].x + 1) * 20, (snake[snake[0].len - 1].y + 1) * 20);
	pDC->FillRect(rect, &newBrush1);
	pDC->SelectObject(oldBrush1);//复原
	newBrush1.DeleteObject();//释放新画刷内存

	//将蛇前进一步，头部需要另外处理
	for (int i = snake[0].len - 1; i>0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	//行走方向判断,处理头部位置
	if (snake[0].direction == 1)snake[0].y--;//上
	if (snake[0].direction == 2)snake[0].y++;//下
	if (snake[0].direction == 3)snake[0].x--;//左
	if (snake[0].direction == 4)snake[0].x++;//右
	CBrush newBrush2, *oldBrush2;
	newBrush2.CreateSolidBrush(RGB(255, 255, 255));
	oldBrush2 = pDC->SelectObject(&newBrush2);
	pDC->Rectangle(snake[0].x * 20, snake[0].y * 20, (snake[0].x + 1) * 20, (snake[0].y + 1) * 20);//绘制新蛇头
	pDC->SelectObject(oldBrush2);
	newBrush2.DeleteObject();

	//判断吃豆条件，撞到就吃，并在尾部添加一格
	if (food.hasfood == true && snake[0].x * 20 == food.x * 20 && snake[0].y * 20 == food.y * 20)
	{
		snake[0].len++;
		food.hasfood = false;//吃掉了食物
		/*snake[snake[0].len - 1].x = snake[snake[0].len - 2].x;
		snake[snake[0].len - 1].y = snake[snake[0].len - 2].y;*/
	}
	//如果食物被吃了 就生成
	if (food.hasfood == false)//没有食物了
	{
		srand((unsigned)time(NULL));//设定伪随机数种子
		while (true){
			food.x = rand() % 16;//使food产生坐标范围为[0,15]
			food.y = rand() % 16;
			int isfo = snake[0].len - 1;
			for (; isfo >= 0; isfo--){
				if (food.x * 20 == snake[isfo].x * 20 && food.y * 20 == snake[isfo].y * 20)//如果新生成的食物在蛇身上，则重新生成
				{
					break;
				}
			}
			if (isfo == -1)//新生成食物不在蛇身上
				break;
		}

		COLORREF bgColor = RGB(100, 100, 100);
		CBrush newBrush3, *oldBrush3;
		newBrush3.CreateSolidBrush(bgColor);
		oldBrush3 = pDC->SelectObject(&newBrush3);
		pDC->Rectangle(food.x * 20, food.y * 20, (food.x + 1) * 20, (food.y + 1) * 20);
		pDC->SelectObject(oldBrush3);
		newBrush3.DeleteObject();

		food.hasfood = true;
	}
	//ReleaseDC(pDC);

	CDialogEx::OnTimer(nIDEvent);
}


void CGreedySnakeDlg::OnContinue()
{
	// TODO:  在此添加命令处理程序代码
	SetTimer(1, 10, NULL);//kill之后的状态已经保存在全局变量snake与food中
}


void CGreedySnakeDlg::OnExit()
{
	// TODO:  在此添加命令处理程序代码
	AfxMessageBox(L"退出游戏!");
	exit (0);
}

void CGreedySnakeDlg::OnStart()
{
	// TODO:  在此添加命令处理程序代码
	SetTimer(1, 3000, NULL);
	AfxMessageBox(L"3秒后开始游戏!");
	init();
}


void CGreedySnakeDlg::OnPause()
{
	// TODO:  在此添加命令处理程序代码
	
	KillTimer(1);
	AfxMessageBox(L"暂停游戏!");
}



void CGreedySnakeDlg::init()
{
	//初始化蛇初始位置，以及蛇初始行动方向，初始长度为3，默认没有食物
	if (false == m_init){
		snake[0].x = 10;
		snake[0].y = 10;
		snake[1].x = 11;
		snake[1].y = 10;
		snake[2].x = 12;
		snake[2].y = 10;
		//---测试边界代码---
		//左边界：（0，0），右边界(324,324)映射到蛇坐标为(0,0)到(15,15)
		/*snake[0].x = 13;
		snake[0].y = 15;
		snake[1].x = 14;
		snake[1].y = 15;
		snake[2].x = 15;
		snake[2].y = 15;*/
		snake[0].direction = 3;
		snake[0].len = 3;
		food.hasfood = false;
		m_init = true;
	}
}


void CGreedySnakeDlg::OnAbout()
{
	// TODO:  在此添加命令处理程序代码
	CAboutDlg cAboutDlg;
	cAboutDlg.DoModal();
}
