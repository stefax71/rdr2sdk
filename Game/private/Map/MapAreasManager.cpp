#include "../../public/Map/MapArea.h"
#include "../../public/Map/MapAreasManager.h"
#include "../../public/Math/MathUtils.h"

MapAreasManager::MapAreasManager()
{
    cache[ETownName::BLACKWATER] = createBlackwater();
    cache[ETownName::RHODES] = createRhodes();
    cache[ETownName::VALENTINE] = createValentine();
    cache[ETownName::STRAWBERRY] = createStrawberry();
    cache[ETownName::TUMBLEWEED] = createTumbleweed();
    cache[ETownName::ARMADILLO] = createArmadillo();
    cache[ETownName::ST_DENIS] = createSaintDenis();
}


MapArea* MapAreasManager::get_map_area(ETownName area)
{
    if (cache.find(area) == cache.end())
    {
        return NULL;
    }
    return cache.find(area)->second;
}

vector<MapArea*> MapAreasManager::get_map_areas()
{
    vector<MapArea*> results;
    map<ETownName, MapArea*>::iterator it;
    for (it = cache.begin(); it != cache.end(); it++)
    {
        results.push_back((*it).second);
    }

    return results;
}

Hash MapAreasManager::get_map_zone_at_pos(Vector3 position)
{
    return get_map_zone_at_pos(position, EZoneType::TOWN);
}

Hash MapAreasManager::get_map_zone_at_pos(Vector3 position, EZoneType zoneType)
{
    return get_map_zone_at_pos(position.x, position.y, position.z, zoneType);
}

Hash MapAreasManager::get_map_zone_at_pos(float x, float y, float z)
{
    return get_map_zone_at_pos(x, y, z, EZoneType::TOWN);
}

Hash MapAreasManager::get_map_zone_at_pos(float x, float y, float z, EZoneType zoneType)
{
    int zoneTypeInt = static_cast<int>(zoneType);
    return ZONE::_GET_MAP_ZONE_AT_COORDS(x, y, z, zoneTypeInt);
}

MapArea* MapAreasManager::createBlackwater()
{
    Vector3 policeDeptCoords;
    policeDeptCoords.x = -756.347f;
    policeDeptCoords.y = -1269.24f;
    policeDeptCoords.z = 43.0285f;

    Vector3 moneyCoords = toVector3(-762.495f, -1267.61f, 43.8441f);

    Vector3 cellCoords = toVector3(-762.69f, -1263.44f, 43.0245f);

    Vector3 posterCoords;
    posterCoords.x = -756.9555f;
    posterCoords.y = -1270.587f;
    posterCoords.z = 44.17991f;
    long long cellnumber = 2167775834;

    return new MapArea("Blackwater", EZoneName::LOWER_WEST_ELIZABETH, ETownName::BLACKWATER, policeDeptCoords,
                       posterCoords, moneyCoords, cellCoords, cellnumber, 90.4f);
}

MapArea* MapAreasManager::createRhodes()
{
    Vector3 policeDeptCoords = toVector3(1358.17f, -1308.19f, 76.7296f);
    Vector3 cellCoords = toVector3(1356.16f, -1301.41f, 76.7606f);
    Vector3 posterCoords = toVector3(1234.58f, -1293.13f, 77.2681f);
    Vector3 moneyCoords = toVector3(1361.9f, -1304.21f, 77.5413f);
    long long cellnumber = 1878514758;

    return new MapArea("Rhodes", EZoneName::LEMOYNE, ETownName::RHODES, policeDeptCoords, posterCoords, moneyCoords,
                       cellCoords, cellnumber, 136);
}

MapArea* MapAreasManager::createValentine()
{
    Vector3 policeDeptCoords = toVector3(-275.256f, 801.303f, 118.397f);
    Vector3 cellCoords = toVector3(-272.71f, 809.093f, 118.371f);
    Vector3 posterCoords = toVector3(-272.777f, 799.70f, 119.412f);
    Vector3 moneyCoords = toVector3(-277.1f, 805.486f, 119.17f);
    long long cellnumber = 535323366;

    return new MapArea("Valentine", EZoneName::NEW_HANOVER, ETownName::VALENTINE, policeDeptCoords, posterCoords,
                       moneyCoords, cellCoords, cellnumber, 11);
}

MapArea* MapAreasManager::createStrawberry()
{
    Vector3 policeDeptCoords = toVector3(-1804.106f, -352.3542f, 164.1339f);
    Vector3 cellCoords = toVector3(-1813.23f, -355.196f, 160.43f);
    Vector3 posterCoords = toVector3(-1805.729f, -348.1523f, 164.342f);
    Vector3 moneyCoords = toVector3(-1807.99f, -348.587f, 164.448f);
    long long cellnumber = 902070893;

    return new MapArea("Strawberry", EZoneName::UPPER_WEST_ELIZABETH, ETownName::STRAWBERRY, policeDeptCoords,
                       posterCoords, moneyCoords, cellCoords, cellnumber, 66.03f);
}

MapArea* MapAreasManager::createTumbleweed()
{
    Vector3 policeDeptCoords = toVector3(-5527.188f, -2927.814f, -1.360926f);
    Vector3 cellCoords = toVector3(-5531.63f, -2919.28f, -2.36093f);
    Vector3 posterCoords = toVector3(-5531.614f, -2934.285f, -1.772461f);
    Vector3 moneyCoords = toVector3(-5530.2f, -2929.55f, -1.57704f);
    long long cellnumber = 2984805596;

    return new MapArea("Tumbleweed", EZoneName::AMBARINO, ETownName::TUMBLEWEED, policeDeptCoords, posterCoords,
                       moneyCoords, cellCoords, cellnumber, 82.30f);
}

MapArea* MapAreasManager::createArmadillo()
{
    Vector3 policeDeptCoords = toVector3(-3619.911f, -2605.103f, -13.33457f);
    Vector3 cellCoords = toVector3(-3617.92f, -2604.87f, -14.3378f);
    Vector3 posterCoords = toVector3(-3625.664f, -2603.477f, -13.42546f);
    Vector3 moneyCoords = toVector3(-3623.91f, -2602.77f, -13.5533f);
    long long cellnumber = 4235597664;

    return new MapArea("Armadillo", EZoneName::AMBARINO, ETownName::ARMADILLO, policeDeptCoords, posterCoords,
                       moneyCoords, cellCoords, cellnumber, 293.79f);
}

MapArea* MapAreasManager::createSaintDenis()
{
    Vector3 policeDeptCoords = toVector3(2502.79f, -1308.546f, 47.95366f);
    Vector3 cellCoords = toVector3(2503.68f, -1307.05f, 47.9537f);
    Vector3 posterCoords = toVector3(2516.739f, -1305.577f, 49.26161f);
    Vector3 moneyCoords = toVector3(2507.4f, -1309.02f, 48.7525f);
    long long cellnumber = 1711767580;

    return new MapArea("SaintDenis", EZoneName::LEMOYNE, ETownName::ST_DENIS, policeDeptCoords, posterCoords,
                       moneyCoords, cellCoords, cellnumber, 91.36f);
}
