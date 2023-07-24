#ifndef _STRAIGHT_BLOCK_H_
#define _STRAIGHT_BLOCK_H_


#include "Block.h"

class StraightBlock : public Block
{
public:
    StraightBlock(double size, float angle, float x, float y);
    void draw(Shader &shaderProgram) override;
};

#endif