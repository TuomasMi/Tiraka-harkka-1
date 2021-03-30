// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Replace this comment with your implementation
}

Datastructures::~Datastructures()
{
    // Replace this comment with your implementation
}

int Datastructures::place_count()
{
    return places.size();
}

void Datastructures::clear_all()
{
    places.clear();
    areas.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{
    std::vector<PlaceID> placeIds;
    for (auto place : places)
    {
        placeIds.push_back(place.first);
    }
    return placeIds;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if (places.find(id) != places.end())
    {
        return false;
    }
    Place place = {name, type, xy};
    places.insert({id, place});
    return true;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{
    if (places.find(id) == places.end())
    {
        return {NO_NAME, PlaceType::NO_TYPE};
    }
    return {places[id].name, places[id].type};
}

Coord Datastructures::get_place_coord(PlaceID id)
{
    if (places.find(id) == places.end())
    {
        return NO_COORD;
    }
    return places[id].xy;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{
    if (areas.find(id) != areas.end()) {
        return false;
    }
    Area area = {id, name, coords, {}, nullptr};
    areas.insert({id, area});
    return true;
}

Name Datastructures::get_area_name(AreaID id)
{
    if (areas.find(id) == areas.end()) {
        return NO_NAME;
    }
    return areas[id].name;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{
    if (areas.find(id) == areas.end()) {
        return {NO_COORD};
    }
    return areas[id].coords;
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.
}


std::vector<PlaceID> Datastructures::places_alphabetically()
{
    std::vector<std::pair<PlaceID, Place>> placePairs;

    for (auto& i : places) {
        placePairs.push_back(i);
    }

    sort(placePairs.begin(), placePairs.end(), [](std::pair<PlaceID, Place>& a, std::pair<PlaceID, Place>& b){
        return a.second.name < b.second.name;
    });

    std::vector<PlaceID> placeIDs;

    for (auto place : placePairs) {
        placeIDs.push_back(place.first);
    }
    return placeIDs;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{
    std::vector<std::pair<PlaceID, Place>> placePairs;
    for (auto& i : places) {
        placePairs.push_back(i);
    }

    std::sort(placePairs.begin(), placePairs.end(), [](std::pair<PlaceID, Place>& a, std::pair<PlaceID, Place>& b){
        if (sqrt(pow(a.second.xy.x, 2) + pow(a.second.xy.y, 2)) == (sqrt(pow(b.second.xy.x, 2) + pow(b.second.xy.y, 2)))) {
            return a.second.xy.y < b.second.xy.y;
        }
        return (sqrt(pow(a.second.xy.x, 2) + pow(a.second.xy.y, 2))) < (sqrt(pow(b.second.xy.x, 2) + pow(b.second.xy.y, 2)));
    });

    std::vector<PlaceID> placeIDs;
    for (auto place : placePairs) {
        placeIDs.push_back(place.first);
    }
    return placeIDs;
}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{

    std::vector<PlaceID> namedPlaceIDs = {};
    for (auto it = places.begin(); it != places.end(); it++) {
        if (it->second.name == name) {
            namedPlaceIDs.push_back(it->first);
        }
    }
    return namedPlaceIDs;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{
    std::vector<PlaceID> typePlaceIDs = {};
    for (auto it = places.begin(); it != places.end(); it++) {
        if (it->second.type == type) {
            typePlaceIDs.push_back(it->first);
        }
    }
    return typePlaceIDs;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{
    if (places.find(id) == places.end()) {
        return false;
    }
    places[id].name = newname;
    return true;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{
    if (places.find(id) == places.end()) {
        return false;
    }
    places[id].xy = newcoord;
    return true;
}

std::vector<AreaID> Datastructures::all_areas()
{
    std::vector<AreaID> areaIDs;
    for (auto area : areas) {
        areaIDs.push_back(area.first);
    }
    return areaIDs;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{
    if (areas.find(id) == areas.end() or areas.find(parentid) == areas.end()) {
        return false;
    }
    if (areas[id].parentArea != nullptr) {
        return false;
    }

    areas[parentid].subAreas.push_back(&areas[id]);
    areas[id].parentArea = &areas[parentid];
    return true;
}
std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{
    if(areas.find(id) == areas.end()) {
        return {NO_AREA};
    }
    parentAreas.clear();
    go_through_parentareas(id);
    return parentAreas;

}

void Datastructures::go_through_parentareas(AreaID id)
{
    if (areas[id].parentArea == nullptr) {
        return;
    }
    parentAreas.push_back(areas[id].parentArea->id);
    go_through_parentareas(areas[id].parentArea->id);
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{
    std::vector<std::pair<PlaceID, Place>> placePairs;
    for (auto place : places) {
        if (type != PlaceType::NO_TYPE) {
            if (place.second.type == type) {
                placePairs.push_back(place);
            }
        }
        else {
            placePairs.push_back(place);
        }
    }

    std::sort(placePairs.begin(), placePairs.end(), [&xy](std::pair<PlaceID, Place>& a, std::pair<PlaceID, Place>& b){
        if (sqrt(pow((xy.x - a.second.xy.x), 2) + pow((xy.y - a.second.xy.y), 2)) == sqrt(pow((xy.x - b.second.xy.x), 2) + pow((xy.y - b.second.xy.y), 2))) {
            return a.second.xy.y < b.second.xy.y;
        }
        return sqrt(pow((xy.x - a.second.xy.x), 2) + pow((xy.y - a.second.xy.y), 2)) < sqrt(pow((xy.x - b.second.xy.x), 2) + pow((xy.y - b.second.xy.y), 2));
    });


    std::vector<PlaceID> placeIDs;
    if (placePairs.size() < 3) {
        for (auto place : placePairs) {
            placeIDs.push_back(place.first);
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            placeIDs.push_back(placePairs[i].first);
        }
    }
    return placeIDs;
}

bool Datastructures::remove_place(PlaceID id)
{
    if (places.find(id) == places.end()) {
        return false;
    }
    places.erase(id);
    return true;
}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{
    if (areas.find(id) == areas.end()) {
        return {NO_AREA};
    }
    subAreas.clear();
    go_through_subareas(id);
    return subAreas;
}

void Datastructures::go_through_subareas(AreaID id)
{
    for (auto& area : areas[id].subAreas) {
        subAreas.push_back(area->id);
        go_through_subareas(area->id);
    }
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{
    if (not areas.count(id1)) {
        return NO_AREA;
    }
    else if (not areas.count(id2)) {
        return NO_AREA;
    }
    std::vector<AreaID> areas1 = subarea_in_areas(id1);
    std::vector<AreaID> areas2 = subarea_in_areas(id2);
    for (unsigned int i = 0; i < areas1.size(); i++) {
        for (unsigned int j = 0; j < areas2.size(); j++) {
            if (areas1[i] == areas2[j]) {
                return areas1[i];
            }
        }
    }
    return NO_AREA;
}
