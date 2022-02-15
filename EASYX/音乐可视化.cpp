#include <graphics.h>
#include <math.h>
#include <time.h>

int main()
{
	double r = 100;
	initgraph(1280, 720);

	srand(time(NULL));
	circle(640, 360, 100);
	setbkcolor(RGB(10, 10, 10));
	for (double x = 0.01;; x = 0.01)
	{
		for (; x < 6.28; x += 0.01, Sleep(10), cleardevice())
		{
			BeginBatchDraw();
			circle(640, 360, r);
			circle(r * sin(x) + 640, r * cos(x) + 360, rand() % 20);
			circle(r * sin(x - 3.14) + 640, r * cos(x - 3.14) + 360, rand() % 20);
			circle(r * sin(x - 1.57) + 640, r * cos(x - 1.57) + 360, rand() % 20);
			circle(r * sin(x + 1.57) + 640, r * cos(x + 1.57) + 360, rand() % 20);
			r = 100 + rand() % 100;
			setlinecolor(RGB(rand() % 256, rand() % 256, rand() % 256));
			EndBatchDraw();
		}
	}

	system("pause");
	return 0;
}

#include <graphics.h> 
#include <time.h>

int main()
{
	initgraph(640, 480);	// 初始化图形窗口
	srand(time(NULL));

	setlinecolor(GREEN);
	for (int range=20,sign=1;; Sleep(10), cleardevice())
	{
		BeginBatchDraw();
		if (rand() % 2)
			sign = -sign;
		POINT pts[] = { {150, 200},
	{160 + sign*rand()%range, 150 + sign*rand()%range},
	{240 + sign*rand()%range, 150 + sign*rand()%range},
	{250 + sign*rand()%range, 100 + sign*rand()%range},
	{260 + sign*rand()%range, 150 + sign*rand()%range},
	{340 + sign*rand()%range, 150 + sign*rand()%range},
	{350, 200} };
		polybezier(pts, 7);		//画绿色的贝塞尔曲线
		EndBatchDraw();
	}

	return 0;
}
