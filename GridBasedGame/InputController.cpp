#include "InputController.h"

InputController::InputController(HWND windowHandle)
{
	m_windowHandle = windowHandle;						

	memset(m_PrevKeys, 0, sizeof(m_PrevKeys));
}

void InputController::SetKeyDown(UINT keyCode)
{
	m_CurrentKeys[keyCode] = true;
}

void InputController::SetKeyUp(UINT keyCode)
{
	m_CurrentKeys[keyCode] = false;
}

bool InputController::GetKeyDown(UINT keyCode)
{
	return !m_PrevKeys[keyCode] && m_CurrentKeys[keyCode];
}

bool InputController::GetKeyHold(UINT keyCode)
{
	return m_CurrentKeys[keyCode];
}

bool InputController::GetKeyUp(UINT keyCode)
{
	return m_PrevKeys[keyCode] && !m_CurrentKeys[keyCode];
}

void InputController::BeginUpdate()
{
	//We'll use this in future weeks when we capture mouse input
}

void InputController::EndUpdate()
{
	//When we finish an update we copy the values of the current arrays into the last arrays
	memcpy(m_PrevKeys, m_CurrentKeys, sizeof(m_CurrentKeys));
}