#include "Camera.h"

Camera::Camera (glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
    Position = position;
    WorldUp = worldup;
    Target = target;
    
	Forward = glm::normalize(Position - Target);
	Right = glm::cross(glm::normalize(WorldUp), Forward);
	Right = glm::normalize(Right);
	Up = glm::cross(Forward, Right);
	Up = glm::normalize(Up);
	const glm::vec3 yUnit(0, 1, 0);
	const glm::vec3 xUnit(1, 0, 0);
    const glm::vec3 zUnit(0, 0, 1);
    float pitch = glm::degrees(-glm::asin(glm::dot(Forward, yUnit)));
    glm::vec3 forward = Forward;
    forward.y = 0;
    forward = glm::normalize(forward);
    float yaw = glm::degrees(glm::acos(glm::dot(forward, xUnit)));
    if (glm::dot(forward, zUnit) > 0)
        yaw = 360 - yaw;
    Yaw = yaw;
    Pitch = pitch;
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
    Position = position;
    WorldUp = worldup;
    Pitch = pitch;
    Yaw = yaw;
    
    Forward.x = glm::cos(pitch) * glm::sin(yaw);
    Forward.y = glm::sin(pitch);
    Forward.z = glm::cos(pitch) * glm::cos(yaw);
    Forward = glm::normalize(Forward);
    
    Right = glm::cross(glm::normalize(WorldUp), Forward);
    Right = glm::normalize(Right);
    Up = glm::cross(Forward, Right);
    Up = glm::normalize(Up);
    Forward.z = -1.0f * Forward.z;
}

glm::mat4 Camera::GetViewMatrix()
{
    return LookAt();
}

void Camera::CameraUpdatePos()
{
    Position += Forward * SpeedZ  + Right * SpeedX + Up * SpeedY ;
}

glm::mat4 Camera::LookAt()
{
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rotat = glm::mat4(1.0f);
    
    trans[3][0] = -Position.x;
    trans[3][1] = -Position.y;
    trans[3][2] = -Position.z;
    rotat[0][0] = Right.x;
    rotat[1][0] = Right.y;
    rotat[2][0] = Right.z;
    rotat[0][1] = Up.x;
    rotat[1][1] = Up.y;
    rotat[2][1] = Up.z;
    rotat[0][2] = Forward.x;
    rotat[1][2] = Forward.y;
    rotat[2][2] = Forward.z;
    
    return rotat * trans;
}

void Camera::CameraUpdateVec()
{
    Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
    Forward = glm::normalize(Forward);
    
    Right = glm::cross(glm::normalize(WorldUp), Forward);
    Right = glm::normalize(Right);
    Up = glm::cross(Forward, Right);
    Up = glm::normalize(Up);
    Forward.z = -1.0f * Forward.z;
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY)
{
    deltaX *= glm::radians(0.001f);
    deltaY *= glm::radians(0.001f);

    Yaw   += deltaY;
    Pitch += deltaX;
    CameraUpdateVec();
}
