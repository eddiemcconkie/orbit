/**************************************************
 * Authors:
 * Eddie McConkie
 * Austin Eldredge
 * Lehi Lopez
 **************************************************/

#pragma once

#include "satellite.h"
#include "entity.h"
#include "position.h"
#include "velocity.h"
#include "fragment.h"

#include <list>
#include <memory>

/**************************************************
 * HUBBLE COMPUTER
 * The computer piece of the Hubble telescope
 **************************************************/
class HubbleComputer : public Satellite
{
public:
	HubbleComputer() : Satellite() { init(); }
	HubbleComputer(const Position& position, const Velocity& velocity, double angle = 0.0) : Satellite(position, velocity, angle, true) { init(); }
	std::list<std::shared_ptr<Entity>> destroy() { return createDestroyedList<Fragment, Fragment>(); } 
	void draw(ogstream& gout) { drawHubbleComputer(position, angle); }

private:
	void init() { radius = 7.0; }
};
