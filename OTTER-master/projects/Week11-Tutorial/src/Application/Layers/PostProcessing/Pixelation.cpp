#include "Pixelation.h"

#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "../RenderLayer.h"
#include "Application/Application.h"

Pixelation::Pixelation() :
	PostProcessingLayer::Effect(),
	_shader(nullptr)
{
	Name = "Pixelate Effect";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/pixelation.glsl" }
	});
}

Pixelation::~Pixelation() = default;

void Pixelation::Apply(const Framebuffer::Sptr & gBuffer)
{

	_shader->Bind();
	_shader->SetUniform("amount", strength);
}

void Pixelation::RenderImGui()
{

	ImGui::SliderInt("Strength", &strength, 0.0f, 100.0f);
}

Pixelation::Sptr Pixelation::FromJson(const nlohmann::json & data)
{
	Pixelation::Sptr result = std::make_shared<Pixelation>();
	result->Enabled = JsonGet(data, "enabled", true);
	return result;
}

nlohmann::json Pixelation::ToJson() const
{
	return {
		{ "enabled", Enabled }
	};
}
