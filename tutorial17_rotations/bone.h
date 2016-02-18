#ifndef BONE_H
#define BONE_H

#include <iostream>

class Bone
{
    public:
        Bone();
        Bone(std::string label);
        void add_child(Bone *chile);
        void set_parent(Bone *parent);
        void update_by_angle(vec3 rotate_angles_deg);

        std::string label;
        std::vector<Bone*> children;
        Bone* parent;

        vec3 mScale;
        vec3 mPos;
        quat mOrientation;

        mat4 ModelMatrix;

    private:
        void init_vars();

};

#endif // BONE_H
