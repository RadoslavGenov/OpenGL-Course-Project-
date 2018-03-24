//
//  camera.cpp
//  TestGL
//
//  Created by Radoka on 3/24/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar){
    this->m_perspective = glm::perspective(fov, aspect, zNear, zFar);
    this->m_position = pos;
    this->m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
    this->m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->m_rotation = glm::quat(1, 0, 0, 0);
}

void Camera::MoveForward(float amount){
    this->m_position += amount;
}

void Camera::MoveRight(float amount){
    this->m_position += glm::cross(this->m_up, this->m_forward) + amount;
}

void Camera::Pitch(float angle)
{
    glm::vec3 right = glm::normalize(glm::cross(this->m_up, this->m_forward));
    
    this->m_forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(this->m_forward, 0.0)));
    this->m_up = glm::normalize(glm::cross(this->m_forward, right));
}

void Camera::RotateY(float angle)
{
    static const glm::vec3 UP(0.0f, 1.0f, 0.0f);
    
    glm::mat4 rotation = glm::rotate(angle, UP);
    
    this->m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(this->m_forward, 0.0)));
    this->m_up = glm::vec3(glm::normalize(rotation * glm::vec4(this->m_up, 0.0)));
}

void Camera::Rotate(float angle, const glm::vec3& axis)
{
    m_rotation = glm::rotate(m_rotation, angle, axis);
    m_position *= glm::vec3(m_rotation.x, m_rotation.y, m_rotation.z);
}
