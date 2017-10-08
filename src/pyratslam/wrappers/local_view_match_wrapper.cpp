
#include "local_view_match_wrapper.h"

LocalViewMatchWrapper::LocalViewMatchWrapper(PtreeWrapper settings_wrapper)
{
    local_view_match_instance = new ratslam::LocalViewMatch(settings_wrapper.get_settings());
}

void LocalViewMatchWrapper::on_image(py::object view_rgb, py::object greyscale, py::object image_width, py::object image_height)
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

        local_view_match_instance->on_image(char_buffer, greyscale_prim, image_width_prim, image_height_prim);
    }
    else {
        PyErr_SetString(PyExc_ValueError, "Invalid image!! Couldn't retrieve a buffer.");
    }
}
