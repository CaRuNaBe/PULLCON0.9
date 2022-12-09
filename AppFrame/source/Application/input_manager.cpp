#include "input_manager.h"
namespace
{
	const XINPUT_STATE operator^( const XINPUT_STATE& left , const XINPUT_STATE& right )
	{
		XINPUT_STATE input;
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons [ i ] = left.Buttons [ i ] ^ right.Buttons [ i ];
		}
		input.LeftTrigger = left.LeftTrigger ^ right.LeftTrigger;
		input.RightTrigger = left.RightTrigger ^ right.RightTrigger;
		input.ThumbLX = left.ThumbLX ^ right.ThumbLX;
		input.ThumbLY = left.ThumbLY ^ right.ThumbLY;
		input.ThumbRX = left.ThumbRX ^ right.ThumbRX;
		input.ThumbRY = left.ThumbRY ^ right.ThumbRY;
		return input;
	};

	const XINPUT_STATE operator&( const XINPUT_STATE& left , const XINPUT_STATE& right )
	{
		XINPUT_STATE input;
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons [ i ] = left.Buttons [ i ] & right.Buttons [ i ];
		}
		input.LeftTrigger = left.LeftTrigger & right.LeftTrigger;
		input.ThumbLX = left.ThumbLX & right.ThumbLX;
		input.ThumbLY = left.ThumbLY & right.ThumbLY;
		input.ThumbRX = left.ThumbRX & right.ThumbRX;
		input.ThumbRY = left.ThumbRY & right.ThumbRY;
		return input;
	};

	const XINPUT_STATE operator~( const XINPUT_STATE& right )
	{
		XINPUT_STATE input;
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons [ i ] = ~right.Buttons [ i ];
		}
		input.LeftTrigger = ~right.LeftTrigger;
		input.RightTrigger = ~right.RightTrigger;
		input.ThumbLX = ~right.ThumbLX;
		input.ThumbLY = ~right.ThumbLY;
		input.ThumbRX = ~right.ThumbRX;
		input.ThumbRY = ~right.ThumbRY;
		return input;
	};
}

InputManager::InputManager()
{
	_gKey = 0;
	_gTrg = 0;
	_gRel = 0;
	Speak_skip_count = 0;
	is_Click_on = false;
	GetJoypadXInputState(DX_INPUT_PAD1,&_gxTrg);
	GetJoypadXInputState(DX_INPUT_PAD1,&_gxRel);
	GetJoypadXInputState(DX_INPUT_PAD1,&_gxKey);
}

InputManager::~InputManager()
{};

bool InputManager::Update()
{
	auto xkeyold = _gxKey;
	GetJoypadXInputState(DX_INPUT_PAD1,&_gxKey);
	_gxTrg = ( _gxKey ^ xkeyold ) & _gxKey;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	_gxRel = ( _gxKey ^ xkeyold ) & ~_gxKey;	// キーのリリース情報生成（離した瞬間しか反応しないキー情報）
	// キーの入力、トリガ入力を得る
	int keyold = _gKey;
	_gKey = GetJoypadInputState( DX_INPUT_PAD1 );
	_gTrg = ( _gKey ^ keyold ) & _gKey;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	_gRel = ( _gKey ^ keyold ) & ~_gKey;	// キーのリリース情報生成（離した瞬間しか反応しないキー情報）
	return true;
};

const bool  InputManager::EveryOtherKey( const int button , const int FrequencyFrame )
{
	if ( _gKey & button )
	{
		Speak_skip_count++;
		if ( 0 == Speak_skip_count % FrequencyFrame )
		{
			is_Click_on = true;
		}
		else
		{
			is_Click_on = false;
		}
	}
	else
	{
		is_Click_on = false;
		Speak_skip_count = 0;
	}
	return is_Click_on;
};
const int InputManager::GetKey( int button )
{
	return _gKey & button;
};
const int InputManager::GetTrg( int button )
{
	return _gTrg & button;
};
const int InputManager::GetRel( int button )
{
	return _gRel & button;
};

const bool  InputManager::XinputEveryOtherKey( const int button , const int FrequencyFrame )
{
	if ( _gxKey.Buttons [ button ] >= 1 || _gxKey.LeftTrigger >= 10 || _gxKey.RightTrigger >= 10 )
	{
		Speak_skip_count++;
		if ( 0 == Speak_skip_count % FrequencyFrame )
		{
			is_Click_on = true;
		}
		else
		{
			is_Click_on = false;
		}
	}
	else
	{
		is_Click_on = false;
		Speak_skip_count = 0;
	}
	return is_Click_on;
};

const bool InputManager::GetKeyXinput( const int button )
{
	return _gxKey.Buttons [ button ] == 1;
};
const bool InputManager::GetTrgXinput( const int button )
{
	return _gxTrg.Buttons [ button ] == 1;
};
const bool InputManager::GetRelXinput( const int button )
{
	return _gxRel.Buttons [ button ] == 1;
};
const unsigned char InputManager::GetLeftTrigger()
{
	return _gxKey.LeftTrigger;
};
const unsigned char InputManager::GetRightTrigger()
{
	return _gxKey.RightTrigger;
};
const short InputManager::GetLstickX()
{
	return _gxKey.ThumbLX;
};
const short InputManager::GetLstickY()
{
	return _gxKey.ThumbLY;
};
const short InputManager::GetRstickX()
{
	return _gxKey.ThumbRX;
};
const short InputManager::GetRstickY()
{
	return _gxKey.ThumbRY;
};
