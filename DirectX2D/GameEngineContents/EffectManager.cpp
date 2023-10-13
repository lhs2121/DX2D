#include "PreCompile.h"
#include "EffectManager.h"

EffectManager* EffectManager::Inst = nullptr;

EffectManager::EffectManager()
{
	Inst = this;
}

EffectManager::~EffectManager()
{
}

void EffectManager::StartEffect(float4 _Pos, SkillType _Type)
{
	Transform.SetWorldPosition(_Pos);
	Renderer->ChangeAnimation("etc");
	switch (_Type)
	{
	case SkillType::FlashJump:
		Renderer->ChangeAnimation("FlashJump");
		break;
	case SkillType::LuckySeven:
		break;
	default:
		break;
	}

	On();
}

void EffectManager::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->CreateAnimation("etc", "etc");
	Renderer->CreateAnimation("FlashJump", "flashjump");
	Renderer->ChangeAnimation("FlashJump");
	Renderer->SetRenderOrder(RenderOrder::Effect);
	Renderer->AutoSpriteSizeOn();

	Off();
}

void EffectManager::Update(float _Delta)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Off();
	}
}
