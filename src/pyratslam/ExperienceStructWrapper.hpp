#include <boost/python.hpp>
#include <Ratslam.hpp>

using namespace boost::python;
using namespace boost::property_tree;
using namespace ratslam;


class PyExperience
{
public:
    PyExperience(Experience experience_struct);

    object id();
    object x_m();
    object y_m();
    object th_rad();
    object x_pc();
    object y_pc();
    object th_pc();
    tuple links_from();
    tuple links_to();

private:
    Experience *experience_struct;
};
