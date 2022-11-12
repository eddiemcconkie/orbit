#pragma once

#define _USE_MATH_DEFINES

#include "position.h"
#include "earth.h"
#include "ship.h"
#include "game.h"
#include "entity.h"
#include "satellite.h"
#include "fragment.h"

#include <cmath>
#include <cassert>

/**************************************************
 * DOUBLES
 **************************************************/
class EarthDummy : public Earth
{
public:
	Acceleration calculateGravity(Entity entity) { assert(false); }
	Position getPosition() { assert(false); }
	double getRadius() { assert(false); }
	double getTimeDilation() { assert(false); }
	void draw() { assert(false); }
	void advance() { assert(false); }
};

class EntityDummy : public Entity  //this is an entity dummy that is not abstract to represent any entity properly
{
public:
	virtual void setPosition(Position pos) { assert(false); }
	virtual Position getPosition() const { assert(false); }
	virtual void setVelocity(Velocity vel) { assert(false); }
	virtual Velocity getVelocity() const { assert(false); }
	virtual double getRadius() const { assert(false); }
	virtual void advance(const Earth& earth) { assert(false); }
	virtual void kill() { assert(false); }
	virtual bool isDead() const { assert(false); }
	virtual std::list<Entity> destroy() { assert(false); }
	virtual void draw(ogstream& gout) { assert(false); }
};

class EarthSpyAdvance : public EarthDummy
{
public:
	void advance() { timesAdvanceCalled++; };
	static int timesAdvanceCalled;
};

class EntitySpyAdvance : public EntityDummy
{
public:
	void advance() { timesAdvanceCalled++; };
	static int timesAdvanceCalled;
};

//this returns the items location as the middle of the board
class StubEntityPosCenter : public EntityDummy
{
public:
	Position getPosition() { return Position(0.0, 0.0); }
};

class StubEntity_x0_y0_r10 : public EntityDummy
{
public:
	Position getPosition() const { return Position(0.0, 0.0); }
	double getRadius() const { return 10.0; }
};

class StubEntity_x10_y0_r10 : public EntityDummy
{
public:
	Position getPosition() const { return Position(10.0, 0.0); }
	double getRadius() const { return 10.0; }
};

class StubEntity_x20_y0_r10 : public EntityDummy
{
public:
	Position getPosition() const { return Position(20.0, 0.0); }
	double getRadius() const { return 10.0; }
};

class StubEntity_x50_y0_r10 : public EntityDummy
{
public:
	Position getPosition() const { return Position(50.0, 0.0); }
	double getRadius() const { return 10.0; }
};

class StubEarth_x0_y0_r10 : public EarthDummy
{
public:
	Position getPosition() { return Position(0.0, 0.0); }
	double getRadius() const { return 10.0; }
};

/**************************************************
 * TEST Game
 * Unit tests for the Game class
 **************************************************/
class TestGame
{
public:
	void run()
	{
		advance_earthMoved();
		advance_entitiesMoved();
		checkCollision_entitiesOverlapping();
		checkCollision_entitiesTouching();
		checkCollision_entitiesNotTouching();
		checkCollision_entityAndEarthOverlapping();
		checkCollision_entityAndEarthTouching();
		checkCollision_entityAndEarthNotTouching();
	}

private:
	/**************************************************
	 * ADVANCE - Check that the advance function is called once for the Earth
	 **************************************************/
	void advance_earthMoved() {
		// setup
		Game game;
		EarthSpyAdvance earthSpy;
		EarthSpyAdvance::timesAdvanceCalled = 0;
		game.earth = earthSpy;

		// exercise
		game.advance();

		// verify
		assert(EarthSpyAdvance::timesAdvanceCalled == 1);

		// teardown
	}

	/**************************************************
	 * ADVANCE - Check that the advance function is called once per Entity
	 **************************************************/
	void advance_entitiesMoved() {
		// setup
		Game game;
		EntitySpyAdvance entitySpy1;
		EntitySpyAdvance entitySpy2;
		EntitySpyAdvance::timesAdvanceCalled = 0;
		game.entities = { entitySpy1, entitySpy2 };

		//exercise
		game.advance();

		//verify
		assert(EntitySpyAdvance::timesAdvanceCalled == 2);

		//teardown
	}

	/**************************************************
	 * CHECK COLLISION (ENTITY V ENTITY) - The two are overlapping
	 **************************************************/
	void checkCollision_entitiesOverlapping() {
		//setup 
		Position::setZoom(1.0);
		Game game;

		StubEntity_x0_y0_r10 entity1;
		StubEntity_x10_y0_r10 entity2;

		//exercise
		bool collided = game.checkCollision(entity1, entity2);

		//verify
		assert(collided);

		//teardown
	}

	/**************************************************
	 * CHECK COLLISION (ENTITY V ENTITY) - The two are tocuhing, which counts as a collision
	 **************************************************/
	void checkCollision_entitiesTouching()
	{
		//setup 
		Position::setZoom(1.0);
		Game game;

		StubEntity_x0_y0_r10 entity1;
		StubEntity_x20_y0_r10 entity2;

		//exercise
		bool collided = game.checkCollision(entity1, entity2);

		//verify
		assert(collided);

		//teardown
	}

	/**************************************************
	 * CHECK COLLISION (ENTITY V ENTITY) - The two are not touching
	 **************************************************/
	void checkCollision_entitiesNotTouching()
	{
		//setup 
		Position::setZoom(1.0);
		Game game;

		StubEntity_x0_y0_r10 entity1;
		StubEntity_x50_y0_r10 entity2;

		//exercise
		bool collided = game.checkCollision(entity1, entity2);

		//verify
		assert(!collided);

		//teardown
	}
	
	/**************************************************
	 * CHECK COLLISION (ENTITY V EARTH) - The two are overlapping
	 * (For simplicity, the following tests will use an Earth with radius 10.0)
	 **************************************************/
	void checkCollision_entityAndEarthOverlapping() {
		//setup 
		Position::setZoom(1.0);
		Game game;

		StubEntity_x10_y0_r10 entity;
		StubEarth_x0_y0_r10 earth;

		//exercise
		bool collided = game.checkCollision(entity, earth);

		//verify
		assert(collided);

		//teardown
	}

	/**************************************************
	 * CHECK COLLISION (ENTITY V EARTH) - The two are touching, which counts as a collision
	 **************************************************/
	void checkCollision_entityAndEarthTouching()
	{
		//setup 
		Position::setZoom(1.0);
		Game game;

		StubEntity_x20_y0_r10 entity;
		StubEarth_x0_y0_r10 earth;

		//exercise
		bool collided = game.checkCollision(entity, earth);

		//verify
		assert(collided);

		//teardown
	}

	/**************************************************
	 * CHECK COLLISION (ENTITY V EARTH) - The two are not touching
	 **************************************************/
	void checkCollision_entityAndEarthNotTouching()
	{
		//setup 
		Position::setZoom(1.0);
		Game game;

		StubEntity_x50_y0_r10 entity;
		StubEarth_x0_y0_r10 earth;

		//exercise
		bool collided = game.checkCollision(entity, earth);

		//verify
		assert(!collided);

		//teardown
	}
};
