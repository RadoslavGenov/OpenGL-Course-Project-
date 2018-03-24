//
//  camera.hpp
//  TestGL
//
//  Created by Radoka on 3/14/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

class Camera {
    
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
    
    inline glm::mat4 GetViewProjection() const {
        return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
    }
    
    void MoveForward(float amount);
    
    void MoveRight(float amount);
    
    void Pitch(float angle);
    
    void RotateY(float angle);

    void Rotate(float angle, const glm::vec3& axis);
    
    glm::vec3 GetPos(){ return m_position; }
    
private:
    glm::mat4 m_perspective;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    glm::quat m_rotation;
};

#endif /* camera_hpp */
