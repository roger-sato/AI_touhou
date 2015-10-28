#pragma once

#include <Windows.h>

namespace TouhouAILogic {

	public class KeyManage
	{
		INPUT input;

		void KeyOn(short keycode);
		void KeyOff(short keycode);

	public:
		static KeyManage& Instance()
		{
			static KeyManage instance;
			return instance;
		}

		void SendUp();
		void SendDown();
		void SendRight();
		void SendLeft();
		void SendEnter();

		void OnUp();
		void OffUp();
		void OnRight();
		void OffRight();
		void OnLeft();
		void OffLeft();
		void OnDown();
		void OffDown();

		void OnZ();
		void OffZ();
		void OnX();
		void OffX();


	private:
		KeyManage() {}
		KeyManage(const KeyManage &other) {}
		KeyManage &operator=(const KeyManage &other) {}
	};
}