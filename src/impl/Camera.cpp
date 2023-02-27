#include "Camera.h"


glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(Position, Position + Front, camUp);
}

void Camera::updateCameraVectors(){
    glm::vec3 direction;
    direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    direction.y = sin(glm::radians(Pitch));
    direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(direction);
    camRight = glm::normalize(glm::cross(Front, WorldUp));
    camUp = glm::normalize(glm::cross(camRight, Front));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime){
    float velocity = MovementSpeed * deltaTime;
    float oldY = Position.y;

    switch (direction){
        case Forward:
            Position += velocity * Front;
            Position.y = oldY;
            break;
        
        case Backward:
            Position -= velocity * Front;
            Position.y = oldY;
            break;

        case Right:
            Position += velocity * camRight;
            break;

        case Left:
            Position -= velocity * camRight;
            break;

        case Up:
            Position += velocity * camUp;
            break;
            
        case Down:
            Position -= velocity * camUp;
            break;

        default:
            break;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constraintPitch){
    xOffset *= SENS;
    yOffset *= SENS;

    Yaw = glm::mod(Yaw + xOffset, 360.0f);
    Pitch += yOffset;
    if (constraintPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset){
    Zoom -= (float)yOffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 90.0f)
        Zoom = 90.0f;
}

