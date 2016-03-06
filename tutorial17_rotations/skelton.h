#ifndef SKELTON_H
#define SKELTON_H

#include <iostream>
#include "bone.h"


class Skelton
{
    public:
        Skelton();
        void update_bone(std::string _label, glm::vec3 angles);
        Skelton(Bone* _root);
        Bone* root;
        GLuint MatrixID, ModelMatrixID;
        GLsizei indices_count;
        void render(mat4 ProjectionMatrix, mat4 ViewMatrix);

        void point_to(vec3 target);


    private:
        void update_bone(Bone* bone, std::string _label, glm::vec3 angles);
        void draw_single_bone(Bone* bone, mat4 ProjectionMatrix, mat4 ViewMatrix);
        void render_root_down(Bone* root, mat4 ProjectionMatrix, mat4 ViewMatrix);

};

#endif // SKELTON_H
