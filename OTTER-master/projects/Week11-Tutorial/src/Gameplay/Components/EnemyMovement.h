#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

class EnemyMovement : public GamePlay::IComponent {
public:
    typedef std::shared_ptr<JumpBehaviour> Sptr;

	std::weak_ptr<Gameplay::IComponent> Panel;

    EnemyMovement();
    virtual ~EnemyMovement();

    virtual void Awake() override;
    virtual void Update(float deltaTime) override;
    void setTarget(glm::vec3 position);

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(JumpBehaviour);
	virtual nlohmann::json ToJson() const override;
	static JumpBehaviour::Sptr FromJson(const nlohmann::json& blob);

protected:
    float moveSpeed;
    glm::vec3 target;
    glm::vec3

    GamePlay::Physics::RigidBody::Sptr _body;
}