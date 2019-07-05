#pragma once
#include "glew.h"
#include "../math/Math.h"
#include <cmath>
#include <iostream>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVTY = 0.1f;
const float ZOOM = 45.0f;

namespace gi
{

  enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    PITCH_UP,
    PITCH_DOWN,
    YAW_DOWN,
    YAW_UP
  };

  class Camera
  {
  public:
    //Camera Attributes
    Vec3 pos;
    Vec3 front;
    Vec3 up;
    Vec3 right;
    Vec3 worldUp;

    //Angle
    float yaw;
    float pitch;

    //Options
    float zoom;
    float MovementSpeed;
    float MouseSensitivity;

    bool firstMove = true;
    float prevMouseX, prevMouseY;

    float lastX, lastY;
    bool working = true;
    void SetWork(bool _input) { working = _input; }
    bool GetWork(void) { return working; }

    Mat4 LookAt(Vec3 _eye, Vec3 _center, Vec3 _up);
    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix

      // Constructor with vectors
    Camera(Vec3 _position = Vec3(0.0f, 0.0f, 0.0f), Vec3 _up = Vec3(0.0f, 1.0f, 0.0f), float _yaw = YAW, float _pitch = PITCH)
      : front(Vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), zoom(ZOOM)
    {
      pos = _position;
      worldUp = _up;
      yaw = _yaw;
      pitch = _pitch;
      updateCameraVectors();
    }



    Mat4 GetViewMatrix()
    {
        if (working)
            return GetLookAt(pos, pos + front, up);
        else
        {
            return GetLookAt(Vec3(10000.f, 10000.f, 10000.f), Vec3(10001.f, 10001.f, 10001.f), up);
        }
      /*Mat4 viewMat;
      viewMat.Translate(-pos);
      return viewMat*GetLookAt(pos, front, up);*/

      //return LookAt(pos, pos + front, up);
      //return LookAt(pos, front, up);
    }

    // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {

      float velocity = MovementSpeed * deltaTime;
      if (direction == FORWARD)
        pos += front * velocity;
      if (direction == BACKWARD)
        pos -= front * velocity;
      if (direction == LEFT)
        pos -= right * velocity;
      if (direction == RIGHT)
        pos += right * velocity;
      if (direction == PITCH_UP)
      {
        pitch += 30.f * velocity;
        updateCameraVectors();
      }
      if (direction == PITCH_DOWN)
      {
        pitch -= 30.f * velocity;
        updateCameraVectors();
      }
      if (direction == YAW_DOWN)
      {
        yaw -= 30.f *  velocity;
        updateCameraVectors();
      }
      if (direction == YAW_UP)
      {
        yaw += 30.f *  velocity;
        updateCameraVectors();
      }
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
            updateCameraVectors();
        }
        if (pitch < -89.0f)
        {
            pitch = -89.0f;
            updateCameraVectors();
        }
    }

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
      xoffset *= MouseSensitivity;
      yoffset *= MouseSensitivity;

      yaw += xoffset;
      pitch += yoffset;

      // TODO(DONGHO) : Make sure that when pitch is out of bounds, screen doesn't get flipped
      if (constrainPitch)
      {
        if (pitch > 89.0f)
          pitch = 89.0f;
        if (pitch < -89.0f)
          pitch = -89.0f;
      }

      // Update Front, Right and Up Vectors using the updated Eular angles
      updateCameraVectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
      if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
      if (zoom <= 1.0f)
        zoom = 1.0f;
      if (zoom >= 45.0f)
        zoom = 45.0f;
    }

  private:
    void updateCameraVectors()
    {
      // Calculate the new Front vector
      front.x = cos(DegreeToRadian(yaw)) * cos(DegreeToRadian(pitch));
      front.y = sin(DegreeToRadian(pitch));
      front.z = sin(DegreeToRadian(yaw)) * cos(DegreeToRadian(pitch));
      front.Normalize();
      // Also re-calculate the Right and Up vector
      right = (front.CrossProduct(worldUp)).Normalize();
      // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
      up = (right.CrossProduct(front)).Normalize();
    }
  };
}