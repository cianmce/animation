#include "skelton.h"

Skelton::Skelton()
{

}

Skelton::Skelton(Bone* _root)
{
    std::cout<<"\n\tSetting root\n\n";
    this->root = _root;
}

void Skelton::update_bone(std::string _label, glm::vec3 angles)
{
    this->update_bone(this->root, _label, angles);
}


void Skelton::update_bone(Bone *bone, std::string _label, glm::vec3 angles)
{
    // If bone == label then update this and return
    if(bone->label == _label){
        bone->update_by_angle(angles);
        return;
    }
    // Else try all children
    for(int i=0; i<bone->children.size(); i++){
        this->update_bone(bone->children[i], _label, angles);
    }
}

void Skelton::render(mat4 ProjectionMatrix, mat4 ViewMatrix)
{
    this->render_root_down(this->root, ProjectionMatrix, ViewMatrix);
}



void Skelton::draw_single_bone(Bone* bone, mat4 ProjectionMatrix, mat4 ViewMatrix)
{
    mat4 ModelMatrix = bone->ModelMatrix;

    mat4 MVP         = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(this->MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(this->ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

    // draw the triangles !
    glDrawElements(
        GL_TRIANGLES,      // mode
        this->indices_count,    // count
        GL_UNSIGNED_SHORT,   // type
        (void*)0           // element array buffer offset
    );
}

void Skelton::render_root_down(Bone* root, mat4 ProjectionMatrix, mat4 ViewMatrix)
{
    // draw itself
    this->draw_single_bone(root, ProjectionMatrix, ViewMatrix);
    int children_count = root->children.size();

    for(int i=0; i<children_count; i++){
        Bone* child = root->children[i];
        this->render_root_down(child, ProjectionMatrix, ViewMatrix);
    }
}

void Skelton::point_to(vec3 target){
    Bone *start = this->root->children[0]->children[0];
    // Bone *start = this->root;
    start->point_to(target);
//
//    Bone *hand = ->children[0];
//    std::cout << hand->label << ": " << glm::to_string(hand->end_effector_pos()) << " -> " << glm::to_string(target) << "\n";
//    vec3 angle_axis = degrees(hand->angle_axis_to(target));
//
//    //angle_axis *= 0.5;
//
//    std::cout << glm::to_string(angle_axis) << "\n";
//    if(glm::distance(hand->end_effector_pos(), target) > 0.5 ){
//        hand->update_by_angle(angle_axis);
//    }
}










