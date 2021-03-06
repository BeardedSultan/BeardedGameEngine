#pragma once

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace beardedGameEngine { namespace graphics {

	#define MAX_KEYS 1024
	#define MAX_BUTTONS 32

	class Window
	{
	public:
		Window(const char *title, int width, int height);
		~Window();
		bool closed() const;
		void update();
		void clear() const;
		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
	public:
		bool isKeyPressed(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		void getMousePosition(double& xpos, double& ypos) const;
	private:
		//m stands for member var
		const char *m_Title;
		int m_Width, m_Height;
		friend struct GLFWWindow;
		GLFWwindow *m_Window;
		bool m_Closed;
	private:
		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double m_MouseX, m_MouseY;
	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	};

} }