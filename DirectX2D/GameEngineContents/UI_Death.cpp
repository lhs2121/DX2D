#include "PreCompile.h"
#include "UI_Death.h"
#include "StatData.h"
#include "StatManager.h"

UI_Death::UI_Death()
{
}

UI_Death::~UI_Death()
{
}

void UI_Death::Start()
{
	float4 WinSize = ContentsCore::GetStartWindowSize();
	{
		Notice = CreateComponent<GameEngineUIRenderer>(0);
		Notice->SetSprite("UI_Death");
		Notice->AutoSpriteSizeOn();
	}

	float4 scale = Notice->GetImageTransform().GetLocalScale();

	{
		OKButton = CreateComponent<GameEngineUIRenderer>(0);
		OKButton->SetSprite("Button",1);
		OKButton->Transform.SetLocalPosition({ scale.hX() - 35,-scale.hY() + 23 });
	}
	{
		Col = CreateComponent<GameEngineCollision>(CollisionOrder::UI_Button);
		Col->Transform.SetLocalPosition(OKButton->Transform.GetLocalPosition());
		Col->Transform.SetLocalScale(OKButton->GetImageTransform().GetLocalScale());
		GameEngineInput::AddInputObject(this);
	}
}

void UI_Death::Update(float _Delta)
{
	bool IsCol = 
		Col->Collision(CollisionOrder::Cursor, [&](std::vector<std::shared_ptr<GameEngineCollision>>_Col)
		{
			OKButton->SetSprite("Button", 0);
			if (InputIsPress(VK_LBUTTON))
			{
				OKButton->SetSprite("Button", 2);
			}
			if (InputIsUp(VK_LBUTTON))
			{
				GameEngineCore::ChangeLevel("TownLevel");
				StatManager::Inst->ResetHp();
				Death();
			}
		});

	if (IsCol == false)
	{
		OKButton->SetSprite("Button", 1);
	}
}
