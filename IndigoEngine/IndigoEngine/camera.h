#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum direction {
	NONE = 0,
	FORWARD,
	BACKWARDS,
	RIGHT,
	LEFT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	void ProcessKeyboardInput(direction movementDirection, float deltaTime);
	void ProcessMouseInput(float xoffset, float yoffset);
	glm::mat4 GetViewMatrix() const;
	glm::vec3 getPos() const;
	glm::vec3 getFront() const;

private:

	float	m_speed,
			m_sensitivity,
			m_zoom,
			m_yaw,
			m_pitch;

	glm::vec3	m_position,
				m_front,
				m_right,
				m_up,
				m_worldUp;

	void UpdateCameraVectors();
};
