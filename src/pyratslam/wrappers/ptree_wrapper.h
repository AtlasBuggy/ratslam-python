#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <utils.h>

namespace py = boost::python;

class PtreeWrapper
{
public:
    PtreeWrapper();
    PtreeWrapper(std::string file_path);

    PtreeWrapper get_child(std::string name);
    py::object get(std::string name, py::object default_value);

    boost::property_tree::ptree get_settings();
private:
    boost::property_tree::ptree settings;

};
