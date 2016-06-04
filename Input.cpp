#include "Input.h"

bool Input::Initialise(HWND hwnd, HINSTANCE hInst)
{
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL)))
	{
		if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&_directInput, NULL)))
		{
			return false;
		}
	}

	if(FAILED(_directInput->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL)))
	{
		if(FAILED(_directInput->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL)))
		{
			return false;
		}
	}

	if(FAILED(_keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		if(FAILED(_keyboard->SetDataFormat(&c_dfDIKeyboard)))
		{
			return false;
		}
	}
	if(FAILED(_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		if(FAILED(_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		{
			return false;
		}
	}

	if(FAILED(_directInput->CreateDevice(GUID_SysMouse, &_mouse, NULL)))
	{
		if(FAILED(_directInput->CreateDevice(GUID_SysMouse, &_mouse, NULL)))
		{
			return false;
		}
	}

	if(FAILED(_mouse->SetDataFormat(&c_dfDIMouse)))
	{
		if(FAILED(_mouse->SetDataFormat(&c_dfDIMouse)))
		{
			return false;
		}
	}

	if(FAILED(_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
	{
		if(FAILED(_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		{
			return false;
		}
	}

	return true;
}

void Input::GetInputData()
{
	_keyboard->Acquire();
	_hr = _keyboard->GetDeviceState(sizeof(_keyBuffer), (LPVOID)&_keyBuffer); 

	if(_hr != DI_OK)
	{
		_keyboard->Acquire();
		while(_hr == DIERR_INPUTLOST)
		{
			_hr = _keyboard->Acquire();
		}
	}

	_mouse->Acquire();
	_hr = _mouse->GetDeviceState(sizeof(_mouseState), (LPVOID)&_mouseState); 
	if(_hr == DIERR_INPUTLOST)
	{
		_mouse->Acquire();
	}
}

void Input::GetKeyboardState()
{
	_keyboard->Acquire();
	_hr = _keyboard->GetDeviceState(sizeof(_keyBuffer), (LPVOID)&_keyBuffer); 

	if(_hr != DI_OK)
	{
		_keyboard->Acquire();
		while(_hr == DIERR_INPUTLOST)
		{
			_hr = _keyboard->Acquire();
		}
	}
}

int Input::IsWPressed()
{
	return KEYDOWN(_keyBuffer, DIK_W);
}

int Input::IsSPressed()
{
	return KEYDOWN(_keyBuffer, DIK_S);
}

int Input::IsAPressed()
{
	return KEYDOWN(_keyBuffer, DIK_A);
}

int Input::IsDPressed()
{
	return KEYDOWN(_keyBuffer, DIK_D);
}

int Input::IsEscapePressed()
{
	return KEYDOWN(_keyBuffer, DIK_ESCAPE);
}

void Input::CleanUp()
{
	if(_directInput != NULL)
	{
		_directInput->Release();
		_directInput = NULL;
	}

	if(_keyboard != NULL)
	{
		_keyboard->Release();
		_keyboard = NULL;
	}

	if(_mouse != NULL)
	{
		_mouse->Release();
		_mouse = NULL;
	}
}
