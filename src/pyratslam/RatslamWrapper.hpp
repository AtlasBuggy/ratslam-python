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
    PyExperienceMap get_experience_map();
private:
    ptree *settings;
    Ratslam *rat_slam_instance;
};
