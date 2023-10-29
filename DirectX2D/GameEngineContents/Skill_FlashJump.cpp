#include "PreCompile.h"
#include "Skill_FlashJump.h"
#include "Player.h"

Skill_FlashJump::Skill_FlashJump()
{
}

Skill_FlashJump::~Skill_FlashJump()
{
}

void Skill_FlashJump::Start()
{

}

void Skill_FlashJump::Update(float _Delta)
{

}

void Skill_FlashJump::Release()
{
	CurRenderer = nullptr;

	std::list<std::shared_ptr<GameEngineSpriteRenderer>>::iterator Start = RendererGroup.begin();
	std::list<std::shared_ptr<GameEngineSpriteRenderer>>::iterator End = RendererGroup.end();

	for (; Start != End; Start++)
	{
		(*Start)->Death();
		(*Start) = nullptr;
	}
}

void Skill_FlashJump::StartSkill()
{
	float4 Pos = Player::MainPlayer->Transform.GetWorldPosition();
	float Dir = Player::MainPlayer->GetDir();

	CurRenderer = GetNonUpdateRenderer();
	CurRenderer->CurAnimation()->Reset();
	CurRenderer->Transform.SetWorldPosition(Pos);
	FlipX(Dir, CurRenderer);
	CurRenderer->On();
}

std::shared_ptr<class GameEngineSpriteRenderer> Skill_FlashJump::GetNonUpdateRenderer()
{
	std::list<std::shared_ptr<GameEngineSpriteRenderer>>::iterator Start = RendererGroup.begin();
	std::list<std::shared_ptr<GameEngineSpriteRenderer>>::iterator End = RendererGroup.end();

	for (; Start != End; Start++)
	{
		if ((*Start)->IsUpdate() == false)
		{
			return (*Start);
		}
	}

	std::shared_ptr<GameEngineSpriteRenderer> NewRenderer = CreateComponent<GameEngineSpriteRenderer>();
	NewRenderer->CreateAnimation("FlashJump", "FlashJump", 0.1f, 0, 7, false);
	NewRenderer->ChangeAnimation("FlashJump");
	NewRenderer->SetRenderOrder(RenderOrder::Effect);
	NewRenderer->AutoSpriteSizeOn();
	NewRenderer->SetEndEvent("FlashJump", 
		[](GameEngineSpriteRenderer* _Renderer) 
		{
			_Renderer->Off();
		});
	RendererGroup.push_back(NewRenderer);
	return NewRenderer;
}
