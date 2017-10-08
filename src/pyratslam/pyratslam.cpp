#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "ptree_wrapper.cpp"
#include "local_view_match_wrapper.cpp"
#include "visual_odometry_wrapper.cpp"
#include "posecell_network_wrapper.cpp"
#include "experience_map_wrapper.cpp"

#include <posecell_network.h>

namespace py = boost::python;
using namespace ratslam;

void ptree_bad_path_translator(const boost::property_tree::ptree_bad_path& exception) {
    PyErr_SetString(PyExc_UserWarning, exception.what());
}


BOOST_PYTHON_MODULE(pyratslam)
{
    py::register_exception_translator<boost::property_tree::ptree_bad_path>(&ptree_bad_path_translator);

    py::class_<PtreeWrapper>("Ptree", py::init<std::string>())
        .def("get_child", &PtreeWrapper::get_child)
        .def("get", &PtreeWrapper::get)
    ;

    py::class_<LocalViewMatchWrapper>("LocalViewMatch", py::init<PtreeWrapper>())
        .def("on_image", &LocalViewMatchWrapper::on_image)
        .def("get_current_vt", &LocalViewMatchWrapper::get_current_vt)
        .def("get_relative_rad", &LocalViewMatchWrapper::get_relative_rad)
    ;

    py::class_<VisualOdometryWrapper>("VisualOdometry", py::init<PtreeWrapper>())
        .def("on_image", &VisualOdometryWrapper::on_image)
    ;

    py::class_<PosecellNetworkWrapper>("PosecellNetwork", py::init<PtreeWrapper>())
        .def("on_view_template", &PosecellNetworkWrapper::on_view_template)
        .def("on_odo", &PosecellNetworkWrapper::on_odo)
        .def("get_current_exp_id", &PosecellNetworkWrapper::get_current_exp_id)
        .def("get_relative_rad", &PosecellNetworkWrapper::get_relative_rad)
        .def("x", &PosecellNetworkWrapper::x)
        .def("y", &PosecellNetworkWrapper::y)
        .def("th", &PosecellNetworkWrapper::th)
        .def("get_action", &PosecellNetworkWrapper::get_action)
    ;

    py::enum_<PosecellNetwork::PosecellAction>("PosecellAction")
        .value("NO_ACTION", PosecellNetwork::NO_ACTION)
        .value("CREATE_NODE", PosecellNetwork::CREATE_NODE)
        .value("CREATE_EDGE", PosecellNetwork::CREATE_EDGE)
        .value("SET_NODE", PosecellNetwork::SET_NODE)
    ;

    py::class_<ExperienceMapWrapper>("ExperienceMap", py::init<PtreeWrapper>())
        .def("set_goal", &ExperienceMapWrapper::set_goal)
        .def("on_odo", &ExperienceMapWrapper::on_odo)
        .def("on_set_experience", &ExperienceMapWrapper::on_set_experience)
        .def("on_create_experience", &ExperienceMapWrapper::on_create_experience)
        .def("on_create_link", &ExperienceMapWrapper::on_create_link)
        .def("iterate", &ExperienceMapWrapper::iterate)
        .def("get_experience_x_m", &ExperienceMapWrapper::get_experience_x_m)
        .def("get_experience_y_m", &ExperienceMapWrapper::get_experience_y_m)
        .def("get_experience_th_rad", &ExperienceMapWrapper::get_experience_th_rad)
        .def("get_current_id", &ExperienceMapWrapper::get_current_id)
        .def("get_num_experiences", &ExperienceMapWrapper::get_num_experiences)
    ;
}
