
#include "CAnimal.h"
#include "Console.h"
#include "CVEHICLE.h"

void background()
{
	PlaySound(TEXT("a.wav"), NULL,SND_LOOP | SND_ASYNC);
	
}

void init()
{
	for (int i = 0; i <= HEIGHT ; i++)
		for (int j = 0; j <= WIDTH; j++)
			buffer.square(i, j, ' ');
}
void displayAnimal(CBIRD b, CDINOSAUR d)
{
	//Draw background
	for (int i = 0; i <= HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 && j == WIDTH - 1) buffer.square(i, j, (char)187);
			else if (i % 5 == 0)
			{
				if (j == WIDTH - 1) buffer.square(i, j, (char)185);
				else buffer.square(i, j, (char)205);
			}
			else if (j == WIDTH - 1)
			 buffer.square(i, j, (char)186);
		}
	//Draw Bird
	b.Move(9);
	//Draw Dinosaur
	d.Move(10);

	GotoXY(0, 0);
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			TextColor(buffer.table[i][j].color);
			putchar(buffer.table[i][j].character);
			buffer.table[i][j].character = ' ';
		}
		if (i < HEIGHT - 1)
			putchar('\n');
	}

}

void handleAnimal(CBIRD& b, CDINOSAUR& d)
{
	b.goRight();
	if (b.getX() == WIDTH - lengthB) b.Update(1, 11);
	d.goRight();
	if (d.getX() == WIDTH - lengthD) d.Update(1, 21);
}

void displayVehicle(vector<CTRUCK> tArr, CCAR c, CTRAFFICLIGHT light)
{
	//Draw background
	for (int i = 0; i <= HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 && j == WIDTH - 1) buffer.square(i, j, (char)187);
			else if (i % 5 == 0)
			{
				if (j == WIDTH - 1) buffer.square(i, j, (char)185);
				else buffer.square(i, j, (char)205);
			}
			else if (j == WIDTH - 1)
				buffer.square(i, j, (char)186);
		}

	//Draw Truck
	for (int i = 0; i < tArr.size(); i++)
		tArr[i].Move(11);
	//Draw Car
	c.Move(12);
	//Draw light
	light.print(WIDTH, 6);
	light.print(WIDTH, 16);

	GotoXY(0, 0);
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			TextColor(buffer.table[i][j].color);
			putchar(buffer.table[i][j].character);
			buffer.table[i][j].character = ' ';
		}
		if (i < HEIGHT - 1)
			putchar('\n');
	}

}

void handleVehicle(vector<CTRUCK>& tArr, CCAR& c, CTRAFFICLIGHT& light)
{
	for (int i = 0; i < tArr.size(); i++)
	{
		tArr[i].goRight(light);
		if (tArr[i].getX() == WIDTH - lengthT) tArr[i].Update(1, 6);
	}
	c.goRight(light);
	if (c.getX() == WIDTH - lengthC) c.Update(1, 16);
	if (light.isRed()) {
		Sleep(2000);
		light.changeColor();
	}
	else if (tArr[0].getX() % 20 == 0)
		light.changeColor();
}

int main()
{
	FixConsoleWindow();
	ShowCur(0);
	DisableSelection();
	ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);
	system("title Game");
	init();
	CBIRD b;
	CDINOSAUR d;
	while (1)
	{
		displayAnimal(b,d);
		handleAnimal(b,d);
		Sleep(5);
	}

	/*HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)printB, NULL, NULL,NULL);
	HANDLE h1 = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)printD, NULL, NULL, NULL);
	WaitForSingleObject(h, INFINITE);
	CloseHandle(h);
	WaitForSingleObject(h1, INFINITE);
	CloseHandle(h1);*/
	/*thread Bird(t1);
	thread Dinosaur(t2);
	if (Bird.joinable()) Bird.join();
	if (Dinosaur.joinable()) Dinosaur.join();*/
	/*thread b(background);
	thread Bird(printB);
	thread Dinosaur(printD);
	Bird.join();
	Dinosaur.join();
	b.join();*/
	//CDINOSAUR d;
	//d.Tell();
	//background();
	
	/*thread dino(&CDINOSAUR::Tell,d);
	dino.join();
	*/
	
	return 0;
}