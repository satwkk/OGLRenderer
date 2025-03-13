#pragma once

#include <string>
#include "Utility.h"

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& filePath, uint32_t slot);
	~Texture();

	void Bind();
	void UnBind();

    bool IsLoaded() { return m_TextureID != 0; }

	uint32_t GetSlot() { return m_Slot; }
	uint32_t GetID() { return m_TextureID; }

private:
	uint32_t m_TextureID;
	uint32_t m_Slot;
};
