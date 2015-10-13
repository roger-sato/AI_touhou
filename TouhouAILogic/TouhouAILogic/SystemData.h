#pragma once


namespace TouhouAILogic {

	public class SystemData{
		System::IntPtr WindowHandle;

	public:
		static SystemData& Instance()
		{
			static SystemData instance;
			return instance;
		}

		void SetWindowHandle(System::IntPtr hw);
		System::IntPtr GetWindowHandle();

	private:
		SystemData() {}
		SystemData(const SystemData &other) {}
		SystemData &operator=(const SystemData &other) {}
	};
}