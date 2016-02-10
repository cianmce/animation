#ifndef BONE_H
#define BONE_H


class Bone
{
    public:
        Bone();

        void rotate_deg(vec3 angles);
        void rotate_rad(vec3 angles);

        void set_pos(vec3 pos);

        void draw();


        mat4 get_MVP();

        // Public Vars
        mat4 ModelMatrix;
    //private:
        // Private Vars
        Bone *parent;
        std::vector<Bone*> children;
        vec3 mScale;
        vec3 mPos;
        quat mOrientation;
};

#endif // BONE_H
