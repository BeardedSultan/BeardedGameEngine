#include "x64\src\graphics\window.h"
#include "x64\src\maths\maths.h"
#include "x64\src\utils\fileutils.h"
#include "x64\src\graphics\shader.h"

int main()	
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 800, 600);
	//glClearColor(0.5f, 0.1f, 0.7f, 1.0f);
	
	GLfloat vertices[] =
	{
		4, 3, 0,
		12, 3, 0,
		4, 6, 0,
		4, 6, 0,
		12, 6, 0,
		4, 3, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	mat4 ortho = mat4::orthograhic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	shader.setUniform2f("light_pos", vec2(8.0f, 4.5f));
	shader.setUniform4f("colour", vec4(1.0f, 0.0f, 0.0f, 0.1f));

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

	while (!window.closed()) {
		window.clear();
		
		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

	return 0;
}