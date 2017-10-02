
#include "RatslamWrapper.hpp"

#define EXP_MAP rat_slam_instance->get_experience_map()

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

        std::cout << p << std::endl;
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

PyExperience PyRatslam::get_experience(int id)
{
    PyExperience exp(*(EXP_MAP->get_experience(id)));
    return exp;
}

object PyRatslam::get_num_experiences()
{
    return object(EXP_MAP->get_num_experiences());
}

object PyRatslam::get_current_id() {
    return object(EXP_MAP->get_current_id());
}

void PyRatslam::add_goal(object x_m, object y_m) {
    double prim_x_m = extract<double>(x_m);
    double prim_y_m = extract<double>(y_m);
    EXP_MAP->add_goal(prim_x_m, prim_y_m);
}

object PyRatslam::calculate_path_to_goal(object time_s) {
    double prim_time_s = extract<double>(time_s);
    return object(EXP_MAP->calculate_path_to_goal(prim_time_s));
}

object PyRatslam::get_goal_waypoint() {
    return object(EXP_MAP->get_goal_waypoint());
}

void PyRatslam::clear_goal_list() {
    EXP_MAP->clear_goal_list();
}

object PyRatslam::get_current_goal_id() {
    std::cout << EXP_MAP->get_current_goal_id() << std::endl;
    return object(EXP_MAP->get_current_goal_id());
}

void PyRatslam::delete_current_goal() {
    EXP_MAP->delete_current_goal();
}

object PyRatslam::get_goal_success() {
    return object(EXP_MAP->get_goal_success());
}

object PyRatslam::get_subgoal_m() {
    return object(EXP_MAP->get_subgoal_m());
}

object PyRatslam::get_subgoal_rad() {
    return object(EXP_MAP->get_subgoal_rad());
}


PyRatslam::~PyRatslam()
{

}
