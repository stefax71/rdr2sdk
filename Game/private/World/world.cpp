#include "../../public/World/world.h"
#define _USE_MATH_DEFINES

#include <random>
#include <cmath>

#include "../../public/native/types.h"
#include "..\..\public\Math\MathUtils.h"
	
	


void getGroundPos(Vector3 originalPos, Vector3* outPos)
{
	float groundZ;
	MISC::GET_GROUND_Z_FOR_3D_COORD(originalPos.x, originalPos.y, originalPos.z, &groundZ, false);

	outPos->x = originalPos.x;
	outPos->y = originalPos.y;
	outPos->z = groundZ;
}

void getGroundPos(Vector3* originalPos)
{
	getGroundPos(*originalPos, originalPos);
}

Vector3 getRandomPositionInRange(Vector3 center, int radius)
{
	int x = rndInt((int)center.x - radius, (int)center.x + radius + 1);
	int topOrBottom = rndInt(0, 2) == 1 ? 1 : -1;
	double y = topOrBottom * sqrt(pow(radius, 2) - pow(x - center.x, 2)) + center.y;
	
	Vector3 output;
	output.x = x;
	output.y = (float)y;
	output.z = getGroundPos(output);
	return output;
}

Vector3 getRandomPedPositionInRange(Vector3 source, int radius)
{
	Vector3 position = getRandomPositionInRange(source, radius);
	PATHFIND::GET_SAFE_COORD_FOR_PED(position.x, position.y, position.z, true, &position, 16);
	return position;
}

float getGroundPos(Vector3 originalPos)
{
	float groundZ;
	MISC::GET_GROUND_Z_FOR_3D_COORD(originalPos.x, originalPos.y, originalPos.z + 30, &groundZ, false);
	return groundZ;
}

float distanceBetweenEntities(Entity entity1, Entity entity2)
{
	Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, 1, 0);
	Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, 1, 0);

	return MISC::GET_DISTANCE_BETWEEN_COORDS(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, 1);
}

float distanceBetweenEntitiesHor(Entity entity1, Entity entity2)
{
	Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, 1, 0);
	Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, 1, 0);

	return MISC::GET_DISTANCE_BETWEEN_COORDS(pos1.x, pos1.y, 0, pos2.x, pos2.y, 0, 1);
}

Object createProp(char* model, Vector3 position, float heading, bool isStatic, bool isVisible)
{
	Hash modelHash = MISC::GET_HASH_KEY(model);

	if (!STREAMING::HAS_MODEL_LOADED(modelHash))
	{
		STREAMING::REQUEST_MODEL(modelHash, false);
	}

	while (!STREAMING::HAS_MODEL_LOADED(modelHash))
	{
		WAIT(0);
	}

	Object prop = OBJECT::CREATE_OBJECT(modelHash, position.x, position.y, position.z, false, false, !isStatic, 0, 0);
	ENTITY::SET_ENTITY_HEADING(prop, heading);
	ENTITY::FREEZE_ENTITY_POSITION(prop, isStatic);
	ENTITY::SET_ENTITY_VISIBLE(prop, isVisible);

	return prop;
}


tm getGameTime()
{
	tm gameTime;
	gameTime.tm_year = 70; // make problems only with years aroud 1970, not 1900.
	gameTime.tm_mon = CLOCK::GET_CLOCK_MONTH();
	gameTime.tm_mday = CLOCK::GET_CLOCK_DAY_OF_MONTH();
	gameTime.tm_wday = CLOCK::GET_CLOCK_DAY_OF_WEEK();
	gameTime.tm_hour = CLOCK::GET_CLOCK_HOURS();
	gameTime.tm_min = CLOCK::GET_CLOCK_MINUTES();
	gameTime.tm_sec = CLOCK::GET_CLOCK_SECONDS();

	return gameTime;
}

float random_angle()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> dis(0.0, 2.0 * 3.14159265358979323846);
	return static_cast<float>(dis(gen));
}

Vector3 random_position_around(const Vector3& center, float distance, bool safe_coords)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dis(0.0, 2.0 * M_PI);

	float angle = dis(gen);
	
	Vector3 position;
	
	position.x = center.x + (distance + 1) *  std::cos(angle);
	position.y = center.y + (distance + 1) * std::sin(angle);
	position.z = center.z;
	
	if (safe_coords)
	{
		PATHFIND::GET_SAFE_COORD_FOR_PED(position.x, position.y, position.z, true, &position, 16);
	}
	return position;
}