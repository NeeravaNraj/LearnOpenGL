#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <vector>
#define DEF_YAW -90.0f
#define DEF_PITCH 0.0f
#define MOVE_SPEED 2.5f
#define SENS 0.07f
#define FOV 45.0f


enum Camera_Movement {
    Forward, 
    Backward,
    Right,
    Left,
    Up,
    Down
};

class Camera {
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 camUp;
        glm::vec3 camRight;
        glm::vec3 WorldUp;

        float Yaw, Pitch, MovementSpeed, Sensitivity, Zoom;

        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEF_YAW, float pitch = DEF_PITCH) : Front(glm::vec3(0.0f, 0.0f, 1.0f)), MovementSpeed(MOVE_SPEED), Sensitivity(SENS), Zoom(FOV){
            Position = position;
            WorldUp = up;
            Yaw = yaw;  
            Pitch = pitch;
            updateCameraVectors();
        }


        Camera(float xpos, float ypos, float zpos, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, 1.0f)), MovementSpeed(MOVE_SPEED), Sensitivity(SENS), Zoom(FOV){
            Position = glm::vec3(xpos, ypos, zpos);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        glm::mat4 GetViewMatrix();

        void ProcessKeyboard(Camera_Movement direction, float deltaTime);
        void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constraintPitch = true);
        void ProcessMouseScroll(float yOffset);

    
    private:
        void updateCameraVectors();
};
#endif
