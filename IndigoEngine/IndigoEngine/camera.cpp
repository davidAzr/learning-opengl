#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_speed(SPEED), m_sensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	m_position = position;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	UpdateCameraVectors();	
}

void Camera::ProcessKeyboardInput(direction movementDirection, float deltaTime)
{
	auto frameSpeed = m_speed * deltaTime;

	switch (movementDirection) {
		case FORWARD:
			m_position += frameSpeed * m_front;
			//m_position += glm::vec3(frameSpeed * m_front.x, 0.0f, frameSpeed * m_front.z);
			break;
		case BACKWARDS:
			m_position -= frameSpeed * m_front;
			//m_position -= glm::vec3(frameSpeed * m_front.x, 0.0f, frameSpeed * m_front.z);
			break;
		case RIGHT:
			m_position += frameSpeed * m_right;
			//m_position += glm::vec3(frameSpeed * m_right.x, 0.0f, frameSpeed * m_right.z);
			break;
		case LEFT:
			m_position -= frameSpeed * m_right;
			//m_position -= glm::vec3(frameSpeed * m_right.x, 0.0f, frameSpeed * m_right.z);
			break;
	}
}

void Camera::ProcessMouseInput(float xoffset, float yoffset)
{
	m_pitch += m_sensitivity * yoffset;
	m_yaw += m_sensitivity * xoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(direction);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
