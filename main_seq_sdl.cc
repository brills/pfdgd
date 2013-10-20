#include "bhtree/body.h"
#include "graph.h"
#include "dfdrawer.h"

#include "SDL.h"
#include "SDL_gfxPrimitives.h"

#include <memory>
#include <set>
#include <vector>
#include <unistd.h>

#define N 3
#define FPS 240

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

  if (argc <= 1) return -1;
  Graph graph(argv[1]);
  vector<Body>& node = graph.get_node();
  vector<set<int> >& adj = graph.get_adj();
  DFDrawer dfdrawer(&node, &adj);
  bool gameRunning = true;

  int cnt = 0;
  while (gameRunning) {
    int ticks = SDL_GetTicks();
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameRunning = false;
      }
    }

    dfdrawer.Iterate();
    // Draw bodies
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    for (auto& n : node) {
      int x = n.get_px() * WINDOW_HEIGHT;
      int y = n.get_py() * WINDOW_WIDTH;
      ellipseRGBA(screen, x, y, 5, 5, 255, 255, 0, 200);
    }

    for (int i = 0; i < adj.size(); ++i) {
      for (auto other_id : adj[i]) {
        int x1 = node[i].get_px() * WINDOW_HEIGHT;
        int x2 = node[other_id].get_px() * WINDOW_HEIGHT;
        int y1 = node[i].get_py() * WINDOW_WIDTH;
        int y2 = node[other_id].get_py() * WINDOW_WIDTH;

        lineRGBA(screen, x1, y1, x2, y2, 200, 200, 200, 200);
      }
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
