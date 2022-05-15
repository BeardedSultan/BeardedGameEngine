#include "window.h"

namespace beardedGameEngine { namespace graphics {

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	/* WINDOW_SECTION */

	void window_resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	/* set window properties, initialize m_Keys[] and m_MouseButtons[] arrays */
	Window::Window(const char *title, int width, int height) 
	{
		m_Title = title;
		m_Width = width;
		m_Height = height;
		if (!init()) {
			glfwTerminate();
		}

		for (int i = 0; i < MAX_KEYS; i++) {
			m_Keys[i] = false;
		}
		for (int i = 0; i < MAX_BUTTONS; i++) {
			m_MouseButtons[i] = false;
		}
	}
	
	Window::~Window()
	{
		glfwTerminate();
	}

	/* initialize window, set callbacks for mouse buttons, keys and cursor */
	bool Window::init()
	{
		if (!glfwInit()) {
			std::cout << "Failed to initialize glfw." << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window) {
			std::cout << "Window creation error." << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0.0);

		if (glewInit() != GLEW_OK) {
			std::cout << "Could not initialize GLEW." << std::endl;
			return false;
		}

		std::cout << "OpenGL" << glGetString(GL_VERSION) << std::endl;
		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}
	
	void Window::update()
	{
		glfwPollEvents();
		//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
		glfwSwapBuffers(m_Window);
	}

	/*INPUT_SECTION*/

	/* callback adjusts value in corresponding array */
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*) glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	bool Window::isKeyPressed(unsigned int keycode) const
	{
		if (keycode >= MAX_KEYS) {
			//TODO: Log this
			return false;
		}
		return m_Keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button) const
	{
		if (button >= MAX_BUTTONS) {
			//TODO: Log this
			return false;
		}
		return m_MouseButtons[button];
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void Window::getMousePosition(double& xpos, double& ypos) const 
	{
		xpos = m_MouseX;
		ypos = m_MouseY;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseX = xpos;
		win->m_MouseY = ypos;
	}

} }