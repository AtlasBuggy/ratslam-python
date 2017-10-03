#include <boost/python.hpp>
#include <Ratslam.hpp>

using namespace boost::python;
using namespace boost::property_tree;
using namespace ratslam;

/*
 * Ratslam wrapper class
 */
class PyRatslam
{
public:
    PyRatslam(std::string config_path);
    ~PyRatslam();

    void set_view_rgb(object view_rgb);
    void set_odom(object vtrans, object vrot);
    void set_delta_time(object delta_time_s);
    void process();

    object get_num_experiences();
    PyExperience get_experience(object id);
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
private:
    ptree *settings;
    Ratslam *rat_slam_instance;
};
