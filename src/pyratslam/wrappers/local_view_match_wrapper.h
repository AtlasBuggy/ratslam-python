
#include <local_view_match.h>

namespace py = boost::python;

class LocalViewMatchWrapper
{
public:
    LocalViewMatchWrapper(PtreeWrapper settings);

    void on_image(py::object view_rgb, py::object greyscale, py::object image_width, py::object image_height);
    int get_current_vt() { return this->local_view_match_instance->get_current_vt(); }

    double get_relative_rad() { return this->local_view_match_instance->get_relative_rad(); }

private:
    ratslam::LocalViewMatch *local_view_match_instance;
};
