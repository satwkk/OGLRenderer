#pragma once

#include <memory>

class VertexArray;
class Shader;

class Renderer
{
public:
	bool Init();
	void ShutDown();
	inline Renderer* Get() { return s_Instance; }
	void Render(std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray>& vertexArray);
	
private:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;

public:
	static Renderer* s_Instance;
};