
#ifndef ROOM_ENV_HPP
#define ROOM_ENV_HPP

#include <vector>
#include <utility>
#include <cmath>
class Point {
public:
    Point(int x, int y) : m_x(x), m_y(y) {}
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    // std::pair<int, int> getPair() const { return {m_x, m_y}; }
    // double operator- (Point const & p) const 
    //     { return sqrt(pow(m_x - p.m_x, 2) + pow(m_y - p.m_y, 2)); }
private:
    int m_x;
    int m_y;
};
double calcDistance(Point p1, Point p2)
{
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
};

class Wall {
public:
    Wall(const Point p1, const Point p2, double lossFactor)
        : m_p1(p1), m_p2(p2), m_lossFactor(lossFactor) {}
    Point getP1() const { return m_p1; }
    Point getP2() const { return m_p2; }
    double getLossFactor() const { return m_lossFactor; }

private:
    Point m_p1;
    Point m_p2;
    double m_lossFactor;
};

class Pillar {
public:
    Pillar(Point p, double lossFactor)
        : m_p(p), m_lossFactor(lossFactor) {}
    Point getP() const { return m_p; }
    // std::vector<std::pair<int, int>> getVertices() const {
    //     return {{m_x - 30, m_y - 30}, {m_x - 30, m_y + 30}, {m_x + 30, m_y + 30}, {m_x + 30, m_y - 30}};
    // }
    double getLossFactor() const { return m_lossFactor; }

private:
    Point m_p;
    double m_lossFactor;
};

class Signal {
public:
    Signal() {}
    Signal(Point p, double power, double frequency)
        : m_p(p), m_power(power), m_frequency(frequency) {}
    void setSignal(Point p, double power, double frequency) {
        m_p = p;
        m_power = power;
        m_frequency = frequency;
    }
    Point getPoint() const { return m_p; }
    double getPower() const { return m_power; }
    double getFrequency() const { return m_frequency; }
private:
    Point m_p = Point(0, 0);
    double m_power;
    double m_frequency;
};


class Room {
public:

    Room() {}

    void addWall(const Wall& w) {
        m_walls.emplace_back(w);
    }

    void addPillar(const Pillar& p) {
        m_pillars.emplace_back(p);
    }

    void setSignal(const Signal& s) {
        m_signal = s;
    }

    void setAirLossFactors(const std::vector<double>& airLossFactors) {
        m_air_loss_factors = airLossFactors;
    }

    const std::vector<Wall>& getWalls() const { return m_walls; }
    const std::vector<Pillar>& getPillars() const { return m_pillars; }
    const Signal& getSignal() const { return m_signal; }

    double computePathLoss(const Point& point) const;

private:
    // std::vector<Point> m_points;
    std::vector<Wall> m_walls;
    std::vector<Pillar> m_pillars;
    Signal m_signal;
    std::vector<double> m_air_loss_factors;
};


#endif 