#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

class EnemyMovement : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<EnemyMovement> Sptr;

	std::weak_ptr<Gameplay::IComponent> Panel;

	EnemyMovement(Gameplay::GameObject::Sptr self, float speed, Gameplay::GameObject::Sptr target);
	virtual ~EnemyMovement();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(EnemyMovement);
	virtual nlohmann::json ToJson() const override;
	static EnemyMovement::Sptr FromJson(const nlohmann::json& blob);

protected:
	float moveSpeed;
	glm::vec3 movementVector;

	Gameplay::Physics::RigidBody::Sptr _body;
	Gameplay::GameObject::Sptr _self;
	Gameplay::GameObject::Sptr _target;

private:
	float GetDistance(glm::vec3 A, glm::vec3 B);
};