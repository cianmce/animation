#include "bone.h"


Bone::Bone()
{
}

Bone::Bone(std::string _label)
{
    label = _label;
    std::cout<<"Made: "<<label<<"\n";
    init_vars();
}

void Bone::init_vars()
{
    mOrientation = quat(vec3(0.0));
    mPos         = vec3(0.0);
    mScale       = vec3(1.0);
    parent       = NULL;
    parent_angle_limit = 80;
}

void Bone::set_parent(Bone *_parent)
{
    parent = _parent;
}

void Bone::add_child(Bone *_child)
{
    _child->set_parent(this);
    children.push_back(_child);
}

void Bone::update_by_angle(vec3 rotate_angles_deg){
    quat prev_orientation = quat(this->mOrientation);
    if(rotate_angles_deg != vec3(0,0,0)){
        quat rotation(radians(rotate_angles_deg));
        this->mOrientation *= rotation;
    }

    // Convert Orientation Quat to mat4
    mat4 RotationMatrix    = toMat4(mOrientation);
    mat4 TranslationMatrix = translate(mat4(), mPos);
    mat4 ScalingMatrix     = scale(mat4(), mScale);
    // This model
    mat4 prev_model_mat = mat4(this->ModelMatrix);
    this->ModelMatrix      = TranslationMatrix * RotationMatrix * ScalingMatrix;

    if(this->parent!=NULL){
        // Has a parent
        this->ModelMatrix = this->parent->ModelMatrix * this->ModelMatrix;

        if(this->parent->parent!=NULL){
            vec3 direction_vec = vec3(this->ModelMatrix[2]);
            vec3 parent_direction_vec = vec3(this->parent->ModelMatrix[2]);
            float dot_prod = glm::dot(direction_vec, parent_direction_vec);
            float len      = glm::length(direction_vec) * glm::length(parent_direction_vec);
            float angle_to_parent = glm::acos(dot_prod/len);
            std::cout<<"angle_to_parent: "<<degrees(angle_to_parent)<<"\n";

            if(glm::abs(degrees(angle_to_parent)) > parent_angle_limit){
                this->ModelMatrix  = mat4(prev_model_mat);
                this->mOrientation = quat(prev_orientation);
            }
        }
    }

    // Update all children
    for(int i=0; i<this->children.size(); i++){
        vec3 empty_angles = vec3(0,0,0);
        this->children[i]->update_by_angle(empty_angles);
    }
}









