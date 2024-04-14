#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Environment.h"
#include "Renderer.h"
#include <time.h>
#include "Timer.h"
#include <vector>

#include <cstdlib>


static unsigned int windowWidth() { return 1024; }
static unsigned int windowHeight() { return 700; }
static float radius = 10.0f;
static Uint8 redness = 23;

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment * environment)
{
	std::cout << "Key pressed: " << key << std::endl;
}

/// <summary>
/// Called at each time step.
/// </summary>
static bool backwards = false;
void onSimulate()
{
  if (!backwards){
    radius += 0.05f;
    if (radius > 30.0f)
      backwards = true;
  }
  else{
    radius -= 0.05f;
    if (radius < 5.0f)
      backwards = false;
  }
  redness = (Uint8)(redness + 1) % 255;
}

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/)
{
  // Vector2<float> position1 = Vector2<float>(windowWidth()/2, windowHeight()/2);
  // Vector2<float> position2 = Vector2<float>(100, 100);
  // Vector2<float> position3 = Vector2<float>(100, 500);
  // Vector2<float> position4 = Vector2<float>(900, 100);
  std::string  str = "Hello World!";



	// 1 - Initialization of SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS/* | SDL_INIT_AUDIO*/) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	// 2 - Initialization of the renderer
	Renderer::initialize(windowWidth(), windowHeight());

	// 3 - Creation of an environment
	Environment environment(windowWidth(), windowHeight());

	// 4 - We change the seed of the random number generator
	srand((unsigned int)time(NULL));

	// The main event loop...
	SDL_Event event;
	bool exit = false;
	while (!exit) 
	{
		// 1 - We handle events 
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'q'))
			{
				::std::cout << "Exit signal detected" << ::std::endl;
				exit = true;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				onKeyPressed((char)event.key.keysym.sym, &environment);
			}
		}
      Renderer::Color color1(redness, 245, 45, 255);
      Renderer::Color color2(redness, 34, 245, 255);
      Renderer::Color color3(redness, 0, 190, 255);
      Renderer::Color color4(redness, 100, 45, 255);
      std::vector<Renderer::Color> colors = {color1, color2, color3, color4};
            // Generate a random index
      std::size_t randomIndex = std::rand() % colors.size();

      // Access the randomly chosen object
      Renderer::Color randomObject = colors[randomIndex];
	  //Renderer::getInstance()->drawString(position, str, color);
	  // Renderer::getInstance()->drawCircle(position1, radius, color1);
    // Renderer::getInstance()->drawCircle(position2, radius, color2);
    // Renderer::getInstance()->drawCircle(position3, radius, color3);
    // Renderer::getInstance()->drawCircle(position4, radius, color4);

    for (int i = 0; i < 100; i++)
    {
      //radius = (float)(rand() % 30 + 10);
      Renderer::getInstance()->drawCircle(Vector2<float>(rand() % windowWidth(), rand() % windowHeight()), radius, randomObject);
    }
    
		// 2 - We update the simulation
		Timer::update(0.5);
		onSimulate();
		// 3 - We render the scene
		Renderer::getInstance()->flush();
	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();

	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
