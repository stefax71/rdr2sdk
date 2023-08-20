#include "../../public/native/types.h"
#include "../../public/Map/MapArea.h"

#include <set>



MapArea::MapArea(const char* name, EZoneName zone_name, ETownName town_name, Vector3 policeDeptCoords, Vector3 bountyPostersCoords, Vector3 moneyCoords, Vector3 cellCoords, long long cellnumber, float bountyPosterHeading)
{
	this->name = name;
	this->town_hash_ = town_name;
	this->zone_hash_ = zone_name;
	this->policeDeptCoords = new Vector3(policeDeptCoords);
	this->bountyPostersCoords = new Vector3(bountyPostersCoords);
	this->moneyCoords = new Vector3(moneyCoords);
	this->cellCoords = new Vector3(cellCoords);
	this->cellnumber = cellnumber;
}