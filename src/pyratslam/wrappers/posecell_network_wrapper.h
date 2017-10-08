
#include <posecell_network.h>

namespace py = boost::python;

class PosecellNetworkWrapper
{
public:
    PosecellNetworkWrapper(PtreeWrapper settings_wrapper);

    void on_view_template(unsigned int vt, double vt_rad);
    void on_odo(double vtrans, double vrot, double time_diff_s);

    unsigned int get_current_exp_id()  { return posecell_network_instance->get_current_exp_id(); }
    double get_relative_rad()  { return posecell_network_instance->get_relative_rad(); }

    double x()  { return posecell_network_instance->x(); }
    double y()  { return posecell_network_instance->y(); }
    double th()  { return posecell_network_instance->th(); }

    ratslam::PosecellNetwork::PosecellAction get_action()  { return posecell_network_instance->get_action(); }

private:
    ratslam::PosecellNetwork *posecell_network_instance;
};
