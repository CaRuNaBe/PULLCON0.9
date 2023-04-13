#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "mode/ModeTitle.h"
#include "mode/ModeSpeakScript.h"
// ŽÀ‘Ì
ApplicationMain g_oApplicationMain;

bool ApplicationMain::Initialize( HINSTANCE hInstance )
{
  if ( !base::Initialize( hInstance ) )
  {
    return false;
  }
  font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );
  gGlobal.Init();

  auto title = std::make_shared<ModeTitle>( *this,1 );
  base::GetInstance()->GetModeServer()->Add( title );

  return true;
}

bool ApplicationMain::Terminate()
{
  base::Terminate();
  return true;
}


bool ApplicationMain::Input()
{
  base::Input();
  return true;
}

bool ApplicationMain::Update()
{
  base::Update();
  if ( is_game_end )
  {
    return false;
  }
  return true;
}

bool ApplicationMain::Draw()
{
  base::Draw();
  return true;
}

