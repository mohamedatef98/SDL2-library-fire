/*
 * Swam.h
 *
 *  Created on: Jul 15, 2017
 *      Author: m7med
 */

#ifndef SWARM_H_
#define SWARM_H_
#include "Particle.h"
namespace maa {

class Swarm {
private:
	  Particle *m_pParticles;
	  int lastTime;
public:
	const static int NPARTICLES = 5000;
	Swarm();
	virtual ~Swarm();
	const Particle * const getParticle() {return m_pParticles;}
	void update(int elapsed);

};

} /* namespace maa */

#endif /* SWAM_H_ */
