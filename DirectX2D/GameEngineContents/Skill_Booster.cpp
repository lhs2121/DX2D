#include "PreCompile.h"
#include "Skill_Booster.h"
#include "StatManager.h"
#include "Player.h"
#include "UI_Buff.h"

Skill_Booster::Skill_Booster()
{
}

Skill_Booster::~Skill_Booster()
{
}

void Skill_Booster::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>();
	Renderer->CreateAnimation("SurekenBooster", "SurekenBooster",0.1f,0,10,false);
	Renderer->ChangeAnimation("SurekenBooster");
	Renderer->AutoSpriteSizeOn();
	Renderer->SetPivotType(PivotType::Bottom);
	Renderer->SetRenderOrder(RenderOrder::Effect2);
	Renderer->SetEndEvent("SurekenBooster",
		[&](GameEngineSpriteRenderer*)
		{
			Renderer->Off();
		});
	Renderer->Off();
}

void Skill_Booster::Release()
{

}

void Skill_Booster::StartSkill()
{
	Renderer->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition());
	Renderer->On();
	Renderer->CurAnimation()->Reset();
	UI_Buff::Inst->RenderBuffUI(SkillType::SurekenBooster);
}

