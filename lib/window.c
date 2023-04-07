#include "../include/sdl2_game_engine/window/window.h"
#include "../include/pacman/pacman_init.h"
#include "../include/pacman/pacman/pacman.h"
#include "../include/pacman/pacman_action.h"

#include <unistd.h>

bool Initialize() {

	if(!Screen_Init(SCREEN_HEIGHT, SCREEN_WIDTH, FPS, WINDOW_TITLE)) {
		return false;
	}

	GLOBAL_DATA(lastTick) = SDL_GetTicks();

	/* ------------------------------------ */
	/* Initialize and Render the Characters */
	/* ------------------------------------ */

	characters.blinky_definition = Sprite_Define(&ghost, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, GHOST_HITBOX_XOFF, GHOST_HITBOX_XOFF, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, BLINKY_SPRITE);
	characters.pinky_definition = Sprite_Define(&ghost, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, GHOST_HITBOX_XOFF, GHOST_HITBOX_XOFF, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, PINKY_SPRITE);
	characters.inky_definition = Sprite_Define(&ghost, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, GHOST_HITBOX_XOFF, GHOST_HITBOX_XOFF, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, INKY_SPRITE);
	characters.clyde_definition = Sprite_Define(&ghost, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, GHOST_HITBOX_XOFF, GHOST_HITBOX_XOFF, GHOST_WIDTH, GHOST_SPRITE_HEIGHT, CLYDE_SPRITE);

	characters.pacman_definition = Sprite_Define(&pacman_anim, PACMAN_WIDTH, PACMAN_SPRITE_HEIGHT, PACMAN_HITBOX_XOFF, PACMAN_HITBOX_XOFF, PACMAN_WIDTH, PACMAN_SPRITE_HEIGHT, PACMAN_SPRITE);

	Sprites_Init();

	Sprite_Create_Instance(characters.blinky_definition, 0, 0, 0, 0, 0);
	Sprite_Create_Instance(characters.pinky_definition, 0, 300, 0, 0, 0);
	Sprite_Create_Instance(characters.inky_definition, 0, 600, 0, 0, 0);
	Sprite_Create_Instance(characters.clyde_definition, 0, 900, 0, 0, 0);

	int pacman_instance = Sprite_Create_Instance(characters.pacman_definition, 0, GLOBAL_DATA(screenCenter).x, GLOBAL_DATA(screenCenter).y, PACMAN_SPEED, PACMAN_SPEED);

	Sprite_Draw_Instances();

	Create_Player(&player, &sprite_instances[pacman_instance], 4);

	Action_Define(0, SDL_SCANCODE_UP, MOVE_UP, UP, Move_Up);
	Action_Define(0, SDL_SCANCODE_DOWN, MOVE_DOWN, DOWN, Move_Down);
	Action_Define(0, SDL_SCANCODE_LEFT, MOVE_LEFT, LEFT, Move_Left);
	Action_Define(0, SDL_SCANCODE_RIGHT, MOVE_RIGHT, RIGHT, Move_Right);

	return true;
}

void Update() {
	SDL_SetRenderDrawColor(GLOBAL_DATA(renderer), 0, 0, 0, 255);
	SDL_RenderClear(GLOBAL_DATA(renderer));
	GLOBAL_DATA(keyboardState) = SDL_GetKeyboardState(NULL);

	GLOBAL_DATA(curTick) = SDL_GetTicks();
	float diff = GLOBAL_DATA(curTick) - GLOBAL_DATA(lastTick);
 	GLOBAL_DATA(elapsed) = diff / 1000.f;

	/* -------------------- */
	/* 		Update Sprites 		*/
	/* -------------------- */

	Enable_Actions(0);

	Sprite_Update_Instances();

	SDL_RenderPresent(GLOBAL_DATA(renderer));

	GLOBAL_DATA(lastTick) = GLOBAL_DATA(curTick);

	if (GLOBAL_DATA(elapsed) < 1 / (INI_DATA(FPS))) {
	}
	else {
		sleep((GLOBAL_DATA(elapsed)) - 1 / (INI_DATA(FPS)));
	}
}

void Shutdown(void) {
	if (GLOBAL_DATA(renderer)) {
		SDL_DestroyRenderer(GLOBAL_DATA(renderer));
	}

	if (GLOBAL_DATA(window)) {
		SDL_DestroyWindow(GLOBAL_DATA(window));
	}

	for (int i = 0; i < MAX_PLAYERS; i++) {
		free(players[i]);
	}

	SDL_Quit();
}
