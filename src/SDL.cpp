
#include <iostream>
#include "Screen.h"
#include <cmath>
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace maa;

int main() {


	srand(time(NULL));
	Screen screen;
	screen.init(0x00000000);


	Swarm swarm;

	screen.update();

	while (true) {


		int timeLeft = SDL_GetTicks();





		const Particle *pParticles = swarm.getParticle();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {

				unsigned char red = 128 * (1 + sin(0.0007 * timeLeft ));
				unsigned char green = 128 * (1 + sin(0.0002 * timeLeft+3));
				unsigned char blue = 128 * (1 + cos(0.0003 * timeLeft ));
				Particle particle = pParticles[i];

				int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
				int y = (particle.m_y + 1) * Screen::SCREEN_HEIGHT / 2;


				screen.setPixel(x, y, red, green, blue);
			}
		screen.boxBlur();
		screen.update();
		swarm.update(timeLeft);

		if (screen.processEvents()) break;

	}

		return 0;
	}
