#pragma once
#include "shortLived.h"

using namespace std;

class Fragment : public ShortLived {
public:
	Fragment() {}
	Fragment(Position position, Velocity velocity) {}
	Fragment(Position position, Velocity velocity, float launchAngle) {}
	void draw(ogstream gout) {}
};