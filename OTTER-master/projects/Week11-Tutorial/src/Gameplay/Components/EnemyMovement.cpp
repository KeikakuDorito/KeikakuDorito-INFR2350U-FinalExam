#include "Gameplay/Components/EnemyMovement.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include <cmath>

EnemyMovement::EnemyMovement(GameObject::Sptr self, float speed, GameObject::Sptr target){
	_self = self;
	moveSpeed = speed;
	_target = target;
}


void EnemyMovement::Awake(){
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if(_body == nullptr){
		IsEnabled = false;
	}
}

void Enemymovement::Update(float deltaTime){
	//if enemy is too close, flee behaviour
	if(GetDistance(_self->GetPosition(), _target->GetPosition()) < 5.f){
		movementVector.X = (_target->GetPositionX() - _self->GetPosition().X);
		movementVector.Y = _self->GetPosition().Y;
		movementVector.Z = _self->GetPosition().Z;
	}
	//else go towards player
	else{
		movementVector.X = (_self->GetPosition() - _target->GetPositionX());
		movementVector.Y = _self->GetPosition().Y;
		movementVector.Z = _self->GetPosition().Z;
	}
	
}

float EnemyMovement::GetDistance(glm::vec3 A, glm::vec3 B){
	float x = A.X - B.X;
	x = pow(x, 2);
	float y = A.Y - B.Y;
	y = pow(y, 2);

	return sqrt(x+y);
}

EnemyMovement::~EnemyMovement() = default;

void EnemyMovement::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Speed", &moveSpeed, 1.0f);
}

nlohmann::json EnemyMovement::ToJson() const {
	return {
		{ "speed", moveSpeed }
	};
}

EnemyMovement::Sptr EnemyMovement::FromJson(const nlohmann::json& blob) {
	EnemyMovement::Sptr result = std::make_shared<EnemyMovement>();
	result->moveSpeed = blob["speed"];
	return result;
}