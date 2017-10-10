
#include <experience_map.h>

namespace py = boost::python;

class ExperienceMapWrapper
{
public:
    ExperienceMapWrapper(PtreeWrapper settings_wrapper);

    void set_goal(double x_m, double y_m);

    void on_odo(double vtrans, double vrot, double time_diff_s);
    int on_set_experience(int new_exp_id, double rel_rad);
    int on_create_experience(unsigned int exp_id);
    bool on_create_link(int exp_id_from, int exp_id_to, double rel_rad);

    void iterate()  { experience_map_instance->iterate(); }

    int get_num_experiences()  { return experience_map_instance->get_num_experiences(); }

    double get_experience_x_m(unsigned int current_id) {
        // std::cout << "x_m: " << experience_map_instance->get_experience(current_id)->x_m << endl;
        return experience_map_instance->get_experience(current_id)->x_m;
    }
    double get_experience_y_m(unsigned int current_id) {
        return experience_map_instance->get_experience(current_id)->y_m;
    }
    double get_experience_th_rad(unsigned int current_id) {
        return experience_map_instance->get_experience(current_id)->th_rad;
    }
    unsigned int get_current_id()  { return experience_map_instance->get_current_id(); }


    int get_num_links()  { return experience_map_instance->get_num_links(); }

    unsigned int get_link_exp_from_id(unsigned int current_id) {
        return experience_map_instance->get_link(current_id)->exp_from_id;
    }
    unsigned int get_link_exp_to_id(unsigned int current_id) {
        return experience_map_instance->get_link(current_id)->exp_to_id;
    }


private:
    ratslam::ExperienceMap *experience_map_instance;
};
