#pragma once
#include <chrono>
#include <string>
#include <iostream>
#include "Player.hpp"
#include "Trab.hpp"
#include "MWindowUtil.hpp"
#include <random>
 
using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private:
		bool _isGameRunning, gameOver;
		//MConsoleRenderer cRenderer;
		MWindowUtil* cWindow;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		Player* p = new Player();
		Trab* t[6];
		int trabSize = sizeof(t) / sizeof(t[0]);
		//int score, scoreCount;
		int key;
		double deltaTime;
	public:
		MGameLoop()
		{
			_isGameRunning = false;
			startRenderTimePoint = chrono::system_clock::now();
			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			gameOver = false;
			//score = 0;
			//scoreCount = 0;
			for (size_t i = 0; i < trabSize; i++)
			{
				t[i] = new Trab();
			}
			char TitleName[] = "Chrome dino";
			cWindow = new MWindowUtil(640, 480, TitleName, 0.025, 1.0 / 3 * 0.1, 40, 20);
			key = -1;
			deltaTime = 0;
		}
		~MGameLoop() {}
		
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
		void Release()
		{
			delete(p);
			for (size_t i = 0; i < trabSize; i++)
				delete(t[i]);
			delete(cWindow);
		}
		void Input()
		{
			key = cWindow->FindKey();
			if (gameOver)
			{
				if (key == GLFW_KEY_R)
				{
					for (size_t i = 0; i < trabSize; i++)
						t[i]->Hide();
					p->Reset();
					//score = 0;
					//scoreCount = 0;
					gameOver = false;
				}
			}
			else
			{
				if (key == GLFW_KEY_SPACE)
					p->isSpacePressed();
				if (key == GLFW_KEY_DOWN)
					p->isDownPressed();
			}
		}
		void Update()
		{
			cWindow->WindowEvent();
			if (cWindow->isEnd())
				_isGameRunning = false;

			if (!gameOver)
			{
				random_device rd;
				mt19937 gen(rd());
				p->Flight(deltaTime);
				for (size_t i = 0; i < trabSize; i++)
				{
					if (t[i]->isOn)
					{
						t[i]->Move(deltaTime);
						if (t[i]->x < -0.5f)
							t[i]->Hide();
					}
				}
				uniform_int_distribution<int> dis(1, 20);
				if (dis(gen) == 1)
				{
					int arrNum = -1;
					for (size_t i = 0; i < trabSize; i++)
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
						for (size_t i = 0; i < trabSize; i++)
						{
							if (t[i]->x < 35)
								count++;
						}
						if (count == 6)
							t[arrNum]->Initialize();
					}
				}
				for (size_t i = 0; i < trabSize; i++)
				{
					if (t[i]->isOn && t[i]->Collider(p))
						gameOver = true;
				}
				//scoreCount++;
				//if (scoreCount == 2)
				//{
				//	score++;
				//	scoreCount = 0;
				//}
			}
		}
		void Render()
		{
			cWindow->Clear();

			if (!gameOver)
			{
				cWindow->PrintRectangle(p->x, p->y, 0, 255, 0);

				for (size_t i = 0; i < trabSize; i++)
				{
					if (t[i]->isOn)
						cWindow->PrintTriangle(t[i]->x, t[i]->y, 255, 0, 0, t[i]->length);
				}
				for (size_t i = 0; i < 41; i++)
					cWindow->PrintRectangle(i, 8, 0, 0, 0);
			}
			//else
			//{
				//cRenderer.MoveCursor(16, 7);
				//cRenderer.DrawString("Game Over!");
			//}
			//cRenderer.MoveCursor(0, 0);
			//cRenderer.DrawString(to_string(score));


			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			deltaTime = renderDuration.count();
		}
	};
}