#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "Screen.h"
#include "Swarm.h"

using namespace std;
using namespace window;

int main() {
	
	// `srand` seeds the random number generator to produce different numbers every time the program is run
	srand(time(NULL));
	
	Screen screen;
	
	if (!screen.init()) {
		cout << "Error initialising SDL." << endl;
	}
	
	Swarm swarm;
	const int SCREEN_WIDTH_BY_2 = Screen::SCREEN_WIDTH / 2;
	const int SCREEN_HEIGHT_BY_2 = Screen::SCREEN_HEIGHT / 2;
	
	while (true) {
		/* Update particles */
		
		int elapsed = SDL_GetTicks();
		swarm.update(elapsed);
		
		/* Draw particles */
		
		// Max size of unsigned char is 127, will not go above 255
		unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);

		const Particle *const pParticles = swarm.getParticles();
		
		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];
			// Add 1 to get from 0 to 2 instead on -1 to 1
			int x = (particle.m_x + 1) * SCREEN_WIDTH_BY_2;
			// Center y position
			int y = particle.m_y * SCREEN_WIDTH_BY_2 + SCREEN_HEIGHT_BY_2;
			
			screen.setPixel(x, y, red, green, blue);
		}
		
		screen.boxBlur();
		
		/* Draw the screen */
		
		screen.update();
		
		/* Check for messages/events */
		
		if (!screen.processEvents()) {
			break;
		}
	}
	
	screen.close();
	
	return 0;
}
