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

#include <vector>
#include <time.h>

#define BATCH_RENDERER 1

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

	std::vector<Renderable2D*> sprites;
	srand(time(NULL));

	for (float y = 0; y < 9.0f; y+=0.1) {
		for (float x = 0; x < 16.0f; x+=0.1) {
			sprites.push_back(new 
			#if BATCH_RENDERER
			Sprite
			#else
			StaticSprite
			#endif
			(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, rand() % 1000 / 1000.0f, 1)
			#if !BATCH_RENDERER
			, shader
			#endif
			));
		}
	}

	#if BATCH_RENDERER
	//Sprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
	//Sprite sprite2(7, 1, 2, 3, maths::vec4(0, 1, 0, 1));
	BatchRenderer2D renderer;
	#else
	//StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	//StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0, 1, 0, 1), shader);
	Simple2DRenderer renderer;
	#endif

	while (!window.closed()) {
		window.clear();
		
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (float)(9.0f - y * 9.0f / 720.0f)));

		#if BATCH_RENDERER
		renderer.begin();
		#endif
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}
		#if BATCH_RENDERER
		renderer.end();
		#endif
		renderer.flush();

		window.update();
	}

	return 0;
}