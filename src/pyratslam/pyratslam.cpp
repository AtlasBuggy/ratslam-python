#include <boost/python.hpp>

// ratslam headers
#include <Ratslam.hpp>
#include <Dummy.hpp>
#include <gri_util.h>

// boost property trees
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace boost::python;
using namespace boost::property_tree;
using namespace ratslam;


void read_ini_default(const std::string &filename, ptree &pt)
{
    read_ini(filename, pt);
}

void get_setting_child_default(ptree &child, ptree &settings, std::string name)
{
    gri::get_setting_child(child, settings, name);
}

Dummy* dummy_factory(object obj)
{
    extract<int> get_int(obj);
    if (get_int.check()) {
        return new Dummy(get_int());
    }
    else {
        return new Dummy(0);
    }
}

BOOST_PYTHON_MODULE(pyratslam)
{
    // class_<Dummy, boost::noncopyable>("Dummy", init<Int>());
    // def("make_dummy", dummy_factory);
    class_<Ratslam, boost::noncopyable>("Ratslam", init<ptree>())
        .def("set_view_rgb", &Ratslam::set_view_rgb)
        .def("set_odom", &Ratslam::set_odom)
        .def("set_delta_time", &Ratslam::set_delta_time)
        .def("process", &Ratslam::process)
    ;

    class_<ptree>("ptree");
    def("read_ini", read_ini_default);
    def("get_setting_child", get_setting_child_default);
}
