#include<stdio.h>
#include<conio.h>
#include <graphics.h>
#include <time.h>
/**********全局变量区************/
int i, j;//循环变量
int count = 0;//计步数
int mode;//选择模式
int temp;//交换二维数组数值的变量
int arr[5][5];//定义一个二维数组

/**********函数声明区************/
int main();
void chooseMode();//选择游戏界面
void createMap();//初始化游戏界面
void startGame();//游戏开始界面
void contralDirection(int x);
void direction(int x);//方向控制的实现
void contralGame();//游戏控制的实现  
void createCube();//开局产生随机布局
void printNumber(int x);
void rebuild();
void judge();//判断输赢
void printsteps();//显示步数
 /**********函数实现区************/
void chooseMode()
{
	setfillcolor(RGB(250, 248, 239));
	solidrectangle(0, 0, 640, 480);
	setfillcolor(RGB(244, 177, 121));
	solidroundrect(140, 60, 500, 160, 15, 15);
	solidroundrect(140, 190, 500, 290, 15, 15);
	solidroundrect(140, 320, 500, 420, 15, 15);
	RECT a{ 140, 60, 500, 160 };
	RECT b{ 140, 190, 500, 290 };
	RECT c{ 140, 320, 500, 420 };
	RECT d{ 140,0,500,60 };
	setbkcolor(RGB(244, 177, 121));
	settextstyle(60, 34, _T("楷体"));
	drawtext(_T("3×3"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("4×4"), &b, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("5×5"), &c, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(30, 17, _T("楷体"));
	solidroundrect(192, 12, 452, 52, 15, 15);
	drawtext(_T("数字华容道"), &d, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(60, 34, _T("楷体"));
	RECT n{ 14,60,130,420 };
	solidroundrect(14, 60, 130, 420, 15, 15);
	drawtext(_T("鼠标选择模式"), &n, DT_CENTER | DT_WORDBREAK);
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x >= 140 && m.x <= 500 && m.y >= 60 && m.y <= 160)
			{
				mode = 3;
				break;
			}
			if (m.x >= 140 && m.x <= 500 && m.y >= 190 && m.y <= 290)
			{
				mode = 4;
				break;
			}
			if (m.x >= 140 && m.x <= 500 && m.y >= 320 && m.y <= 420)
			{
				mode = 5;
				break;
			}
		}
	}
}
void createMap()
{
	count = 0;
	setfillcolor(RGB(187, 173, 160));
	solidroundrect(140, 60, 500, 420, 15, 15);
	setfillcolor(RGB(205, 193, 180));
	if (mode == 3)
	{
		for (i = 0; i < mode; i++)
		{
			for (j = 0; j < mode; j++)
			{
				solidroundrect(140 + 9 * (i + 1) + 108 * i, 60 + 9 * (j + 1) + 108 * j, 140 + 9 * (i + 1) + 108 * (i + 1), 60 + 108 * (j + 1) + 9 * (j + 1), 15, 15);
			}
		}
	}
	if (mode == 4)
	{
		for (i = 0; i < mode; i++)
		{
			for (j = 0; j < mode; j++)
			{
				solidroundrect(140 + 8 * (i + 1) + 80 * i, 60 + 8 * (j + 1) + 80 * j, 140 + 8 * (i + 1) + 80 * (i + 1), 60 + 80 * (j + 1) + 8 * (j + 1), 15, 15);
			}
		}
	}
	if (mode == 5)
	{
		for (i = 0; i < mode; i++)
		{
			for (j = 0; j < mode; j++)
			{
				solidroundrect(140 + 5 * (i + 1) + 66 * i, 60 + 5 * (j + 1) + 66 * j, 140 + 5 * (i + 1) + 66 * (i + 1), 60 + 66 * (j + 1) + 5 * (j + 1), 15, 15);
			}
		}
	}

	for (i = 0; i < mode; i++)
	{
		for (j = 0; j < mode; j++)
		{
			arr[i][j] = 0;
		}
	}
	settextstyle(30, 17, _T("楷体"));
	settextcolor(RGB(245, 249, 241));
	setbkcolor(RGB(143, 122, 102));
	setfillcolor(RGB(143, 122, 102));
	solidroundrect(192, 12, 452, 52, 15, 15);
	RECT a{ 140,0,500,60 };
	drawtext(_T("数字华容道"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20, 13, _T("楷体"));
	RECT m{ 14,60,130,420 };
	solidroundrect(14, 60, 130, 420, 15, 15);
	drawtext(_T("ESC\n\n主菜单\n\n\n空格键\n\n开始游戏\n\n\nW上\n\nS下\n\nA左\n\nD右"), &m, DT_CENTER | DT_WORDBREAK);
	printsteps();
}
void startGame()
{
	char c = 0;
	int a = 0;
	while (a != 1)
	{
		if (kbhit())
			c = getch();
		switch (c)
		{
		case 27:
			main();
		case ' ':
			createCube();
			a = 1;
		}
	}
}
void direction(int x)
{
	int c = 0;
	if (x == 1)
	{
		for (i = 0; i < mode; i++)
		{
			for (j = 0; j < mode - 1; j++)
			{
				if (arr[j][i] == 0)
				{
					c = 1;
					break;
				}
			}
			if (c == 1)
				break;
		}
		if (c == 1)
		{
			temp = arr[j][i];
			arr[j][i] = arr[j+1][i];
			arr[j + 1][i] = temp;
			rebuild();
			c = 0;
			count++;
			printsteps();
		}
	}
	if (x == 2)
	{
		for (i = mode - 1; i > 0; i--)
		{
			for (j = 0; j < mode; j++)
			{
				if (arr[i][j] == 0)
				{
					c = 2;
					break;
				}
			}
			if (c == 2)
				break;
		}
		if (c == 2)
		{
			temp = arr[i - 1][j];
			arr[i - 1][j] = arr[i][j];
			arr[i][j] = temp;
			rebuild();
			c = 0;
			count++;
			printsteps();
		}
	}
	if (x == 3)
	{
		for (i = 0; i < mode - 1; i++)
		{
			for (j = 0; j < mode; j++)
			{
				if (arr[j][i] == 0)
				{
					c = 3;
					break;
				}
			}
			if (c == 3)
				break;
		}
		if (c == 3)
		{
			temp = arr[j][i];
			arr[j][i] = arr[j][i+1];
			arr[j][i+1] = temp;
			rebuild();
			c = 0;
			count++;
			printsteps();
		}
	}
	if (x == 4)
	{
		for (i = mode - 1; i > 0; i--)
		{
			for (j = 0; j < mode; j++)
			{
				if (arr[j][i] == 0)
				{
					c = 4;
					break;
				}
			}
			if (c == 4)
				break;
		}
		if (c == 4)
		{
			temp = arr[j][i];
			arr[j][i] = arr[j][i-1];
			arr[j][i-1] = temp;
			rebuild();
			c = 0;
			count++;
			printsteps();
		}
	}
}
void contralGame()
{
	char c = 0;
	while (1)
	{
		c = 0;
		if (kbhit())     //获取键盘信息
			c = getch();
		switch (c)
		{
		case 27:
			main();
		case 'w':
			direction(1);
			judge();
			break;
		case 's':
			direction(2);
			judge();
			break;
		case 'a':
			direction(3);
			judge();
			break;
		case 'd':
			direction(4);
			judge();
			break;
		case' ':
			createMap();
			createCube();
			break;
		}
	}
}
void createCube()
{
	srand((unsigned)time(NULL));
	int m = 1;
	int t, t1, t2;
	int s = 0;
	for (i = 0; i < mode; i++)//先生成正确的状态
	{
		for (j = 0; j < mode; j++)
		{
			arr[i][j] = m;
			m++;
		}
	}
	arr[mode - 1][mode - 1] = 0;//空位的值设为0
	t1 = 1000;
	while (t1 != 1)//1000循环随机调换位置使之达到混乱状态
	{
		t1--;
		t = rand() % (mode - 1)+1;
		for (i = 0; i < t; i++)//横向随机调换
		{
			for (j = 0; j < t + 1; j++)
			{
				if ((i + 1) != (mode - 1) || j != (mode - 1))
				{
					temp = arr[i][j];
					arr[i][j] = arr[i + 1][j];
					arr[i + 1][j] = temp;
					count++;
				}
			}
		}
		t2 = rand() % (mode - 1) + 1;
		for (i = 0; i < t2 + 1; i++)//纵向随机调换
		{
			for (j = 0; j <t2; j++)
			{
				if ((j + 1) != (mode - 1) || i != (mode - 1))
				{
					temp = arr[i][j];
					arr[i][j] = arr[i][j + 1];
					arr[i][j + 1] = temp;
					count++;
				}
			}
		}
	}
	if (count % 2 != 0)//判断调换位置次数的奇偶性
	{
		temp = arr[mode- 3][mode-3];
		arr[mode- 3][mode-3] = arr[mode - 2][mode-2];
		arr[mode - 2][mode-2] = temp;
	}
	for (i = 0; i < mode; i++)
	{
		for (j = 0; j < mode; j++)
		{
			for (int k = 0; k < (mode*mode); k++)        //遍历数组，把数组里面的数字实际打印出来
			{
				if (arr[i][j] == k)
					printNumber(k);
			}
		}
	}
	count = 0;
}
void rebuild()
{
	for (i = 0; i < mode; i++)
	{
		for (j = 0; j < mode; j++)
		{
			for (int k = 0; k<(mode*mode); k++)
			{
				if (arr[i][j] == k)
					printNumber(k);
			}
		}
	}
}

void judge()
{
	int m = 1;
	int n = 0;
	for (i = 0; i < mode; i++)
	{
		for (j = 0; j < mode; j++)
		{
			if (arr[i][j] == m)
			{
				n++;
			}
			m++;
		}
	}
	if (n == (mode*mode -1))
	{
		RECT a{ 140,60,500,420 };
		settextstyle(50, 30, _T("楷体"));
		settextcolor(RGB(118, 110, 101));
		drawtext(_T("恭喜你!"), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}
void printNumber(int x)
{
	int g, h;
	if (mode == 3)
	{
		g = 9;
		h = 108;
	}
	if (mode == 4)
	{
		g = 8;
		h = 80;
	}
	if (mode == 5)
	{
		g = 5;
		h = 66;
	}
	if (x == 0)
	{
		setfillcolor(RGB(205, 193, 180));
		solidroundrect(140 + g * (j + 1) + h * j, 60 + g * (i + 1) + h * i, 140 + g * (j + 1) + h * (j + 1), 60 + h * (i + 1) + g * (i + 1), 15, 15);
		RECT a{ 140 + g * (j + 1) + h * j, 60 + g * (i + 1) + h * i, 140 + g * (j + 1) + h * (j + 1), 60 + h * (i + 1) + g * (i + 1) };
	}
	else
	{
		setfillcolor(RGB(237, 228, 218));
		solidroundrect(140 + g * (j + 1) + h * j, 60 + g * (i + 1) + h * i, 140 + g * (j + 1) + h * (j + 1), 60 + h * (i + 1) + g * (i + 1), 15, 15);
		RECT a{ 140 + g * (j + 1) + h * j, 60 + g * (i + 1) + h * i, 140 + g * (j + 1) + h * (j + 1), 60 + h * (i + 1) + g * (i + 1) };
		settextstyle(50, 30, _T("黑体"));
		settextcolor(RGB(118, 110, 101));
		setbkcolor(RGB(237, 228, 218));
		TCHAR Ls[10];
		_stprintf(Ls, _T("%d"), x);
		drawtext(_T(s), &a, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}
	
void printsteps()
{
	settextstyle(30, 17, _T("楷体"));
	settextcolor(RGB(245, 249, 241));
	setbkcolor(RGB(187, 172, 160));
	setfillcolor(RGB(187, 172, 160));
	solidroundrect(514, 160, 629, 324, 15, 15);
	RECT w{ 514, 170, 629, 240 };
	RECT r{ 514, 220, 629, 300 };
	TCHAR Ls[10];
	_stprintf(Ls, _T("%d"), count);
	drawtext(_T("步数"), &w, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(s), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}	
/*******************主函数*******************/
int main()
{
	initgraph(640, 480);
	chooseMode();
	createMap();
	startGame();
	contralGame();
	getch();
	closegraph();
	return 0;
}
