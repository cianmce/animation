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
    mLength      = vec3(0,0,2.0) * mScale;
    parent       = NULL;
    this->set_lower_limit(-15);
    this->set_upper_limit(70);
}

void Bone::set_lower_limit(float limit)
{
    this->parent_angle_limit_lower = limit;
}
void Bone::set_upper_limit(float limit)
{
    this->parent_angle_limit_upper = limit;
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


void Bone::update_by_angle(vec3 rotate_angles){
    quat prev_orientation = quat(this->mOrientation);

    bool is_finger = this->label=="0_Finger2" || this->label=="0_Finger1" || this->label=="0_Finger0";

    if(is_finger){
        rotate_angles.z = 0.0f;
        rotate_angles.y = 0.0f;
    }

    if(rotate_angles != vec3(0,0,0)){
         quat rotation(rotate_angles);
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

        if(is_finger){
            vec3 parent_angle_axis = this->angle_to_parent();
            float parent_x_angle_deg = degrees(parent_angle_axis.x);
            std::cout << "parent_angle_axis: "<<parent_x_angle_deg<<"\n";
            if(parent_x_angle_deg > parent_angle_limit_upper || parent_x_angle_deg < parent_angle_limit_lower){
                // revert
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

vec3 Bone::global_position(){
    // return vec3(this->ModelMatrix[3][0], this->ModelMatrix[3][1], this->ModelMatrix[3][2]);
    return vec3(this->ModelMatrix[3]);
}

vec3 Bone::end_effector_pos(){
    if(this->children.size()>0){
        return this->children[0]->end_effector_pos();
    }

    mat4 RotationMatrix    = toMat4(mOrientation);
    mat4 TranslationMatrix = translate(mat4(), mLength);
    // This model
    mat4 childModelMatrix  = TranslationMatrix * RotationMatrix;
    childModelMatrix = this->ModelMatrix * childModelMatrix;

    return vec3(childModelMatrix[3]);
}

void Bone::point_to(vec3 target){
    vec3 angle_axis = this->angle_axis_to(target);

//    std::cout << glm::to_string(angle_axis) << "\n";
    this->update_by_angle(angle_axis);

    if(this->parent!=NULL){
        this->parent->point_to(target);
    }
}

vec3 Bone::angle_axis_to(vec3 target){
    vec3 to_target = this->global_position() - target;
    to_target      = target - this->global_position();
    vec3 to_end    = this->global_position() - this->end_effector_pos();
    to_end         = this->end_effector_pos() - this->global_position();

    float angle = -1.0*acos(dot(normalize(to_target), normalize(to_end)));
    if (glm::abs(angle) > 1){
        angle /= 300;
    }else if (glm::abs(angle) > 0.5){
        angle /= 20;
    }else if (glm::abs(angle) > 0.1){
        angle /= 10;
    }

    vec3 axis = normalize(cross(to_target, to_end));

    axis = glm::mat3(glm::inverse(this->ModelMatrix)) * axis;
    axis = normalize(axis);

    vec3 angle_axis = axis * angle;

    std::cout << "\n\t\tangle:\t" << angle << "\n";
//    std::cout << "\taxis:\t" << glm::to_string(axis) << "\n";

    if(glm::abs(angle-3.14159) < 0.001 || glm::abs(angle) < 0.001 || std::isnan(angle)){
        angle_axis = vec3(0, 0, 0);
    }
    return angle_axis;
}

vec3 Bone::angle_to_parent(){

    if(this->parent == NULL){
        return vec3(0,0,0);
    }

    vec3 Va = vec3(this->ModelMatrix[2]);
    vec3 Vb = vec3(this->parent->ModelMatrix[2]);

    float angle = acos(dot(normalize(Va), normalize(Vb)));
    vec3 axis = normalize(cross(Va, Vb));
    axis = glm::mat3(glm::inverse(this->ModelMatrix)) * axis;
    axis = normalize(axis);
    vec3 angle_axis = axis * angle;
    return angle_axis;
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









