#pragma once
#include <chrono>
#include "MConsolUtil.hpp"

using namespace std;

namespace MuSeoun_Engine
{
	class MGameLoop
	{
	private :
		bool _isGameRunning;	
		MConsoleRenderer cRenderer;
		
	public :
		MGameLoop()
		{ _isGameRunning = false; }
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();

			while (_isGameRunning)
			{
				chrono::system_clock::time_point startRenderTimePoint = chrono::system_clock::now();
				Input();
				Update();
				Render();
				chrono::duration<double> renderDuration = chrono::system_clock::now() - startRenderTimePoint;
				string fps = "FPS : " + to_string(1 / renderDuration.count());
				cRenderer.DrawString(fps);
			}
			Release();
		}
		void Stop()
		{ _isGameRunning = false; }

	private :
		void Initialize() {}
		void Release() {}

		void Input() {}
		void Update() {}
		void Render()
		{
			cRenderer.Clear();
			cRenderer.MoveCursor(10, 20);
		}
	};

	


	

}