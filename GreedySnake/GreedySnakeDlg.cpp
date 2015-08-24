
// GreedySnakeDlg.cpp : ʵ���ļ�
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

//����ʳ��ȫ�ֱ���
Snake snake[50];
Food food;

// CGreedySnakeDlg �Ի���



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


// CGreedySnakeDlg ��Ϣ�������

BOOL CGreedySnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//��ȷ���ƻ�ͼ�����СΪ324*324
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	pWnd->SetWindowPos(NULL, 0, 0, 324, 324, SWP_NOZORDER | SWP_NOMOVE);
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGreedySnakeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		initGameFrame();
		CDialogEx::OnPaint();
	}


}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGreedySnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//����̰���߱߿��⾰
void CGreedySnakeDlg::initGameFrame()
{
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	CDC *pDC = pWnd->GetDC();//��ȡ��������
	CBrush DrawBrush,*pOldBrush;//��ˢ����
	DrawBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldBrush = pDC->SelectObject(&DrawBrush);//�Ѷ���ˢѡ�뵽�豸��������
	for (int i = 0; i <= snake[0].len - 1; i++)
		pDC->Rectangle(snake[i].x*20 , snake[i].y*20, (snake[i].x+1)*20, (snake[i].y + 1)*20);
	pDC->SelectObject(pOldBrush);//��ԭ���Ļ�ˢ�Ż�ȥ
	DrawBrush.DeleteObject();//�ͷŲ��õĻ�ˢ
}


