/*
 * Swam.cpp
 *
 *  Created on: Jul 15, 2017
 *      Author: m7med
 */

#include "Swarm.h"


namespace maa {

Swarm::Swarm() {
	lastTime = 0;
	m_pParticles = new Particle[NPARTICLES];

}

Swarm::~Swarm() {
	delete [] m_pParticles;
}
void Swarm::update(int elapsed){
	int interval = elapsed - lastTime;
	lastTime = elapsed;
	for(int i = 0 ; i < NPARTICLES ; i++)
	{
		m_pParticles[i].update(interval);
	}
}


} /* namespace maa */
