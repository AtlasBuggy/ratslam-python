
#include "posecell_network_wrapper.h"

PosecellNetworkWrapper::PosecellNetworkWrapper(PtreeWrapper settings_wrapper)
{
    posecell_network_instance = new ratslam::PosecellNetwork(settings_wrapper.get_settings());
}

void PosecellNetworkWrapper::on_view_template(unsigned int vt, double vt_rad)
{
    posecell_network_instance->on_view_template(vt, vt_rad);
}

void PosecellNetworkWrapper::on_odo(double vtrans, double vrot, double time_diff_s)
{
    posecell_network_instance->on_odo(vtrans, vrot, time_diff_s);
}