BOOL CGreedySnakeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN)
	{
		//MessageBox(L"�������£�");
		switch (pMsg->wParam)
		{
		case VK_UP://direction ���������ҡ��ֱ�Ϊ ��1234��
			//MessageBox(L"�����¼���");
			if (snake[0].direction != 2)
				snake[0].direction = 1;//���߷���Ϊ���¡�ʱ���ܽ���ͷ�������Ϊ���ϡ����������
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);
	//ע��getClientRect��rect������λ�ã����top��left��ȻΪ0
	pWnd->GetWindowRect(&rect);//�õ����windows����ؼ���С
	ScreenToClient(&rect); //ת��client
	CPoint rtOrigin = rect.TopLeft();
	if (TRUE == PtInRect(&rect, point))
	{
		str.Format(L"���λ�ã�%d,%d", point.x-rtOrigin.x, point.y-rtOrigin.y);
		AfxMessageBox(str);
	}

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CGreedySnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CString score;
	//�����߳����������Ѷȣ����ֱ���370ms��270ms,200ms,100ms����һ�����ƶ�
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
		AfxMessageBox(L"��Ӯ�ˣ�");
	}

	score.Format(L"�÷�:%d!", (snake[0].len - 3) * 10);
	//ײ���ж�
	int gameLeftBorder = 0, gameRightBorder = 324;
	if (snake[0].x*20  > gameRightBorder || snake[0].y*20  > gameRightBorder || snake[0].x*20 < gameLeftBorder || snake[0].y*20 < gameLeftBorder){
		KillTimer(1);
		score = CString(L"ײ���߽磬") + score;
		AfxMessageBox(score);
		Invalidate(TRUE);
		m_init = false;
	}
	//������ײ�ж�
	if (snake[0].len>3)//���ٵ���4���߲ſ�����ײ
	for (int sn = snake[0].len - 1; sn>0; sn--)
	{
		if (snake[0].x * 20 == snake[sn].x * 20 && snake[0].y * 20 == snake[sn].y * 20)//����ͷ�������Ƿ��غ��ж��Ƿ���ײ
		{
			KillTimer(1);
			score = CString(L"������ײ��") + score;
			AfxMessageBox(score);
			Invalidate(TRUE);
			m_init = false;
		}
	}

	//---------------����ͼ��---------------
	CWnd *pWndLen = GetDlgItem(IDC_STATUS);
	CString str;
	str.Format(L"̰���߳��ȣ� %d ", snake[0].len);
	pWndLen->SetWindowTextW(str);
	CWnd *pWndLevel = GetDlgItem(IDC_LEVEL);
	str.Format(L"��ǰ�ȼ��� %d ", m_GameLevel);
	pWndLevel->SetWindowTextW(str);

	CWnd *pWnd = GetDlgItem(IDC_GAMEAREA);
	CDC *pDC = pWnd->GetDC();
	COLORREF bgColor = GetSysColor(COLOR_BTNFACE);//��ȡ�Ի���Ĭ�ϱ�����ɫ������β�ػ�Ϊ����ɫ�Դﵽ������β��Ч��
	//pDC->SetBkColor(bgColor);//��GetBKColorһ���������õ�/�޸�����ı�����ɫ

	CBrush newBrush1,*oldBrush1;
	newBrush1.CreateSolidBrush(bgColor);
	oldBrush1 = pDC->SelectObject(&newBrush1);
	CRect rect(snake[snake[0].len - 1].x * 20, snake[snake[0].len - 1].y * 20, (snake[snake[0].len - 1].x + 1) * 20, (snake[snake[0].len - 1].y + 1) * 20);
	pDC->FillRect(rect, &newBrush1);
	pDC->SelectObject(oldBrush1);//��ԭ
	newBrush1.DeleteObject();//�ͷ��»�ˢ�ڴ�

	//����ǰ��һ����ͷ����Ҫ���⴦��
	for (int i = snake[0].len - 1; i>0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	//���߷����ж�,����ͷ��λ��
	if (snake[0].direction == 1)snake[0].y--;//��
	if (snake[0].direction == 2)snake[0].y++;//��
	if (snake[0].direction == 3)snake[0].x--;//��
	if (snake[0].direction == 4)snake[0].x++;//��
	CBrush newBrush2, *oldBrush2;
	newBrush2.CreateSolidBrush(RGB(255, 255, 255));
	oldBrush2 = pDC->SelectObject(&newBrush2);
	pDC->Rectangle(snake[0].x * 20, snake[0].y * 20, (snake[0].x + 1) * 20, (snake[0].y + 1) * 20);//��������ͷ
	pDC->SelectObject(oldBrush2);
	newBrush2.DeleteObject();

	//�жϳԶ�������ײ���ͳԣ�����β�����һ��
	if (food.hasfood == true && snake[0].x * 20 == food.x * 20 && snake[0].y * 20 == food.y * 20)
	{
		snake[0].len++;
		food.hasfood = false;//�Ե���ʳ��
		/*snake[snake[0].len - 1].x = snake[snake[0].len - 2].x;
		snake[snake[0].len - 1].y = snake[snake[0].len - 2].y;*/
	}
	//���ʳ�ﱻ���� ������
	if (food.hasfood == false)//û��ʳ����
	{
		srand((unsigned)time(NULL));//�趨α���������
		while (true){
			food.x = rand() % 16;//ʹfood�������귶ΧΪ[0,15]
			food.y = rand() % 16;
			int isfo = snake[0].len - 1;
			for (; isfo >= 0; isfo--){
				if (food.x * 20 == snake[isfo].x * 20 && food.y * 20 == snake[isfo].y * 20)//��������ɵ�ʳ���������ϣ�����������
				{
					break;
				}
			}
			if (isfo == -1)//������ʳ�ﲻ��������
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
	// TODO:  �ڴ���������������
	SetTimer(1, 10, NULL);//kill֮���״̬�Ѿ�������ȫ�ֱ���snake��food��
}


void CGreedySnakeDlg::OnExit()
{
	// TODO:  �ڴ���������������
	AfxMessageBox(L"�˳���Ϸ!");
	exit (0);
}

void CGreedySnakeDlg::OnStart()
{
	// TODO:  �ڴ���������������
	SetTimer(1, 3000, NULL);
	AfxMessageBox(L"3���ʼ��Ϸ!");
	init();
}


void CGreedySnakeDlg::OnPause()
{
	// TODO:  �ڴ���������������
	
	KillTimer(1);
	AfxMessageBox(L"��ͣ��Ϸ!");
}



void CGreedySnakeDlg::init()
{
	//��ʼ���߳�ʼλ�ã��Լ��߳�ʼ�ж����򣬳�ʼ����Ϊ3��Ĭ��û��ʳ��
	if (false == m_init){
		snake[0].x = 10;
		snake[0].y = 10;
		snake[1].x = 11;
		snake[1].y = 10;
		snake[2].x = 12;
		snake[2].y = 10;
		//---���Ա߽����---
		//��߽磺��0��0�����ұ߽�(324,324)ӳ�䵽������Ϊ(0,0)��(15,15)
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
	// TODO:  �ڴ���������������
	CAboutDlg cAboutDlg;
	cAboutDlg.DoModal();
}
