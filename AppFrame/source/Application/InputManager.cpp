#include "InputManager.h"
namespace
{
	const XINPUT_STATE InitializeXinput()
	{
		XINPUT_STATE input;
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons[i] = 0;
		}
		input.LeftTrigger = 0;
		input.RightTrigger = 0;
		input.ThumbLX = 0;
		input.ThumbLY = 0;
		input.ThumbRX = 0;
		input.ThumbRY = 0;

		return input;
	};

	const XINPUT_STATE operator^( const XINPUT_STATE& left,const XINPUT_STATE& right )
	{
		XINPUT_STATE input = InitializeXinput();
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons[i] = left.Buttons[i] ^ right.Buttons[i];
		}
		input.LeftTrigger = left.LeftTrigger ^ right.LeftTrigger;
		input.RightTrigger = left.RightTrigger ^ right.RightTrigger;
		input.ThumbLX = left.ThumbLX ^ right.ThumbLX;
		input.ThumbLY = left.ThumbLY ^ right.ThumbLY;
		input.ThumbRX = left.ThumbRX ^ right.ThumbRX;
		input.ThumbRY = left.ThumbRY ^ right.ThumbRY;
		return input;
	};

	const XINPUT_STATE operator&( const XINPUT_STATE& left,const XINPUT_STATE& right )
	{
		XINPUT_STATE input = InitializeXinput();
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons[i] = left.Buttons[i] & right.Buttons[i];
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
		XINPUT_STATE input = InitializeXinput();
		for ( int i = 0; i < 16; i++ )
		{
			input.Buttons[i] = ~right.Buttons[i];
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
	Key_skip_count = 0;
	LeftTrigger_skip_count = 0;
	RightTrigger_skip_count = 0;
	is_Click_on_Key = false;
	is_Click_on_R_Trigger = false;
	is_Click_on_L_Trigger = false;
	_gxKey = InitializeXinput();
	_gxTrg = InitializeXinput();
	_gxRel = InitializeXinput();
}

InputManager::~InputManager()
{};

bool InputManager::Update()
{
	SetJoypadDeadZone( DX_INPUT_PAD1,0.50 );
	auto xkeyold = _gxKey;
	GetJoypadXInputState( DX_INPUT_PAD1,&_gxKey );
	_gxTrg = (_gxKey ^ xkeyold) & _gxKey;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	_gxRel = (_gxKey ^ xkeyold) & ~_gxKey;	// キーのリリース情報生成（離した瞬間しか反応しないキー情報）

	int keyold = _gKey;
	_gKey = GetJoypadInputState( DX_INPUT_KEY_PAD1 );
	_gTrg = (_gKey ^ keyold) & _gKey;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	_gRel = (_gKey ^ keyold) & ~_gKey;	// キーのリリース情報生成（離した瞬間しか反応しないキー情報）
	return true;
};

const bool& InputManager::EveryOtherKey( const int button,const int FrequencyFrame )
{
	if ( _gKey & button )
	{
		Key_skip_count++;
		if ( 0 == Key_skip_count % FrequencyFrame )
		{
			is_Click_on_Key = true;
		}
		else
		{
			is_Click_on_Key = false;
		}
	}
	else
	{
		is_Click_on_Key = false;
		Key_skip_count = 0;
	}
	return is_Click_on_Key;
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

//xinputコントローラー情報
//連続入力
const bool InputManager::GetKeyXinput( const int button )
{
	return _gxKey.Buttons[button] == 1;
};
//押したときだけ反応
const bool InputManager::GetTrgXinput( const int button )
{
	return _gxTrg.Buttons[button] == 1;
};
//離したとき反応
const bool InputManager::GetRelXinput( const int button )
{
	return _gxRel.Buttons[button] == 1;
};
//左トリガーの入力状態を取得
const unsigned char& InputManager::GetLeftTrigger()
{
	return _gxKey.LeftTrigger;
};
//右トリガーの入力状態を取得
const unsigned char& InputManager::GetRightTrigger()
{
	return _gxKey.RightTrigger;
};
//左スティックのx軸を取得
short& InputManager::GetLstickX()
{
	return _gxKey.ThumbLX;
};
//左スティックのy軸を取得
short& InputManager::GetLstickY()
{
	return _gxKey.ThumbLY;
};
//右スティックのx軸を取得
const short& InputManager::GetRstickX()
{
	return _gxKey.ThumbRX;
};
//右スティックのy軸を取得
const short& InputManager::GetRstickY()
{
	return _gxKey.ThumbRY;
};
//ボタンの隔フレーム入力を取得
const bool& InputManager::XinputEveryOtherKey( const int button,const int FrequencyFrame )
{
	is_Click_on_Key = true;
	if ( _gxKey.Buttons[button] >= 1 && (Key_skip_count == 0) )
	{
		Key_skip_count++;
		return is_Click_on_Key;
	}
	if ( _gxKey.Buttons[button] >= 1 )
	{
		Key_skip_count++;
		if ( 0 == Key_skip_count % FrequencyFrame )
		{
			is_Click_on_Key = true;
		}
		else
		{
			is_Click_on_Key = false;
		}
	}
	else
	{
		is_Click_on_Key = false;
		Key_skip_count = 0;
	}
	return is_Click_on_Key;
};
//右トリガーの隔フレーム入力を取得
const bool& InputManager::XinputEveryOtherRightTrigger( const int FrequencyFrame )
{
	is_Click_on_R_Trigger = true;
	if ( _gxKey.RightTrigger >= 10 && (RightTrigger_skip_count == 0) )
	{
		RightTrigger_skip_count++;
		return is_Click_on_R_Trigger;
	}
	if ( _gxKey.RightTrigger >= 10 )
	{
		RightTrigger_skip_count++;
		if ( 0 == RightTrigger_skip_count % FrequencyFrame )
		{
			is_Click_on_R_Trigger = true;
		}
		else
		{
			is_Click_on_R_Trigger = false;
		}
	}
	else
	{
		is_Click_on_R_Trigger = false;
		RightTrigger_skip_count = 0;
	}
	return is_Click_on_R_Trigger;
};
//左トリガーの隔フレーム入力を取得
const bool& InputManager::XinputEveryOtherLeftTrigger( const int FrequencyFrame )
{
	is_Click_on_L_Trigger = true;
	if ( _gxKey.LeftTrigger >= 10 && (LeftTrigger_skip_count == 0) )
	{
		LeftTrigger_skip_count++;
		return is_Click_on_L_Trigger;
	}
	if ( _gxKey.LeftTrigger >= 10 )
	{
		LeftTrigger_skip_count++;
		if ( 0 == LeftTrigger_skip_count % FrequencyFrame )
		{
			is_Click_on_L_Trigger = true;
		}
		else
		{
			is_Click_on_L_Trigger = false;
		}
	}
	else
	{
		is_Click_on_L_Trigger = false;
		LeftTrigger_skip_count = 0;
	}
	return is_Click_on_L_Trigger;
};
