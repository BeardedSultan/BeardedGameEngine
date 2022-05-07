#include "x64\src\graphics\window.h"
#include "x64\src\maths\maths.h"
#include "x64\src\utils\fileutils.h"

int main()	
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 800, 600);
	glClearColor(0.5f, 0.1f, 0.7f, 1.0f);

	std::string file = read_file("main.cpp");
	std::cout << file << std::endl;

	/*
	mat4 a = mat4::orthograhic(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
	std::cout << a << std::endl;
	mat4 b = mat4::perspective(5.0f, 10.0f, 1.5f, 2.0f);
	std::cout << b << std::endl;
	a *= b;
	std::cout << a << std::endl;
	mat4 c = mat4::rotation(60.0f, vec3(2.0f, 3.0f, 4.0f));
	std::cout << c << std::endl;
	vec4 column = a.columns[3];
	std::cout << column << std::endl;
	*/

	/*
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	*/

	while (!window.closed()) {
		window.clear();
		
		#if 0
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		#elseif 0
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
		#endif

		window.update();
	}

	return 0;
}