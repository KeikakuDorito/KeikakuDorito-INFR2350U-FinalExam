#include "Gameplay/Components/EnemyMovement.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include <cmath>

void EnemyMovement::Awake(){
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if(_body == nullptr){
		IsEnabled = false;
	}
}

void EnemyMovement::Update(float deltaTime){
	//if enemy is too close, flee behaviour
	if(abs(GetDistance(_self->GetPosition(), _target->GetPosition())) < 1.f){
		movementVector.x = (_self->GetPosition().x - _target->GetPosition().x);
		movementVector.y = 0;
		movementVector.z = 0;
	}
	//else go towards player
	else{
		movementVector.x = (_target->GetPosition().x - _self->GetPosition().x);
		movementVector.y = 0;
		movementVector.z = 0;
	}
	
	_body->SetLinearVelocity(movementVector * moveSpeed);
}

float EnemyMovement::GetDistance(glm::vec3 A, glm::vec3 B){
	float x = A.x - B.x;
	x = pow(x, 2);
	float y = A.y - B.y;
	y = pow(y, 2);

	return sqrt(x+y);
}

EnemyMovement::EnemyMovement() :
	IComponent()
{ }

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

void EnemyMovement::setSelf(Gameplay::GameObject::Sptr self){
	_self = self;
}

	
void EnemyMovement::setSpeed(float speed){
	moveSpeed = speed;
}
	
void EnemyMovement::setTarget(Gameplay::GameObject::Sptr target){
	_target = target;
}