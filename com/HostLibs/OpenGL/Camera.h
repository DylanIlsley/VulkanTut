#pragma once
// -------------------------------
// SYSTEM INCLUDE FILES
#include <vector>
// -------------------------------
// LIBRARY INCLUDE FILES
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// -------------------------------
// LOCAL INCLUDE FILES

/// Enum storing the different possible camera movements
enum eCameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};;

// Macro default definitions
#define CAMERA_YAW_DEFAULT					-90.0f
#define CAMERA_PITCH_DEFAULT				0.0f
#define CAMERA_SPEED_DEAFULT				3.0f
#define CAMERA_MOUSE_SENSITIVTY_DEFAULT		0.1f
#define CAMERA_ZOOM_DEFAULT					45.0f

/// Class used to construct a camera viewpoint
class cCamera
{
public:
	/// Constructor
	/// @param[in] Position			The starting position of the camera, defaulted to 0,0,0
	/// @param[in] UpDirection		The up direction of the camera, defaulted to 0,1,0
	/// @param[in] fYaw				The starting yaw value of the camera, defaulted to the global default
	/// @param[in] fPitch			The starting pitch value of the camera, defaulted to the global default
	cCamera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 UpDirection = glm::vec3(0.0f, 1.0f, 0.0f), float fYaw = CAMERA_YAW_DEFAULT, float fPitch = CAMERA_PITCH_DEFAULT) :
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		m_fMovementSpeed(CAMERA_SPEED_DEAFULT),
		m_fMouseSensitivity(CAMERA_MOUSE_SENSITIVTY_DEFAULT),
		m_fZoom(CAMERA_ZOOM_DEFAULT),
		m_Position(Position),
		m_Up(UpDirection),
		m_WorldUp(UpDirection),
		m_fYaw(fYaw),
		m_fPitch(fPitch)
	{
		UpdateCameraVectors();
	}

	/// Constructor with scalar values
	/// @param[in] fPosX	The starting X position of the camera
	/// @param[in] fPosY	The starting Y position of the camera
	/// @param[in] fPosZ	The starting Z position of the camera
	/// @param[in] fUpX		The Up direction's X value
	/// @param[in] fUpY		The Up direction's Y value
	/// @param[in] fUpZ		The Up direction's Z value
	/// @param[in] fYaw		The starting yaw value for the camera
	/// @param[in] fPitch	The starting pitch value for the camera
	cCamera(float fPosX, float fPosY, float fPosZ, float fUpX, float fUpY, float fUpZ, float fYaw, float fPitch) :
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		m_fMovementSpeed(CAMERA_SPEED_DEAFULT),
		m_fMouseSensitivity(CAMERA_MOUSE_SENSITIVTY_DEFAULT),
		m_fZoom(CAMERA_ZOOM_DEFAULT),
		m_Position(fPosX, fPosY, fPosZ),
		m_WorldUp(fUpX, fUpY, fUpZ),
		m_fYaw(fYaw),
		m_fPitch(fPitch)
	{
		UpdateCameraVectors();
	}

	/// Gets the view matrix from the camera
	/// return		The view matrix calculated by the camera
	glm::mat4 GetViewMatrix()
	{
		// Only recalculate the view matrix if the view has been changed
		if (m_bViewChanged) {
			m_CurrentViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
			m_bViewChanged = false;
		}

		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	/// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	/// @param[in] Direction		The direction of the camera movement
	/// @param[in] fDeltaTime		The time difference from the last frame, dictates how much the camera position should be updated
	void ProcessKeyboard(eCameraMovement Direction, float fDeltaTime)
	{
		float velocity = m_fMovementSpeed * fDeltaTime;
		if (Direction == FORWARD)
			m_Position += m_Front * velocity;
		if (Direction == BACKWARD)
			m_Position -= m_Front * velocity;
		if (Direction == LEFT)
			m_Position -= m_Right * velocity;
		if (Direction == RIGHT)
			m_Position += m_Right * velocity;
	}

	void KeyTester(int iKeyNumber)
	{
		std::cout << "KeyPressed!" + std::to_string(iKeyNumber);
	}

	/// Handles movement of the mouse to update pitch and yaw
	/// @param[in] fXOffset			The offset of the x position from its previous position
	/// @param[in] fYOffset			The offset of the y position from its previous position
	/// @param[in] ConstainPitch	Whether the pitch values should be clamped
	void ProcessMouseMovement(float fXOffset, float fYOffset, GLboolean ConstrainPitch = true)
	{
		fXOffset *= m_fMouseSensitivity;
		fYOffset *= m_fMouseSensitivity;
		m_fYaw += fXOffset;
		m_fPitch += fYOffset;

		if (ConstrainPitch)
		{
			if (m_fPitch > 89.0f)
				m_fPitch = 89.0f;
			else if (m_fPitch < -89.0f)
				m_fPitch = -89.0f;
		}
		// update Front, Right, and Up Vectors using the updated Euler angles
		UpdateCameraVectors();
	}

	/// Handles scrolling of the mouse wheel
	void ProcessMouseScroll(float fYOffset)
	{
		m_fZoom -= (float)fYOffset;
		if (m_fZoom < 1.0f)
			m_fZoom = 1.0f;
		else if (m_fZoom > 45.0f)
			m_fZoom = 45.0f;
	}

	/// Get the current zoom level of the camera
	/// return			The zoom level of the camera
	float GetZoom()
	{
		return m_fZoom;
	}

	glm::vec3 GetPosition()
	{
		return m_Position;
	}

private:
	/// Updates the direction vectors of the camera
	void UpdateCameraVectors()
	{
		m_bViewChanged = true;

		glm::vec3 front;
		front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
		front.y = -1.0f * sin(glm::radians(m_fPitch));
		front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
	// camera Attributes
	glm::vec3 m_Position; ///< The position of the camera
	glm::vec3 m_Front; ///< local store of the front direction for the camera
	glm::vec3 m_Up; ///< Local store of the up direction for the camera
	glm::vec3 m_Right; ///< Local store of the right direction for the camera
	glm::vec3 m_WorldUp; ///< Local store of the world's up direction

	//Euler angles
	float m_fYaw;
	float m_fPitch;
	// Camera options
	float m_fMovementSpeed; ///< How quickly the camera should move
	float m_fMouseSensitivity; ///< How sensitive the mouse should be to zooming
	float m_fZoom; ///< Local store of the current zoom level

	// View matrix variables
	glm::mat4 m_CurrentViewMatrix; ///< The current view matrix of the camera
	bool m_bViewChanged = true; ///< Whether the view point has changed since the last acquistion of the view matrix, defaulted to true.
};