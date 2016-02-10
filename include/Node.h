#ifndef NODE_H
#define NODE_H

#include <vector>




class Node
{
    typedef std::vector<Node*> NodeVector;

    public:
        Node();
        void rotate_deg(glm::vec3 angles);
        void rotate_rad(glm::vec3 angles);
        Node *parent;
        NodeVector children;
        glm::mat4 ModelMatrix;
//        glm::mat4 ViewMatrix;
//        glm::mat4 ProjectionMatrix;
//        glm::mat4 MVP;
        void draw();

        glm::quat gOrientation2;


    protected:
    private:
};

#endif // NODE_H
