#include "x64\src\graphics\window.h"
#include "x64\src\maths\maths.h"
#include "x64\src\utils\fileutils.h"
#include "x64\src\graphics\shader.h"

#include "x64\src\graphics\buffers\buffer.h"
#include "x64\src\graphics\buffers\indexbuffer.h"
#include "x64\src\graphics\buffers\vertexarray.h"

int main()
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 1280, 720);

	GLfloat vertices[] =
	{
		0, 3, 0,
		0, 6, 0,
		8, 4, 0,
		8, 3, 0
	};
	GLfloat verticesB[] =
	{
		0, 3, 0,
		0, 6, 0,
		8, 6, 0,
		8, 3, 0
	};
	GLfloat verticesC[] =
	{
		0, 3, 0,
		0, 6, 0,
		//8, 6, 0,
		8, 3, 0
	};
	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	GLfloat colorsA[] =
	{
		1, 0, 0, 1,
		1, 0, 0, 1,
		1, 0, 0, 1,
		1, 0, 0, 1
	};
	GLfloat colorsB[] =
	{
		0, 0, 1, 1,
		0, 0, 1, 1,
		0, 0, 1, 1,
		0, 0, 1, 1
	};
	GLfloat colorsC[] =
	{
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1
	};
	VertexArray sprite1, sprite2, sprite3;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);
	sprite2.addBuffer(new Buffer(verticesB, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);
	sprite3.addBuffer(new Buffer(verticesC, 4 * 3, 3), 0);
	sprite3.addBuffer(new Buffer(colorsC, 4 * 4, 4), 1);

	mat4 ortho = mat4::orthograhic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

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
		
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.bind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.bind();
		sprite2.unbind();

		sprite3.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, -3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.bind();
		sprite3.unbind();

		window.update();
	}

	return 0;
}