#include "Gameplay/Components/EnemyMovement.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"

void EnemyMovement::Awake(){
    _body = GetComponent<Gameplay::Physics::RigidBody>();
    if(_body == nullptr){
        IsEnabled = false;
    }
}

void Enemymovement::Update(float deltaTime){

}

void EnemyMovement::setTarget(glm::vec3 position){
    target = position;
}