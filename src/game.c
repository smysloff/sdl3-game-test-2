#include "game.h"

extern Keyboard_t keyboard;
extern Controls_t controls;

Game_t game;


static void GameLoop_Events(void);
static void GameLoop_Update(void);
static void GameLoop_Render(void);

static void GameLoopUpdate_Menu(void);
static void GameLoopUpdate_Play(void);
static void GameLoopUpdate_Stop(void);
static void GameLoopRender_Menu(void);
static void GameLoopRender_Play(void);
static void GameLoopRender_Stop(void);

static void SetGameState(GameState state);


void Game_Init(void)
{
  SetGameState(GAME_STATE_INIT);

  if (SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("SDL_Init(). %s", SDL_GetError());
    Game_Quit();
  }

  if (!(game.window = SDL_CreateWindow(
    WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0))
  ) {
    SDL_Log("SDL_CreateWindow(). %s", SDL_GetError());
    Game_Quit();
  }

  if (!(game.renderer = SDL_CreateRenderer(
    game.window, NULL, SDL_RENDERER_ACCELERATED))
  ) {
    SDL_Log("SDL_CreateRenderer(). %s", SDL_GetError());
    Game_Quit();
  }

  if (TTF_Init())
  {
    SDL_Log("TTF_Init(). %s", TTF_GetError());
    Game_Quit();
  }

  if (!(game.font = TTF_OpenFont(FONT_PATH, GAME_NAME_SIZE)))
  {
    SDL_Log("TTF_OpenFont(). %s", TTF_GetError());
    Game_Quit();
  }

  SDL_Surface *surface;
  SDL_Color color = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };
  
  surface = TTF_RenderUTF8_Solid(game.font, GAME_NAME, color);
  game.title = SDL_CreateTextureFromSurface(game.renderer, surface);

  surface = TTF_RenderUTF8_Solid(game.font, "press any button to start", color);
  game.invite = SDL_CreateTextureFromSurface(game.renderer, surface);

  SDL_DestroySurface(surface);
  
  SetGameState(GAME_STATE_MENU);
}

void Game_Loop(void)
{
  while (game.state != GAME_STATE_OVER)
  {
    GameLoop_Events();
    GameLoop_Update();
    GameLoop_Render();
  }
}

void Game_Quit(void)
{
  if (game.font) TTF_CloseFont(game.font);
  if (TTF_WasInit()) TTF_Quit();

  if (game.renderer) SDL_DestroyRenderer(game.renderer);
  if (game.window) SDL_DestroyWindow(game.window);
  if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_Quit();
}


static void GameLoop_Events(void)
{
  while (SDL_PollEvent(&game.event))
  {
    switch (game.event.type)
    {
      case SDL_EVENT_QUIT:
	SetGameState(GAME_STATE_OVER);
      break;

      case SDL_EVENT_KEY_DOWN:
	Keyboard_KeyDownHandler(&game.event.key);
      break;
	
      case SDL_EVENT_KEY_UP:
	Keyboard_KeyUpHandler(&game.event.key);
      break;
	
      default: break;
    }
  }
}

static void GameLoop_Update(void)
{
  Controls_Update();

  switch (game.state)
  {
    case GAME_STATE_MENU: GameLoopUpdate_Menu(); break;
    case GAME_STATE_PLAY: GameLoopUpdate_Play(); break;
    case GAME_STATE_STOP: GameLoopUpdate_Stop(); break;
    default: break;
  }
}

static void GameLoop_Render(void)
{
  switch (game.state)
  {
    case GAME_STATE_MENU: GameLoopRender_Menu(); break;
    case GAME_STATE_PLAY: GameLoopRender_Play(); break;
    case GAME_STATE_STOP: GameLoopRender_Stop(); break;
    default: break;
  }
}

static void GameLoopUpdate_Menu(void)
{
  if (controls.escape) SetGameState(GAME_STATE_OVER);
  else if (controls.enter) SetGameState(GAME_STATE_PLAY);
}

static void GameLoopUpdate_Play(void)
{
  if (controls.escape) SetGameState(GAME_STATE_STOP);
}

static void GameLoopUpdate_Stop(void)
{
  if (controls.escape) SetGameState(GAME_STATE_OVER);
  else if (controls.enter) SetGameState(GAME_STATE_PLAY);
}

static void GameLoopRender_Menu(void)
{
  SDL_SetRenderDrawColor(game.renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game.renderer);

  SDL_FRect dstrect;
    
  dstrect.x = WINDOW_WIDTH / 2. - 250;
  dstrect.y = WINDOW_HEIGHT / 2. - 100 - 100;
  dstrect.w = 500;
  dstrect.h = 200;
  SDL_RenderTexture(game.renderer, game.title, NULL, &dstrect);

  dstrect.x = WINDOW_WIDTH / 2. - 300;
  dstrect.y = WINDOW_HEIGHT / 2. - 50 + 100;
  dstrect.w = 600;
  dstrect.h = 100;
  SDL_RenderTexture(game.renderer, game.invite, NULL, &dstrect);

  SDL_RenderPresent(game.renderer);
}

static void GameLoopRender_Play(void)
{
  SDL_SetRenderDrawColor(game.renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game.renderer);

  SDL_RenderPresent(game.renderer);
}

static void GameLoopRender_Stop(void)
{
  SDL_SetRenderDrawColor(game.renderer, 0x00, 0x00, 0xFF, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game.renderer);

  SDL_RenderPresent(game.renderer);
}

static void SetGameState(GameState state)
{
  game.state = state;
  bzero(&keyboard, sizeof(keyboard));
}
