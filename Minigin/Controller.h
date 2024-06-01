#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class Controller final
	{


	public:



		enum class ControllerButton
		{
			DPad_Up = 0x0001,
			DPad_Down = 0x0002,
			DPad_Left = 0x0004,
			DPad_Right = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			Left_Thumb = 0x0040,
			Right_Thumb = 0x0080,
			Left_Shoulder = 0x0100,
			Right_Shoulder = 0x0200,
			A = 0x1000,
			B = 0x2000,
			X = 0x4000,
			Y = 0x8000,
			Null = 0x000
		};

		Controller(int controlerIdx);
		~Controller();
		void Update();
		
		bool IsDown(unsigned int button) const;
		bool IsUp(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

		bool HasStateChange() const;
		glm::vec2 GetDPadDirection() const;


	private:

		class ControllerImpl;
		//std::unique_ptr<ControllerImpl> m_controllerImpl;
		ControllerImpl* m_controllerImpl;

	};
}


