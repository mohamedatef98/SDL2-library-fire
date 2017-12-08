/*
 * Particle.h
 *
 *  Created on: Jul 15, 2017
 *      Author: m7med
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <stdlib.h>
#include <cmath>
#include "Screen.h"

namespace maa {

class Particle {
private:
	double m_direction;
	double m_speed;
	void init();
public:
	double m_x;
	double m_y;
	Particle();
	virtual ~Particle();
	void update(int interval);


};

} /* namespace maa */

#endif /* PARTICLE_H_ */
