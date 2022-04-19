#pragma once
#include <chrono>
#include <thread>
#include "MConsolUtil.hpp"
#include "Player.hpp"

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private:
		bool _isGameRunning;
		MConsoleRenderer cRenderer;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;
		Player* p = new Player();
	public:
		MGameLoop()
		{
			_isGameRunning = false;
			startRenderTimePoint = chrono::system_clock::now();
			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
		}
		~MGameLoop()
		{
			delete(p);
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
				p->isKeyPressed();
		}
		void Update()
		{
			p->filghtCounter();
		}
		void Render()
		{
			cRenderer.Clear();

			cRenderer.MoveCursor(p->x, p->y);
			cRenderer.DrawString("P");

			cRenderer.MoveCursor(10, 20);

			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			cRenderer.DrawString(fps);

			this_thread::sleep_for(chrono::milliseconds(1));
		}
	};
}