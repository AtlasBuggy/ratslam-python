#include "ExperienceMapWrapper.hpp"

/*
 * Experience_Map wrapper class
 */

PyExperienceMap::PyExperienceMap(Experience_Map exp_map) {
    this->exp_map = &exp_map;
}

PyExperienceMap::~PyExperienceMap() {
    delete exp_map;
}

Experience PyExperienceMap::get_experience(int id) {
    return *(exp_map->get_experience(id));
}

object PyExperienceMap::get_num_experiences() {
    return object(exp_map->get_num_experiences());
}

object PyExperienceMap::get_current_id() {
    return object(exp_map->get_current_id());
}

void PyExperienceMap::add_goal(object x_m, object y_m) {
    double prim_x_m = extract<double>(x_m);
    double prim_y_m = extract<double>(y_m);
    exp_map->add_goal(prim_x_m, prim_y_m);
}

object PyExperienceMap::calculate_path_to_goal(object time_s) {
    double prim_time_s = extract<double>(time_s);
    return object(exp_map->calculate_path_to_goal(prim_time_s));
}

object PyExperienceMap::get_goal_waypoint() {
    return object(exp_map->get_goal_waypoint());
}

void PyExperienceMap::clear_goal_list() {
    exp_map->clear_goal_list();
}

object PyExperienceMap::get_current_goal_id() {
    return object(exp_map->get_current_goal_id());
}

void PyExperienceMap::delete_current_goal() {
    exp_map->delete_current_goal();
}

object PyExperienceMap::get_goal_success() {
    return object(exp_map->get_goal_success());
}

object PyExperienceMap::get_subgoal_m() {
    return object(exp_map->get_subgoal_m());
}

object PyExperienceMap::get_subgoal_rad() {
    return object(exp_map->get_subgoal_rad());
}

tuple PyExperienceMap::get_goals() {
    return tuple(exp_map->get_goals());
}
