#include "Button_Com.h"

JEONG_BEGIN

class Bar_Com : public Button_Com
{
public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void CollisionLateUpdate(float DeltaTime) override;
	void Render(float DeltaTime) override;
	Bar_Com* Clone() override;
	void AfterClone() override;

	void SetDir(BAR_DIR dir);
	void SetMinValue(float minValue) { m_MinValue = minValue; }
	void SetMaxValue(float maxValue) { m_MaxValue = maxValue; }
	void SetValue(float Value) { m_Value = Value; }
	void AddValue(float Value);
	void SetMinMaxValue(float minValue, float maxValue);

private:
	BAR_DIR m_Dir;
	float m_MinValue;
	float m_MaxValue;
	float m_Value;

protected:
	Bar_Com();
	Bar_Com(const Bar_Com& CopyData);
	~Bar_Com();

public:
	friend class GameObject;
};

JEONG_END