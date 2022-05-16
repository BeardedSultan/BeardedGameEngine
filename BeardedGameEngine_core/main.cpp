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

#include "x64\src\graphics\layers\layer.h"
#include "x64\src\graphics\layers\tilelayer.h"
#include "x64\src\graphics\layers\group.h"

#include <vector>
#include <time.h>
#include "x64\src\graphics\texture.h"

int main()
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 1280, 720);

	srand(time(NULL));
	
	Shader* shader = new Shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	Shader& s = *shader;

	TileLayer layer(shader);
	for (float y = -8.9f; y < 9.0f; y += 3) {
		for (float x = -15.9f; x < 16.0f; x += 3) {
			layer.add(new Sprite(x, y, 2.8f, 2.8f, maths::vec4(rand() % 1000 / 1000.0f, 0, rand() % 1000 / 1000.0f, 1)));
		}
	}

	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;

	glActiveTexture(GL_TEXTURE0);
	Texture texture("alto.png");
	texture.bind();

	while (!window.closed()) {

		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		s.enable();
		s.setUniform2f("light_pos", vec2((float)(x * 32.0f / 1280.0f - 16.0f), (float)(9.0f - y * 18.0f / 720.0f)));

		layer.render();

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
