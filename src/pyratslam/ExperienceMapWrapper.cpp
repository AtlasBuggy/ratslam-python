#include "ExperienceMapWrapper.hpp"

/*
 * Experience_Map wrapper class
 */

 PyExperienceMap::PyExperienceMap() {

 }

PyExperienceMap::PyExperienceMap(Experience_Map exp_map) {
    this->exp_map = &exp_map;
}

PyExperienceMap::~PyExperienceMap() {
    // delete exp_map;
}

PyExperience PyExperienceMap::get_experience(int id) {
    std::cout << exp_map->get_num_experiences() << std::endl;
    PyExperience exp(*(exp_map->get_experience(id)));
    return exp;
    // std::cout << "something" << std::endl;
    // std::cout << exp_map->get_goals().size() << std::endl;
    // return object();
    // if (exp_map->get_goals().size() > 0) {
    //     return object(*(exp_map->get_experience(id)));
    // }
    // else {
    //     return object();
    // }
}

object PyExperienceMap::get_num_experiences() {
    return object(exp_map->get_num_experiences());
}
