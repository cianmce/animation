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
    mLength      = vec3(0,0,2.0);
    parent       = NULL;
    this->threshold    = 0.5;
    this->set_lower_limit(-45);
    this->set_upper_limit(70);
}

void Bone::set_lower_limit(float limit)
{
    this->parent_angle_limit_lower = limit - this->threshold;
}
void Bone::set_upper_limit(float limit)
{
    this->parent_angle_limit_upper = limit + this->threshold;
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

    TranslationMatrix = translate(mat4(), mPos+mLength);
    this->end_effector_mat = TranslationMatrix * RotationMatrix * ScalingMatrix;

    if(this->parent!=NULL){
        // Has a parent
        this->ModelMatrix = this->parent->ModelMatrix * this->ModelMatrix;
        this->end_effector_mat = this->parent->ModelMatrix * this->end_effector_mat;

        if(this->parent->parent!=NULL){
            vec3 direction_vec = vec3(this->ModelMatrix[2]);
            vec3 parent_direction_vec = vec3(this->parent->ModelMatrix[2]);

            float angle_to_parent = degrees(this->signed_angle(direction_vec, parent_direction_vec));

            vec3 cross = glm::cross(direction_vec, parent_direction_vec);




            if( angle_to_parent < parent_angle_limit_lower || angle_to_parent > parent_angle_limit_upper ){
                this->ModelMatrix  = mat4(prev_model_mat);
                this->mOrientation = quat(prev_orientation);
            }
        }
    }

    if(this->label=="0_Mid"){
        // this->ModelMatrix = glm::translate(this->ModelMatrix, vec3(0.0f, 0.1f, 0.1f));



        std::cout << this->label << " - global_position: \n";
        std::cout << glm::to_string(this->global_position());
        std::cout << "\t";
        std::cout << glm::to_string(this->end_effector_pos());
        std::cout << "\n\n";

    }

    // Update all children
    for(int i=0; i<this->children.size(); i++){
        vec3 empty_angles = vec3(0,0,0);
        this->children[i]->update_by_angle(empty_angles);
    }
}

vec3 Bone::global_position(){
    // return vec3(this->ModelMatrix[3][0], this->ModelMatrix[3][1], this->ModelMatrix[3][2]);
    return vec3(this->ModelMatrix[3]);
}

vec3 Bone::end_effector_pos(){
    return vec3(this->end_effector_mat[3]);
}


float Bone::signed_angle(vec3 Va, vec3 Vb)
{
    float magnitude = acos(dot(normalize(Va), normalize(Vb)));
    vec3 axis = normalize(cross(Va, Vb));
    if(axis[2]>0){
        magnitude = -magnitude;
    }
    return magnitude;
}









