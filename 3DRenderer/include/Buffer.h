#pragma once

#include <vector>
#include <string>
#include <Gl/glew.h>

#define BufferID unsigned int

template<typename T>
BufferID CreateBuffer(unsigned int type, const std::vector<T>& data);

template<typename T>
BufferID 
CreateBuffer(unsigned int type, const std::vector<T> &data)
{
    BufferID id;
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    return id;
}

enum EVertexAttributeType
{
    Int1,
    Int2,
    Int3,

    UInt1,
    UInt2,
    UInt3,

    Float1,
    Float2,
    Float3,

    Byte,
    UByte
};

static uint32_t GetSizeFromAttribType(EVertexAttributeType type)
{
    switch (type)
    {
        case EVertexAttributeType::Int1:             return sizeof(int32_t) * 1;
        case EVertexAttributeType::Int2:             return sizeof(int32_t) * 2;
        case EVertexAttributeType::Int3:             return sizeof(int32_t) * 3;
        case EVertexAttributeType::UInt1:            return sizeof(uint32_t) * 1;
        case EVertexAttributeType::UInt2:            return sizeof(uint32_t) * 2;
        case EVertexAttributeType::UInt3:            return sizeof(uint32_t) * 3;
        case EVertexAttributeType::Float1:           return sizeof(float) * 1;
        case EVertexAttributeType::Float2:           return sizeof(float) * 2;
        case EVertexAttributeType::Float3:           return sizeof(float) * 3;
        case EVertexAttributeType::Byte:             return sizeof(char) * 1;
        case EVertexAttributeType::UByte:            return sizeof(unsigned char) * 1;
    }
    return -1;
}

static uint32_t GetCountFromAttribType(EVertexAttributeType type)
{
    switch (type)
    {
        case EVertexAttributeType::Int1:            return 1;
        case EVertexAttributeType::Int2:            return 2;
        case EVertexAttributeType::Int3:            return 3;
        case EVertexAttributeType::UInt1:           return 1;
        case EVertexAttributeType::UInt2:           return 2;
        case EVertexAttributeType::UInt3:           return 3;
        case EVertexAttributeType::Float1:          return 1;
        case EVertexAttributeType::Float2:          return 2;
        case EVertexAttributeType::Float3:          return 3;
        case EVertexAttributeType::Byte:            return 1;
        case EVertexAttributeType::UByte:           return 1;
    }
    return -1;
}

static GLenum GetGLTypeFromAttribType(EVertexAttributeType type)
{
    switch (type)
    {
        case EVertexAttributeType::Int1:            return GL_INT;
        case EVertexAttributeType::Int2:            return GL_INT;
        case EVertexAttributeType::Int3:            return GL_INT;
        case EVertexAttributeType::UInt1:           return GL_UNSIGNED_INT;
        case EVertexAttributeType::UInt2:           return GL_UNSIGNED_INT;
        case EVertexAttributeType::UInt3:           return GL_UNSIGNED_INT;
        case EVertexAttributeType::Float1:          return GL_FLOAT;
        case EVertexAttributeType::Float2:          return GL_FLOAT;
        case EVertexAttributeType::Float3:          return GL_FLOAT;
        case EVertexAttributeType::Byte:            return GL_BYTE;
        case EVertexAttributeType::UByte:           return GL_UNSIGNED_BYTE;
    }
    return -1;
}

struct SVertexAttributeLayout
{
    EVertexAttributeType AttributeType;
    int Offset;

    SVertexAttributeLayout(EVertexAttributeType type, int offset) :
        AttributeType{type},
        Offset{offset}
    {
    }

    SVertexAttributeLayout(const SVertexAttributeLayout& other) :
        AttributeType{ other.AttributeType },
        Offset{ other.Offset } 
    {
    }

    SVertexAttributeLayout& operator=(const SVertexAttributeLayout& other)
    {
        AttributeType = other.AttributeType;
        Offset = other.Offset;
        return *this;
    }
};

struct SVertexBufferData
{
    std::vector<float> Vertices;
    std::vector<SVertexAttributeLayout> BufferLayouts;

    uint32_t GetStride()
    {
        uint32_t stride = 0;
        for (auto& layout : BufferLayouts)
        {
            stride += GetSizeFromAttribType(layout.AttributeType);
        }

        return stride;
    }
};
