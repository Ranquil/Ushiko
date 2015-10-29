#pragma once
#include <GLES\gl.h>
#include <GLES2\gl2.h>
#include "..\core\ErrorHandler.h"
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>
//#include "Shader.h"

namespace graphics
{
	enum CAMERA_MOVEMENT{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		RESET
	};

	class Camera
	{
		//friend class shader;
	public:
		/**Moves camera to the desired direction, stops movement or resets position
		*/
		void moveCamera(CAMERA_MOVEMENT move);
		/**Sets camera position
		*/
		void setCameraPosition(glm::vec2 position);
		/**Sets camera movement speed
		*/
		void setSpeed(int speed){ _step = speed; }
		
		void useProjection(GLint windowLocation);

		/**
		Constructor takes vec2 window size
		*/
		Camera(glm::vec2 window);
		Camera(void){};
		~Camera();

	private:
		int _step = 1;
		glm::vec2 _displaySize;
		glm::vec2 _origin;
		glm::vec3 _position;
		float rotation;
		glm::mat4 _windowProjection, _viewProjection, _worldProjection;
		GLchar * _windowString = "window";
		GLchar * _viewString = "view";
		GLchar * _worldString = "world";
		GLint _windowLocation, _viewLocation, _worldLocation;
	};
}


