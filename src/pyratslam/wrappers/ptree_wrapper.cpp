#include "ptree_wrapper.h"

#define APPLY_PYTHON_TYPE(type) \
    type retrieved_value; \
    type default_value_prim = py::extract<type>(default_value); \
    ratslam::get_setting_from_ptree(retrieved_value, this->settings, name, default_value_prim); \
    return_value = py::object(retrieved_value) \


PtreeWrapper::PtreeWrapper()
{

}

PtreeWrapper::PtreeWrapper(std::string file_path)
{
    read_ini(file_path, settings);
}

PtreeWrapper PtreeWrapper::get_child(std::string name)
{
    PtreeWrapper ptree_wrapper;
    ptree_wrapper.settings = this->settings.get_child(name);

    return ptree_wrapper;
}

py::object PtreeWrapper::get(std::string name, py::object default_value)
{
    py::extract<int> int_checker(default_value);
    py::extract<double> double_checker(default_value);
    py::extract<std::string> string_checker(default_value);

    py::object return_value;
    if (int_checker.check()) {
        APPLY_PYTHON_TYPE(int);
    }
    else if (double_checker.check()) {
        APPLY_PYTHON_TYPE(double);
    }
    else if (string_checker.check()) {
        APPLY_PYTHON_TYPE(std::string);
    }
    else {
        PyErr_SetString(PyExc_ValueError, "Couldn't find a matching type!!");
    }

    return return_value;
}

boost::property_tree::ptree PtreeWrapper::get_settings()
{
    return this->settings;
}
