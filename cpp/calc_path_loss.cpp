#include<pybind11/pybind11.h>

float calc_path_loss(float x1, float y1, float x2, float y2)
{
    return x1+x2+y1+y2;
}

PYBIND11_MODULE(_calc_path_loss, m)
{
    m.def("calc_path_loss", &calc_path_loss, "Calculate the path loss.");
} 