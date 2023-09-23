#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class KerningCity : public GameEngineLevel
{
public:
	// constrcuter destructer
	KerningCity();
	~KerningCity();

	// delete Function
	KerningCity(const KerningCity& _Other) = delete;
	KerningCity(KerningCity&& _Other) noexcept = delete;
	KerningCity& operator=(const KerningCity& _Other) = delete;
	KerningCity& operator=(KerningCity&& _Other) noexcept = delete;

	std::shared_ptr<class Map0> GetCurMap()
	{
		return CurMap;
	}
protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class Map0> CurMap;
};

