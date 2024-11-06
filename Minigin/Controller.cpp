#include "Controller.h"
#include <Windows.h>
#include <Xinput.h>
#pragma comment (lib, "xinput.lib")



namespace dae
{

	class Controller::ControllerImpl
	{
		XINPUT_STATE _previousState{};
		XINPUT_STATE _currentState{};

		WORD _buttonsPressedThisFrame{};
		WORD _buttonsReleasedThisFrame{};

		int m_ControllerIndex;
	public:

		ControllerImpl(int controllerIndex)
			:m_ControllerIndex{ controllerIndex }
		{
			ZeroMemory(&_previousState, sizeof(XINPUT_STATE));
			ZeroMemory(&_currentState, sizeof(XINPUT_STATE));
		}

		void Update()
		{
			CopyMemory(&_previousState, &_currentState, sizeof(XINPUT_STATE));
			ZeroMemory(&_currentState, sizeof(XINPUT_STATE));
			XInputGetState(m_ControllerIndex, &_currentState);

			auto buttonChanges = _currentState.Gamepad.wButtons ^ _previousState.Gamepad.wButtons;

			_buttonsPressedThisFrame = buttonChanges & _currentState.Gamepad.wButtons;
			_buttonsReleasedThisFrame = buttonChanges & (~_currentState.Gamepad.wButtons);
		}

		bool IsDownThisFrame(unsigned int button) const
		{
			return _buttonsPressedThisFrame & static_cast<unsigned int>(button);
		}

		bool IsUpThisFrame(unsigned int button) const
		{
			return _buttonsReleasedThisFrame & static_cast<unsigned int>(button);
		}

		bool IsPressed(unsigned int button) const
		{
			return _currentState.Gamepad.wButtons & static_cast<unsigned int>(button);

		}

		bool HasStateChange()
		{
			return _currentState.dwPacketNumber != _previousState.dwPacketNumber;
		}
	};



	Controller::Controller(int controllerIdx)
	{	
		m_controllerImpl = new ControllerImpl(controllerIdx);
	}

	Controller::~Controller()
	{
		delete m_controllerImpl;
	}

	void Controller::Update()
	{
		m_controllerImpl->Update();
	}

	bool Controller::IsPressed(unsigned int button) const
	{
		return m_controllerImpl->IsPressed(button);
	}

	bool Controller::IsDown(unsigned int button) const
	{
		return m_controllerImpl->IsDownThisFrame(button);
	}

	bool Controller::IsUp(unsigned int button) const
	{
		return m_controllerImpl->IsUpThisFrame(button);
	}


	bool Controller::HasStateChange() const
	{
		return m_controllerImpl->HasStateChange();
	}

	glm::vec2 Controller::GetDPadDirection() const
	{
		glm::vec2 axis{ 0, 0 };
		if (IsDown(static_cast<unsigned int>(ControllerButton::DPad_Left))) axis.x = -1.f;
		else if (IsDown(static_cast<unsigned int>(ControllerButton::DPad_Right))) axis.x = 1.0f;

		if (IsDown(static_cast<unsigned int>(ControllerButton::DPad_Down))) axis.y = 1.f;
		else if (IsDown(static_cast<unsigned int>(ControllerButton::DPad_Up))) axis.y = -1.0f;

		return axis;
	}


}