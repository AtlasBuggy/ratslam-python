
#include "RatslamWrapper.hpp"

PyRatslam::PyRatslam(std::string config_path) {
    ptree _settings;
	read_ini(config_path, _settings);

    ptree ratslam_settings;
	gri::get_setting_child(ratslam_settings, _settings, "ratslam");
	rat_slam_instance = new Ratslam(ratslam_settings);

    settings = &_settings;
}

void PyRatslam::set_view_rgb(object view_rgb) {
    PyObject* pview_rgb = view_rgb.ptr();
    Py_buffer pybuf;
    if (PyObject_GetBuffer(pview_rgb, &pybuf, PyBUF_SIMPLE) != -1)
    {
        void *buf = pybuf.buf;
        const unsigned char *p = (unsigned char *)buf;
        PyBuffer_Release(&pybuf);

        rat_slam_instance->set_view_rgb(p);
    }
}
void PyRatslam::set_odom(object vtrans, object vrot)
{
    double primitive_vtrans = extract<double>(vtrans);
    double primitive_vrot = extract<double>(vrot);

    rat_slam_instance->set_odom(primitive_vtrans, primitive_vrot);
}
void PyRatslam::set_delta_time(object delta_time_s)
{
    double primitive_dt = extract<double>(delta_time_s);

    rat_slam_instance->set_delta_time(primitive_dt);
}
void PyRatslam::process()
{
    rat_slam_instance->process();
}

PyExperienceMap PyRatslam::get_experience_map()
{
    Experience_Map instance_exp_map = *(rat_slam_instance->get_experience_map());
    PyExperienceMap rat_exp_map(instance_exp_map);
    return rat_exp_map;
}

PyRatslam::~PyRatslam()
{
    delete rat_slam_instance;
}
