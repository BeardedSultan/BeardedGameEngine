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

#include <vector>
#include <time.h>

int main()
{
	using namespace beardedGameEngine;
	using namespace graphics;
	using namespace maths;

	Window window("BeardedGameEngine", 1280, 720);

	srand(time(NULL));

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader* shader = new Shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	Shader* shader2 = new Shader("x64/src/shaders/basic.vert", "x64/src/shaders/basic.frag");
	Shader& s = *shader;
	Shader& s2 = *shader2;
	//shader.setUniformMat4("pr_matrix", ortho);

	//std::vector<Renderable2D*> sprites; 
	//for (float y = 0.1; y < 9.0f; y += 1) {
	//	for (float x = 0.1; x < 16.0f; x += 1) {
	//		sprites.push_back(new Sprite(x, y, 0.8f, 0.8f, maths::vec4(rand() % 1000 / 1000.0f, 0, rand() % 1000 / 1000.0f, 1)));
	//	}
	//}
	//BatchRenderer2D renderer;

	TileLayer layer(shader);
	for (float y = -8.9f; y < 9.0f; y += 1) {
		for (float x = -15.9f; x < 16.0f; x += 1) {
			layer.add(new Sprite(x, y, 0.8f, 0.8f, maths::vec4(rand() % 1000 / 1000.0f, 0, rand() % 1000 / 1000.0f, 1)));
		}
	}

	Sprite* button = new Sprite(-15.0f, 5.0f, 6, 3, maths::vec4(1, 1, 1, 1));
	layer.add(button);
	//layer.push(maths::mat4(button->getPosition()));
	layer.add(new Sprite(0.5f, 0.5f, 5.0f, 2.0f, maths::vec4(1, 0, 1, 1)));
	//layer.pop(maths::mat4(button->getPosition()));

	TileLayer layer2(shader2);
	layer2.add(new Sprite(-2, -2, 4.0f, 4.0f, maths::vec4(0, rand() % 1000 / 1000.0f, rand() % 1000 / 1000.0f, 1)));

	Timer time;
	float timer = 0.0f;
	unsigned int frames = 0;

	while (!window.closed()) {

		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		s.enable();
		s.setUniform2f("light_pos", vec2((float)(x * 32.0f / 1280.0f - 16.0f), (float)(9.0f - y * 18.0f / 720.0f)));
		s2.enable();
		s2.setUniform2f("light_pos", vec2((float)(x * 32.0f / 1280.0f - 16.0f), (float)(9.0f - y * 18.0f / 720.0f)));

		layer.render();
		layer2.render();

		mat4 rotateA = mat4::rotation(time.elapsed() * 50.0f, vec3(0, 0, 1));
		s.setUniformMat4("ml_matrix", rotateA);
		mat4 rotateB = mat4::rotation(time.elapsed() * 50.0f, vec3(0, 0, 1));
		s2.setUniformMat4("ml_matrix", rotateB);

		/*renderer.begin();
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}
		renderer.end();
		renderer.flush();*/

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