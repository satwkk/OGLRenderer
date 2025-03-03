#pragma once

#include <GL/glew.h>
#include <string>
#include <map>

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& filePath, uint32_t slot);
	~Texture();

	void Bind();
	void UnBind();

private:
	uint32_t m_TextureID;
	uint32_t m_Slot;
};