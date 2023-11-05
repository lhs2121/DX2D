#include "PreCompile.h"
#include "Skill_ShowDown.h"
#include "Player.h"
#include "Monster.h"
#include "StatData.h"

Skill_ShowDown::Skill_ShowDown()
{
}

Skill_ShowDown::~Skill_ShowDown()
{
}

void Skill_ShowDown::Start()
{
	SkillCol = CreateComponent<GameEngineCollision>();
	SkillCol->SetCollisionType(ColType::AABBBOX2D);
	SkillCol->Transform.SetLocalScale({ 450,300 });
	SkillCol->Off();
}

void Skill_ShowDown::Update(float _Delta)
{
	SkillCol->Collision(CollisionOrder::MonsterAttack, [&](std::vector<std::shared_ptr<GameEngineCollision>> _Collision)
		{
			for (size_t i = 0; i < _Collision.size(); i++)
			{
				if (i > 5)
				{
					break; // 5명까지 때린다
				}
				std::vector<float> Damage =  Player::MainPlayer->GetStat()->GetDamage(6,SkillType::ShowDown);
				int id = GameEngineRandom::GameEngineRandom().RandomInt(0, 999999);

				std::shared_ptr<Monster> Target = _Collision[i]->GetActor()->GetDynamic_Cast_This<Monster>();
				Target->ApplyDamage(Damage);
				Target->RenderDamage(Damage, id, i*10);
			}
			SkillCol->Off();
		});
}

void Skill_ShowDown::StartSkill()
{
	float4 Pos = Player::MainPlayer->Transform.GetWorldPosition();
	float Dir = Player::MainPlayer->GetDir();

	CurRenderer = GetNonUpdateRenderer();
	CurRenderer->CurAnimation()->Reset();
	CurRenderer->Transform.SetWorldPosition(Pos + float4(Dir * 200, 50));
	SkillCol->Transform.SetWorldPosition(Pos + float4(Dir * 250, 50));
	FlipX(Dir, CurRenderer);
	CurRenderer->On();
}

std::shared_ptr<class GameEngineSpriteRenderer> Skill_ShowDown::GetNonUpdateRenderer()
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
	NewRenderer->AutoSpriteSizeOn();
	NewRenderer->CreateAnimation("ShowDownChallenge", "ShowDownChallenge", 0.07f, 0, 24, false);
	NewRenderer->ChangeAnimation("ShowDownChallenge");
	NewRenderer->SetRenderOrder(RenderOrder::Effect);
	NewRenderer->SetFrameEvent("ShowDownChallenge", 8, 
		[&](GameEngineSpriteRenderer*)
		{
			SkillCol->On();
		});
	NewRenderer->SetFrameEvent("ShowDownChallenge", 11,
		[&](GameEngineSpriteRenderer*)
		{
			SkillCol->Off();
		});
	NewRenderer->SetEndEvent("ShowDownChallenge",
		[](GameEngineSpriteRenderer* _Renderer)
		{
			_Renderer->Off();
		});
	RendererGroup.push_back(NewRenderer);
	return NewRenderer;
}
