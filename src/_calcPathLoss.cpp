#include"_PathLossStructures.hpp"
#include <pybind11/stl.h>
#include<pybind11/pybind11.h>


// PL(dB)=20×log10(f)+Nt×log10(d)+∑wLw−20
// PL是需要計算的path loss，
// f信號頻率，
// d是計算所在點與信號的距離，
// ∑wLw是點與信號間經過的所有障礙物之lossfactor總和
// Nt是空氣的衰減係數，

double Room::computePathLoss(const Point& point) const
{
    double frequency = m_signal.getFrequency();
    double dist = calcDistance(m_signal.getPoint(), point);
    // double loss = 20 * log10(frequency) + m_air_attenuation_coefficient * log10(distance) - 20;
    double loss = 0.0;
    for (const auto& wall : m_walls)
    {
        if(false)
            loss += wall.getLossFactor();
    }
    for (const auto& pillar : m_pillars)
    {
        if(false)
            loss += pillar.getLossFactor();
    }
    double m_air_attenuation_coefficient = 0.1;

    loss += 20 * log10(frequency);
    loss += (dist > 0)? 
                m_air_attenuation_coefficient*log10(dist) : 0;
    loss -= 20;

    return loss;
}



PYBIND11_MODULE(_calcPathLoss, m)
{
    pybind11::class_<Point>(m, "Point")
        .def(pybind11::init<int, int>())
        .def("getX", &Point::getX)
        .def("getY", &Point::getY);
    m.def("calcDistance", &calcDistance, "Calculate the distance between two points.");

    pybind11::class_<Wall>(m, "Wall")
        .def(pybind11::init<Point, Point, double>())
        .def("getP1", &Wall::getP1)
        .def("getP2", &Wall::getP2)
        .def("getLossFactor", &Wall::getLossFactor);

    pybind11::class_<Pillar>(m, "Pillar")
        .def(pybind11::init<Point, double>())
        .def("getP", &Pillar::getP)
        .def("getLossFactor", &Pillar::getLossFactor);

    pybind11::class_<Signal>(m, "Signal")
        .def(pybind11::init<Point, double, double>())
        .def("getPoint", &Signal::getPoint)
        .def("getPower", &Signal::getPower)
        .def("getFrequency", &Signal::getFrequency);
    
    pybind11::class_<Room>(m, "Room")
        .def(pybind11::init())
        .def("addWall", &Room::addWall)
        .def("addPillar", &Room::addPillar)
        .def("setSignal", &Room::setSignal)
        .def("setAirLossFactors", &Room::setAirLossFactors)
        .def("getWalls", &Room::getWalls)
        .def("getPillars", &Room::getPillars)
        .def("getSignal", &Room::getSignal)
        .def("computePathLoss", &Room::computePathLoss);


} 