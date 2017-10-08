
#include "experience_map_wrapper.h"

ExperienceMapWrapper::ExperienceMapWrapper(PtreeWrapper settings_wrapper) {
    experience_map_instance = new ratslam::ExperienceMap(settings_wrapper.get_settings());
}

void ExperienceMapWrapper::on_odo(double vtrans, double vrot, double time_diff_s)  {
    experience_map_instance->on_odo(vtrans, vrot, time_diff_s);
}

int ExperienceMapWrapper::on_set_experience(int new_exp_id, double rel_rad) {
    return experience_map_instance->on_set_experience(new_exp_id, rel_rad);
}

int ExperienceMapWrapper::on_create_experience(unsigned int exp_id) {
    return experience_map_instance->on_create_experience(exp_id);
}


bool ExperienceMapWrapper::on_create_link(int exp_id_from, int exp_id_to, double rel_rad) {
    return experience_map_instance->on_create_link(exp_id_from, exp_id_to, rel_rad);
}

void ExperienceMapWrapper::set_goal(double x_m, double y_m) {
    experience_map_instance->add_goal(x_m, y_m);
}
