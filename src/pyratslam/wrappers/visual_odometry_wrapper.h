
#include <visual_odometry.h>

namespace py = boost::python;

class VisualOdometryWrapper
{
public:
    VisualOdometryWrapper(PtreeWrapper settings_wrapper);

    py::tuple on_image(py::object view_rgb, py::object greyscale, py::object image_width, py::object image_height);

private:
    ratslam::VisualOdometry *visual_odometry_instance;
};
