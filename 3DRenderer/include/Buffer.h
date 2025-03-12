#pragma once

#include <vector>
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
