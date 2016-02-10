#include "bone.h"

Bone::Bone()
{
    printf("Init Bone\n\n");
}

void Bone::draw()
{
    printf("\nDrawing\n");
}

void Bone::rotate_deg(vec3 angles){
    rotate_rad(radians(angles));
}

void Bone::rotate_rad(vec3 angles){
    quat rotation(angles);
    mOrientation = mOrientation * rotation;
    mOrientation = mOrientation * rotation;
    mat4 RotationMatrix = toMat4(mOrientation);
}

void Bone::set_pos(vec3 pos){
    mPos = pos;
}

