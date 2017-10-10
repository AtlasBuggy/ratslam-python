#include <visual_odometry_wrapper.h>

VisualOdometryWrapper::VisualOdometryWrapper(PtreeWrapper settings_wrapper)
{
    visual_odometry_instance = new ratslam::VisualOdometry(settings_wrapper.get_settings());
}

py::tuple VisualOdometryWrapper::on_image(py::object view_rgb, py::object greyscale, py::object image_width, py::object image_height)
{
    PyObject* pview_rgb = view_rgb.ptr();
    Py_buffer pybuf;
    if (PyObject_GetBuffer(pview_rgb, &pybuf, PyBUF_SIMPLE) != -1)
    {
        void *buf = pybuf.buf;
        const unsigned char *char_buffer = (unsigned char *)buf;
        PyBuffer_Release(&pybuf);

        unsigned int image_width_prim = py::extract<unsigned int>(image_width);
        unsigned int image_height_prim = py::extract<unsigned int>(image_height);
        bool greyscale_prim = (bool)(py::extract<int>(greyscale));

        double vtrans_ms = 0.0;
        double vrot_rads = 0.0;

        visual_odometry_instance->on_image(
            char_buffer, greyscale_prim, image_width_prim, image_height_prim,
            &vtrans_ms, &vrot_rads
        );

        py::list return_list;
        return_list.append(vtrans_ms);
        return_list.append(vrot_rads);

        return py::tuple(return_list);
    }
    else {
        PyErr_SetString(PyExc_ValueError, "Invalid image!! Couldn't retrieve a buffer.");
        return py::tuple();
    }
}
