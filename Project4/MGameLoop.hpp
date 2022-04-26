#pragma once
#include <chrono>
#include <thread>
#include "MConsolUtil.hpp"
#include "Player.hpp"
#include "Trab.hpp"
#include <list>
#include <random>

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private:
		bool _isGameRunning, gameOver;
		MConsoleRenderer cRenderer;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		Player* p = new Player();
		Trab* t[6] = {new Trab(), new Trab(), new Trab(), new Trab(), new Trab(), new Trab()};
		int score, scoreCount;
	public:
		MGameLoop()
		{
			_isGameRunning = false;
			startRenderTimePoint = chrono::system_clock::now();
			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			gameOver = false;
			score = 0;
			scoreCount = 0;
		}
		~MGameLoop()
		{
			delete(p);
			for (size_t i = 0; i < 6; i++)
				delete(t[i]);
			delete(t);
		}
		
		void Run()
		{
			_isGameRunning = true;
			Initialize();
			while (_isGameRunning)
			{
				Input();
				Update();
				Render();

			}
			Release();
		}
		void Stop()
		{
			_isGameRunning = false;
		}
	private:
		void Initialize() {}
		void Release() {}
		void Input()
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_SPACE) & 0x8001)
			{
				if (!gameOver)
					p->isSpacePressed();
				else
				{
					for (size_t i = 0; i < 6; i++)
					{
						t[i]->Hide();
					}
					p->Reset();
					score = 0;
					scoreCount = 0;
					gameOver = false;
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
			{
				if (!gameOver)
				{
					p->isDownPressed();
				}
			}
		}
		void Update()
		{
			if (!gameOver)
			{
				random_device rd;
				mt19937 gen(rd());
				p->filghtCounter();
				for (size_t i = 0; i < 6; i++)
				{
					if (t[i]->isOn)
					{
						t[i]->MoveConter();
						if (t[i]->x == 0)
							t[i]->Hide();
					}
				}
				uniform_int_distribution<int> dis(1, 20);
				if (dis(gen) == 1)
				{
					int arrNum = -1;
					for (size_t i = 0; i < 6; i++)
					{
						if (!(t[i]->isOn))
						{
							arrNum = i;
							break;
						}
					}
					if (arrNum != -1)
					{
						int count = 0;
						for (size_t i = 0; i < 6; i++)
						{
							if (t[i]->x < 35)
								count++;
						}
						if (count == 6)
						{
							t[arrNum]->Initialize();
						}
					}
				}
				for (size_t i = 0; i < 6; i++)
				{
					if (t[i]->isOn && t[i]->x == 20)
					{
						if (p->y == t[i]->y || (t[i]->length == 2 && p->y == t[i]->y - 1))
						{
							gameOver = true;
						}
					}
				}
				scoreCount++;
				if (scoreCount == 2)
				{
					score++;
					scoreCount = 0;
				}
			}
		}
		void Render()
		{
			cRenderer.Clear();

			if (!gameOver)
			{
				cRenderer.MoveCursor(p->x, p->y);
				cRenderer.DrawString("P");

				for (size_t i = 0; i < 6; i++)
				{
					if (t[i]->isOn)
					{
						cRenderer.MoveCursor(t[i]->x, t[i]->y);
						cRenderer.DrawString("X");
						if (t[i]->length == 2)
						{
							cRenderer.MoveCursor(t[i]->x, t[i]->y - 1);
							cRenderer.DrawString("X");
						}
					}
				}
			}
			else
			{
				cRenderer.MoveCursor(16, 7);
				cRenderer.DrawString("Game Over!");
			}
			cRenderer.MoveCursor(0, 0);
			cRenderer.DrawString(to_string(score));

			cRenderer.MoveCursor(10, 20);

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			cRenderer.DrawString(fps);
			this_thread::sleep_for(chrono::milliseconds(1));
		}
	};
}