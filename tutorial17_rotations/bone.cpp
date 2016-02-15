#include "bone.h"

Bone::Bone()
{
    mScale = vec3(1.0, 1.0, 1.0);
    mPos   = vec3(0, 0, 0);
}

Bone::Bone(vec3 angles_deg, vec3 pos, vec3 scale, std::string name)
{
    label = name;
    std::cout<<"Initing bone: "<<label<<"\n";

    is_root = false;

    mScale = scale;
    mPos   = pos;

    quat rotation(radians(angles_deg));
    mOrientation = rotation;

    printf("\nInited Bone\n");
}

void Bone::update(vec3 rotate_angles_deg, vec3 move_by, vec3 scale_by){
    quat rotation(radians(rotate_angles_deg));
    mOrientation *= rotation;

    mat4 RotationMatrix = toMat4(mOrientation);

    mPos   += move_by;
    mScale *= scale_by;

    mat4 TranslationMatrix = translate(mat4(), mPos);
    mat4 ScalingMatrix = glm::scale(mat4(), mScale);
    ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
}

mat4 Bone::get_model_matrix(){
    std::cout<<label<<": getting matrix\n";

    mat4 RotationMatrix = toMat4(mOrientation);

    std::cout<<label<<": TranslationMatrix\n";
    mat4 TranslationMatrix = translate(mat4(), mPos);

    std::cout<<label<<": ScalingMatrix\n";
    mat4 ScalingMatrix = glm::scale(mat4(), mScale);

    if(is_root){
        std::cout<<label<<": ModelMatrix=**\n";

        ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
    }else{
        std::cout<<label<<": getting parent matrix\n";
        mat4 ParentModelMatrix = parent->get_model_matrix();
        std::cout<<label<<": GOTTEN parent matrix\n";

        ModelMatrix = ParentModelMatrix * TranslationMatrix * RotationMatrix * ScalingMatrix;
        std::cout<<label<<": MULTIPLIED parent matrix\n";

    }
    std::cout<<label<<": returning matrix\n";

    return ModelMatrix;
}



void Bone::add_child(Bone *bone){
    bone->parent = this;
    children.push_back(bone);
}







