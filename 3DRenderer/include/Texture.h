#pragma once

#include <string>
#include "Utility.h"

class CTexture
{
public:
	CTexture() = default;
	CTexture(const std::string& filePath, uint32_t slot);
	~CTexture();

	void Bind();
	void UnBind();

    bool IsLoaded() { return m_uTextureID != 0; }

	uint32_t GetSlot() { return m_uSlot; }
	uint32_t GetID() { return m_uTextureID; }

private:
	uint32_t m_uTextureID;
	uint32_t m_uSlot;
};
