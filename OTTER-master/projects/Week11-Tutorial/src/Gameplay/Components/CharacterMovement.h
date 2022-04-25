#pragma once
#include "Gameplay/Components/IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

class CharacterMovement : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<CharacterMovement> Sptr;

	CharacterMovement();
	virtual ~CharacterMovement();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(CharacterMovement);
	virtual nlohmann::json ToJson() const override;
	static CharacterMovement::Sptr FromJson(const nlohmann::json& blob);

protected:
	float _speed = 0.25f;
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 180.0f);
	Gameplay::Physics::RigidBody::Sptr _body;
};