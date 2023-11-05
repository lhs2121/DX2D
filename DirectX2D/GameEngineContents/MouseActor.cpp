#include "PreCompile.h"
#include "MouseActor.h"

MouseActor::MouseActor()
{
}

MouseActor::~MouseActor()
{
}

void MouseActor::Start()
{
	Renderer = CreateComponent<GameEngineUIRenderer>();
	Renderer->CreateAnimation("Cursor_Default", "Cursor_Default");
	Renderer->ChangeAnimation("Cursor_Default");
	Renderer->SetRenderOrder(UIRenderOrder::Cursor);
	Renderer->AutoSpriteSizeOn();
	Col = CreateComponent<GameEngineCollision>(CollisionOrder::Cursor);
	Col->Transform.SetLocalScale({ 20,20 }); 

	
}
void MouseActor::Update(float _Delta)
{
	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();
	float4 CameraPos = GetLevel()->GetCamera(static_cast<int>(ECAMERAORDER::UI))->Transform.GetWorldPosition();
	float4 Pos = CameraPos + float4(-WinSize.X, WinSize.Y);

	Transform.SetWorldPosition(Pos);
	Transform.AddWorldPosition({ MousePos.X, -MousePos.Y });
}
void MouseActor::Release()
{
}
