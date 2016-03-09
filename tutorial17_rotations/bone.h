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
        vec3 global_position();
        vec3 end_effector_pos();
        void point_to(vec3 target);

        vec3 angle_axis_to(vec3 target); // returns vec3 of axis with angle

        std::string label;
        std::vector<Bone*> children;
        Bone* parent;

        vec3 mScale;
        vec3 mPos;
        vec3 mLength;
        quat mOrientation;


        mat4 ModelMatrix;

        void set_lower_limit(float limit);
        void set_upper_limit(float limit);
        float parent_angle_limit_lower;
        float parent_angle_limit_upper;
        float threshold;

    private:
        mat4 end_effector_mat;
        void init_vars();
        float signed_angle(vec3 Va, vec3 Vb);

};

#endif // BONE_H
