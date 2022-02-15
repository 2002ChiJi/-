#pragma comment(linker, "/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
#include <array>
#include <ctime>
#include <graphics.h>

#define HIGH  650
#define WIDTH 850
#define X_SIZE 50
#define Y_SIZE 50

struct Point
{
	float x, y;
	unsigned char r, g, b;
	Point(int X = NULL, int Y = NULL, unsigned char R = 0, unsigned char G = 0, unsigned char B = 0) :
		x(X), y(Y), r(R), g(G), b(B) {}
	inline  COLORREF GetRgb() { return(RGB(r, g, b)); }
};
static std::array< std::array<float, (WIDTH / X_SIZE) + 1>, (HIGH / Y_SIZE) + 1> Direction;	/*指定每个网格顶点移动的步长*/
static std::array< std::array<Point, (WIDTH / X_SIZE) + 1>, (HIGH / Y_SIZE) + 1> verteics;
static std::array<decltype(verteics), 500> OldVerteics;		/*储存经过变换的顶点网格*/
static short Sign[2] = { -1,1 };

inline void InitColor(unsigned char& Red, unsigned char& Green, unsigned char& Blue)		/*确定初始的颜色，此处可以自由修改以呈现出不同的颜色变换*/
{
	Red = 30, Green = 85, Blue = rand() % 50 + 200;
}

inline void Shader(unsigned char& Red, unsigned char& Green, unsigned char& Blue)			/*根据传入的RGB计算出新的RGB，此处可以自由修改以呈现出不同的颜色变换*/
{
	if (Blue >= 250)Blue = 245;
	else if (Blue <= 200)Blue = 205;
	else 		Blue += Sign[rand() % 2];
}

void InitVerteics()
{
	unsigned char Red, Green, Blue;
	int StepXY[2] = { 0,0 };
	for (auto& Y : verteics)
	{
		for (auto& X : Y)
		{
			InitColor(Red, Green, Blue);
			X = Point(StepXY[0], StepXY[1], Red, Green, Blue);
			StepXY[0] += X_SIZE;
		}
		StepXY[0] = 0, StepXY[1] += Y_SIZE;
	}
	for (auto& Y : Direction)
		for (auto& X : Y)X = Sign[rand() % 2] * (float(rand() % 100) / 100);
}

void ChangeVerteics()
{
	for (int Y = 0; Y < (HIGH / Y_SIZE) + 1; Y++)
	{
		for (int X = 0; X < (WIDTH / X_SIZE) + 1; X++)
		{
			if (rand() % 4 == NULL)			/*有1/4的概率执行if里面的代码*/
			{
				verteics[Y][X].x += Direction[Y][X], verteics[Y][X].y += Direction[Y][X];

				if (rand() % 10 == NULL)
					Direction[Y][X] = Sign[rand() % 2] * (float(rand() % 100) / 100);
			}
			Shader(verteics[Y][X].r, verteics[Y][X].g, verteics[Y][X].b);
		}
	}
}

void DrawVerteics(decltype(verteics)& verteics_)
{
	POINT pts[4];		/*储存要绘制的网格顶点*/
	unsigned int MaxXY[2] = { verteics_[0].size(),verteics_.size() };

	for (unsigned int Y = 0; Y < MaxXY[1] - 1; Y++)
	{
		for (unsigned int X = 0; X < MaxXY[0] - 1; X++)
		{
			pts[0].x = verteics_[Y][X].x, pts[0].y = verteics_[Y][X].y;
			pts[1].x = verteics_[Y + 1][X].x, pts[1].y = verteics_[Y + 1][X].y;
			pts[2].x = verteics_[Y][X + 1].x, pts[2].y = verteics_[Y][X + 1].y;
			pts[3].x = verteics_[Y + 1][X + 1].x, pts[3].y = verteics_[Y + 1][X + 1].y;

			setfillcolor(verteics_[Y][X].GetRgb()), solidpolygon(pts, 3);				/*要绘制两个相连三角形，所以共用一部分顶点*/
			setfillcolor(verteics_[Y + 1][X + 1].GetRgb()), solidpolygon(pts + 1, 3);
		}
	}
}

int main()
{
	srand(time(NULL));
	initgraph(WIDTH, HIGH);
	for (InitVerteics();; verteics = OldVerteics[0])
	{
		for (auto& now : OldVerteics)	ChangeVerteics(), now = verteics;		/*向OldVerteics写入一系列经过变换的网格顶点，形成一帧帧画面*/
		for (auto now = OldVerteics.begin(); now != OldVerteics.end(); now++, Sleep(50))	DrawVerteics(*now);	/*播放每一帧*/
		for (auto now = OldVerteics.rbegin(); now != OldVerteics.rend(); now++, Sleep(50))	DrawVerteics(*now);	/*倒放每一帧*/
	}
}