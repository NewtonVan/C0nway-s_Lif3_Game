#include <iostream>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#define CELLCOLOR 4
#define DEATHCOLOR 1
using namespace std;

const char UP= 72;
const char DOWN= 80;
const char LEFT= 75;
const char RIGHT= 77;
const char MOVE= ' ';
const char LIVE= '0';
const char DEATH= '*';
const int WIDTH= 30;
const int LENGTH= 56;
int board[WIDTH][LENGTH];
struct cell
{
	int x, y;
	cell(){};
	cell(int xx, int yy) : x(xx), y(yy) {}
}player;

void SetChessColor(int i, int j);
void GoToxy(int x, int y);
void Lif3_G4me(void);
int AffineX(int x);
int AffineY(int y);
void FormGame();
void Animation();
void Update();
bool InBoard(int x, int y);
void Operation(int x, int y);
bool LifeExist();
void DrawFrame();

int main()
{
    SetConsoleTitle("C0nway's G4me 0f L!fe!!!!");
    system("color f5");
	Lif3_G4me();
	return 0;
}
void SetCellColor(int i, int j)
{
    HANDLE c3ll;
    c3ll= GetStdHandle(STD_OUTPUT_HANDLE);
    if (board[i][j])
        SetConsoleTextAttribute(c3ll, DEATHCOLOR+15*0x10);
    else
        SetConsoleTextAttribute(c3ll, CELLCOLOR+15*0x10);
}
void GoToxy(int x, int y)
{
    HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X=y;
    pos.Y=x;
    SetConsoleCursorPosition(handle, pos);
}
void Lif3_G4me()
{
	DrawFrame();
	GoToxy(AffineX(1), AffineY(1));
	FormGame();
	Animation();
}
int AffineX(int x)
{
	return x+10;
}
int AffineY(int y)
{
	return y*2+5;
}
void FormGame()
{
	memset(board, 0, sizeof(board));
	player= cell(1, 1);
	int nxtx, nxty;
	char opr;
	while ('\r'!= (opr= getch())){
		if (UP== opr){
			nxtx= player.x-1;
			nxty= player.y;
			Operation(nxtx, nxty);
		}
		else if (DOWN== opr){
			nxtx= player.x+1;
			nxty= player.y;
			Operation(nxtx, nxty);
		}
		else if (LEFT== opr){
			nxtx= player.x;
			nxty= player.y-1;
			Operation(nxtx, nxty);
		}
		else if (RIGHT== opr){
			nxtx= player.x;
			nxty= player.y+1;
			Operation(nxtx, nxty);
		}
		else if (MOVE== opr){
			char cl;
			board[player.x][player.y]^= 1;
			cl= board[player.x][player.y] ? LIVE : DEATH;
			SetCellColor(player.x, player.y);
			putchar(cl);
			GoToxy(AffineX(player.x), AffineY(player.y));
		}
		else {
			continue;
		}
	}
}
void Animation()
{
	while (LifeExist()){
		Update();
		DrawFrame();
		Sleep(23);
	}
}
void Update()
{
	int neibr, tboard[WIDTH][LENGTH];
	for (int i= 1; i< WIDTH-1; ++i){
		for (int j= 1; j< LENGTH-1; ++j){
			neibr= 0;
			for (int k= -1; k< 2; ++k){
				for (int l= -1; l< 2; ++l){
					neibr+= board[i+k][j+l];
				}
			}
			neibr-= board[i][j];
			if (board[i][j]){
				tboard[i][j]= neibr<2 || neibr >3 ? 0 : 1;
			}
			else {
				tboard[i][j]= 3== neibr ? 1 : 0;
			}
		}
	}
	for (int i= 1; i< WIDTH-1; ++i){
		for (int j= 1; j< LENGTH-1; ++j){
			board[i][j]= tboard[i][j];
		}
	}
}
bool InBoard(int x, int y)
{
	return x> 0 && x< WIDTH-1 && y> 0 && y< LENGTH-1;
}
void Operation(int x, int y)
{
	if(InBoard(x, y)){
		player.x= x;
		player.y= y;
		GoToxy(AffineX(player.x), AffineY(player.y));
	}
}
bool LifeExist()
{
	for (int i= 0; i< WIDTH; ++i){
		for (int j= 0; j< LENGTH; ++j){
			if (board[i][j]){
				return true;
			}
		}
	}
	return false;
}
void DrawFrame()
{
	char cl;
	for (int i= 0; i< WIDTH; ++i){
		for (int j= 0; j< LENGTH; ++j){
			GoToxy(AffineX(i), AffineY(j));
			SetCellColor(i, j);
			cl= board[i][j] ? LIVE : DEATH;
			putchar(cl);
			GoToxy(AffineX(i), AffineY(j));
		}
	}
}