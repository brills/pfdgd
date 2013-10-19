#include "bhtree/body.h"
#include "bhtree/quad.h"
#include "bhtree/bhtree.h"

#include "SDL.h"
#include "SDL_gfxPrimitives.h"

#include <unistd.h>
#include <memory>

#define N 3 
#define FPS 120

using namespace std;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;
const char* WINDOW_TITLE = "SDL Start";

int main(int argc, char** argv) {

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                         SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption(WINDOW_TITLE, 0);
  SDL_Event event;

	Body mybodies[N];
  srand(0);
  for (int i = 0; i < N; ++i) {
    mybodies[i].set_px(rand() / (double)RAND_MAX);
    mybodies[i].set_py(rand() / (double)RAND_MAX);
    mybodies[i].set_mass(rand() / (double)RAND_MAX);
  }

  bool gameRunning = true;
	unique_ptr<BHTree> bhtree;
	Quad main_quad(0,1,0,1);

	int cnt = 0;
  while (gameRunning) {
		int ticks = SDL_GetTicks();
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameRunning = false;
      }
    }
			bhtree.reset(new BHTree(main_quad, NULL));
			for (int i = 0; i < N; ++i) {
				bhtree->Insert(mybodies[i]);
			}

			// Update force
			for (int i = 0; i < N; ++i) {
				bhtree->UpdateForce(&mybodies[i]);
				mybodies[i].Update(1 / (double)FPS);
			}

		// Draw bodies
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		for (int i = 0; i < N; ++i) {
			int x = mybodies[i].get_px() * WINDOW_HEIGHT;
			int y = mybodies[i].get_py() * WINDOW_WIDTH;

			ellipseRGBA(screen, x, y, 5, 5, 255, 255, 0, 200);
		}

    SDL_Flip(screen);
		int dticks = SDL_GetTicks() - ticks;
		if (dticks < 1000 / FPS) {
			SDL_Delay((1000 / FPS) - dticks);
		}
  }

  SDL_Quit();

  return 0;
}
