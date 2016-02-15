#ifndef BONE_H
#define BONE_H

#include <iostream>

class Bone
{
    public:
        Bone();
        Bone(vec3 angles_deg, vec3 pos, vec3 scale, std::string name);



        void update(vec3 angles_deg, vec3 pos, vec3 scale);

        void add_child(Bone *bone);

        mat4 get_model_matrix();

        std::string label;

        bool is_root;

        // Public Vars
        mat4 ModelMatrix;
        // mat4 MVP;

    //private:
        // Private Vars
        Bone *parent;
        std::vector<Bone*> children;
        vec3 mScale;
        vec3 mPos;
        quat mOrientation;

};

#endif // BONE_H
