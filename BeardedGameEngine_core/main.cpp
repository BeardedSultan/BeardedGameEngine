#include "x64\src\graphics\window.h"
#include "x64\src\maths\maths.h"
#include "x64\src\utils\fileutils.h"
#include "x64\src\graphics\shader.h"

#include "x64\src\graphics\buffers\buffer.h"
#include "x64\src\graphics\buffers\indexbuffer.h"
#include "x64\src\graphics\buffers\vertexarray.h"

#include "x64\src\graphics\renderable2d.h"
#include "x64\src\graphics\simple2drenderer.h"
#include "x64\src\graphics\static_sprite.h"

int main()
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 1280, 720);

	mat4 ortho = mat4::orthograhic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0, 1, 0, 1), shader);
	Simple2DRenderer renderer;

	while (!window.closed()) {
		window.clear();
		
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

	return 0;
}