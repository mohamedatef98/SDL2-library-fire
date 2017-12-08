/*
 * Particle.cpp
 *
 *  Created on: Jul 15, 2017
 *      Author: m7med
 */

#include "Particle.h"


namespace maa {

Particle::Particle() {
	init();



}

Particle::~Particle() {}

void Particle::init()
{
	m_x =  0;
	m_y =  0;
	m_direction = (2.0 * M_PI * rand())/RAND_MAX;
	m_speed = (0.04 * rand())/RAND_MAX;

	m_speed *= m_speed;

}

void Particle::update(int interval)
{
	m_direction += interval * 0.0002;
	double xspeed = (((double) Screen::SCREEN_HEIGHT)/Screen::SCREEN_WIDTH)*m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);
	m_x += interval * xspeed;
	m_y += interval * yspeed;
	if(m_x > 1 || m_x < -1 || m_y > 1 || m_y < -1)
		init();


}

} /* namespace maa */
