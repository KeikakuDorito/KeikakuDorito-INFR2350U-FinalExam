#include "CharacterMovement.h"

#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Gameplay/InputEngine.h"
#include "Utils/ImGuiHelper.h"
#include "Application/Application.h"

void CharacterMovement::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr)
	{
		IsEnabled = false;
	}
}

void CharacterMovement::RenderImGui()
{
	LABEL_LEFT(ImGui::DragFloat, "Speed", &_speed, 1.0f);
}

nlohmann::json CharacterMovement::ToJson() const
{
	return
	{
		{ "speed", _speed }
	};
}

CharacterMovement::CharacterMovement() : IComponent()
{}

CharacterMovement::~CharacterMovement() = default;

CharacterMovement::Sptr CharacterMovement::FromJson(const nlohmann::json & blob)
{
	CharacterMovement::Sptr result = std::make_shared<CharacterMovement>();
	result->_speed = blob["speed"];
	return result;
}

void CharacterMovement::Update(float deltaTime)
{
	if (InputEngine::IsKeyDown(GLFW_KEY_A))
	{
		_body->SetLinearVelocity(glm::vec3(_speed * -1.0f, 0.0f, 0.0f));
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	if (InputEngine::IsKeyDown(GLFW_KEY_D))
	{
		_body->SetLinearVelocity(glm::vec3(_speed, 0.0f, 0.0f));
		rotation = glm::vec3(0.0f, 0.0f, 180.0f);
	}
	GetGameObject()->SetRotation(rotation);
}

