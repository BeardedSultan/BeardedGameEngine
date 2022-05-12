#include "x64\src\graphics\window.h"
#include "x64\src\maths\maths.h"
#include "x64\src\utils\fileutils.h"
#include "x64\src\graphics\shader.h"

#include "x64\src\graphics\buffers\buffer.h"
#include "x64\src\graphics\buffers\indexbuffer.h"
#include "x64\src\graphics\buffers\vertexarray.h"

#include "x64\src\graphics\renderable2d.h"
#include "x64\src\graphics\simple2drenderer.h"
#include "x64\src\graphics\batchrenderer2d.h"
#include "x64\src\graphics\static_sprite.h"
#include "x64\src\graphics\sprite.h"
#include "x64\src\utils\timer.h"

#include <vector>
#include <time.h>

int main()
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 1280, 720);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);


	std::vector<Renderable2D*> sprites; 
	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 1) {
		for (float x = 0.1; x < 16.0f; x += 1) {
			sprites.push_back(new Sprite(x, y, 0.8f, 0.8f, maths::vec4(rand() % 1000 / 1000.0f, 0, rand() % 1000 / 1000.0f, 1)));
		}
	}

	BatchRenderer2D renderer;

	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;

	while (!window.closed()) {

		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

		renderer.begin();
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}
		renderer.end();
		renderer.flush();

		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f; 
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	return 0;
}