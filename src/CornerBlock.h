#ifndef _CORNER_BLOCK_H_
#define _CORNER_BLOCK_H_

#include "Block.h"


class CornerBlock : public Block
{
public:
    CornerBlock(double size_, float angle, float x, float y);
    void draw(Shader &shaderProgram) override;
};

#endif