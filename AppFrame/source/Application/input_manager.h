#pragma once
#include<DxLib.h>
#include<memory>
class InputManager
{
public:
	InputManager();
	~InputManager();
	bool Update();

	//ì¸óÕä÷êî
	const bool EveryOtherKey( int button , const int FrequencyFrame );
	const int GetKey( int button );
	const int GetTrg( int button );
	const int GetRel( int button );
	const bool& XinputEveryOtherKey( int button , const int FrequencyFrame );
	const unsigned char GetLeftTrigger();
	const unsigned char GetRightTrigger();
	short GetLstickX();
	short GetLstickY();
	const short GetRstickX();
	const short GetRstickY();
	const bool GetKeyXinput( const int button );
	const bool GetTrgXinput( const int button );
	const bool GetRelXinput( const int button );
private:
	XINPUT_STATE 	_gxKey;
	XINPUT_STATE _gxTrg;
	XINPUT_STATE _gxRel;
	int		_gKey , _gTrg , _gRel;
	int Speak_skip_count;
	bool is_Click_on;
};
