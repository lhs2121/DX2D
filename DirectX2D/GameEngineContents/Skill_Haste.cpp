#include "PreCompile.h"
#include "Skill_Haste.h"
#include "StatManager.h"
#include "Player.h"
#include "UI_Buff.h"

Skill_Haste::Skill_Haste()
{
}

Skill_Haste::~Skill_Haste()
{
}

void Skill_Haste::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->CreateAnimation("Haste", "Haste", 0.1f, 0, 8, false);
	Renderer->ChangeAnimation("Haste");
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->AutoSpriteSizeOn();
	Renderer->SetRenderOrder(RenderOrder::Effect2);
	Renderer->SetEndEvent("Haste",
		[&](GameEngineSpriteRenderer* _Renderer)
		{
			Renderer->Off();
		});
	Renderer->Off();
}

void Skill_Haste::Release()
{

}

void Skill_Haste::StartSkill()
{
	Renderer->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition());
	Renderer->CurAnimation()->Reset();
	Renderer->On();
	UI_Buff::Inst->RenderBuffUI(SkillType::Haste);
}
