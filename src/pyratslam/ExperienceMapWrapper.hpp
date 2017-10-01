#include <boost/python.hpp>
#include <Ratslam.hpp>
#include <Experience_Map.h>

using namespace boost::python;
using namespace boost::property_tree;
using namespace ratslam;


/*
 * Experience_Map wrapper class
 */
class PyExperienceMap
{
public:
    PyExperienceMap(Experience_Map exp_map);
    ~PyExperienceMap();

    Experience get_experience(int id);
    object get_num_experiences();
    object get_current_id();

    void add_goal(object x_m, object y_m);
    object calculate_path_to_goal(object time_s);
    object get_goal_waypoint();
    void clear_goal_list();
    object get_current_goal_id();
    void delete_current_goal();
    object get_goal_success();
    object get_subgoal_m();
    object get_subgoal_rad();
    tuple get_goals();

private:
    Experience_Map *exp_map;
};
