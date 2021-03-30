I decided to use unordered map as a datastructure for storing my place and area structs. I chose unordered map because I didn't see any value in keeping the map in order and adding new elements would be fast. 

In all_places I decided to create a vector because the return value was to be a vector. Then I simply went through my unordered map and added all ids to the vector.

In add_place I check if my datastructure already contains the id. If not I create a new struct and add it to the datastructure.

In get_place_name_type I again check if my datastructure already contains the id. If it does I simply return a pair with the asked values.

In get_place_coord I once again check if my datastructure already contains the id. If it does I return the asked coordinates.

In add_area I check if my unordered map contains the area id. If it doesn't, I create a new area with my struct and add it to the datastructure.

In get_area_name I check if the area id is in the datastructure. If found, I return the coordinates of the area.

I use a lot of std::find in these previous functions because its complexity is constant when searching through an unordered map.

In places_alphabetically I create a vector of pairs and push pairs made from the unordered map into it. Then I sort it with std::sort using a lambda function to determine the order.
Then I create a new vector and push the ids from the first vector into it. Vector is used again because it is the function's desired return value.

places_coord_order is done in almost similiar fashion. The only difference really is different lambda function.

find_places_name again uses a vector because it is the return value. It also uses a for-loop for going through the unordered map. This sadly makes many of my functions linear by their complexity, but I didn't find any other way to implement the functions

find_places_type is almost the same as the previous function.

change_place_name and change_place_coord simply use the std::find again.

all_areas simply creates a vector and goes through the unordered map.

add_subarea_to_area Checks if the ids exist and if the subarea already has a parent area. If everything is ok, it adds the subarea to the parentareas subarea vector and the parentarea to the subarea. 

subarea_in_areas is like any other of these, but it uses a recursive function to go through all possible parentareas.

places_closest_to is a bit longer and performs some checks in the beginning to adjust the return values based on the parameters. Then it uses a lambda fuction in a std::sort to sort a vector of pairs.
After this it uses maybe a bit dumb method to return 3 values at most.

remove_place is a simple fuction that uses std::find again.

all_subareas_in_area is like subarea_in_areas but the recursive function goes through a vector.

common_area_of_subareas if a bit heavier function given its nested for loops. This sadly makes the complexity n^2.