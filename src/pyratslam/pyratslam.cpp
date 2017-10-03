#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

// ratslam headers
#include <Ratslam.hpp>
#include <gri_util.h>

// boost property trees
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

// Boost wrappers
// #include "ExperienceMapWrapper.hpp"
// #include "RatslamWrapper.hpp"
// #include "ExperienceStructWrapper.hpp"

typedef std::vector<unsigned int> IntVector;

#include "PyExperience.cpp"
#include "RatslamWrapper.cpp"

using namespace boost::python;
using namespace boost::property_tree;
using namespace ratslam;



BOOST_PYTHON_MODULE(pyratslam)
{
    class_<IntVector>("IntVector")
        .def(vector_indexing_suite<IntVector>() );

    class_<PyRatslam>("Ratslam", init<std::string>())
        .def("set_view_rgb", &PyRatslam::set_view_rgb)
        .def("set_odom", &PyRatslam::set_odom)
        .def("set_delta_time", &PyRatslam::set_delta_time)
        .def("process", &PyRatslam::process)

        .def("get_experience", &PyRatslam::get_experience)
        .def("get_num_experiences", &PyRatslam::get_num_experiences)
        .def("get_current_id", &PyRatslam::get_current_id)

        .def("add_goal", &PyRatslam::add_goal)
        .def("calculate_path_to_goal", &PyRatslam::calculate_path_to_goal)
        .def("get_goal_waypoint", &PyRatslam::get_goal_waypoint)
        .def("clear_goal_list", &PyRatslam::clear_goal_list)
        .def("get_current_goal_id", &PyRatslam::get_current_goal_id)
        .def("delete_current_goal", &PyRatslam::delete_current_goal)
        .def("get_goal_success", &PyRatslam::get_goal_success)
        .def("get_subgoal_m", &PyRatslam::get_subgoal_m)
        .def("get_subgoal_rad", &PyRatslam::get_subgoal_rad)
    ;

    class_<Experience>("ExperienceStruct");  // the Ratslam Experience struct
    class_<PyExperience>("Experience", init<Experience>())   // my struct wrapper
        .def("id", &PyExperience::id)

        .def("x_m", &PyExperience::x_m)
        .def("y_m", &PyExperience::y_m)
        .def("th_rad", &PyExperience::th_rad)

        .def("x_pc", &PyExperience::x_pc)
        .def("y_pc", &PyExperience::y_pc)
        .def("th_pc", &PyExperience::th_pc)

        .def("links_from", &PyExperience::links_from)
        .def("links_to", &PyExperience::links_to)
    ;
}
