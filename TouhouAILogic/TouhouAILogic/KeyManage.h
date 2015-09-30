#pragma once

using namespace System;

namespace TouhouAILogic {

	public class KeyManage
	{

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

	private:
		KeyManage() {}
		KeyManage(const KeyManage &other) {}
		KeyManage &operator=(const KeyManage &other) {}
	};
}