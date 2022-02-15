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
static std::array< std::array<float, (WIDTH / X_SIZE) + 1>, (HIGH / Y_SIZE) + 1> Direction;	/*ָ��ÿ�����񶥵��ƶ��Ĳ���*/
static std::array< std::array<Point, (WIDTH / X_SIZE) + 1>, (HIGH / Y_SIZE) + 1> verteics;
static std::array<decltype(verteics), 500> OldVerteics;		/*���澭���任�Ķ�������*/
static short Sign[2] = { -1,1 };

inline void InitColor(unsigned char& Red, unsigned char& Green, unsigned char& Blue)		/*ȷ����ʼ����ɫ���˴����������޸��Գ��ֳ���ͬ����ɫ�任*/
{
	Red = 0, Green = 50, Blue = rand() % 50 + 180;
}

inline void Shader(unsigned char& Red, unsigned char& Green, unsigned char& Blue)			/*���ݴ����RGB������µ�RGB���˴����������޸��Գ��ֳ���ͬ����ɫ�任*/
{
	Blue += Sign[rand() % 2] * 2;
	if (Blue >= 255 || Blue < 180)Blue = rand() % 50 + 180;
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
	for (int Y = 0; Y < (HIGH / Y_SIZE); Y++)
	{
		for (int X = 0; X < (WIDTH / X_SIZE); X++)
		{
			if (rand() % 4 == NULL)			/*��1/4�ĸ���ִ��if����Ĵ���*/
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
	POINT pts[4];		/*����Ҫ���Ƶ����񶥵�*/
	unsigned int MaxXY[2] = { verteics_[0].size(),verteics_.size() };

	for (unsigned int Y = 0; Y < MaxXY[1] - 1; Y++)
	{
		for (unsigned int X = 0; X < MaxXY[0] - 1; X++)
		{
			pts[0].x = verteics_[Y][X].x, pts[0].y = verteics_[Y][X].y;
			pts[1].x = verteics_[Y + 1][X].x, pts[1].y = verteics_[Y + 1][X].y;
			pts[2].x = verteics_[Y][X + 1].x, pts[2].y = verteics_[Y][X + 1].y;
			pts[3].x = verteics_[Y + 1][X + 1].x, pts[3].y = verteics_[Y + 1][X + 1].y;

			setfillcolor(verteics_[Y][X].GetRgb()), solidpolygon(pts, 3);				/*Ҫ�����������������Σ����Թ���һ���ֶ���*/
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
		for (auto& now : OldVerteics)	ChangeVerteics(), now = verteics;		/*��OldVerteicsд��һϵ�о����任�����񶥵㣬�γ�һ֡֡����*/
		for (auto now = OldVerteics.begin(); now != OldVerteics.end(); now++, Sleep(50))	DrawVerteics(*now);	/*����ÿһ֡*/
		for (auto now = OldVerteics.rbegin(); now != OldVerteics.rend(); now++, Sleep(50))	DrawVerteics(*now);	/*����ÿһ֡*/
	}
}