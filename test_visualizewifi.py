import pytest
from math import sqrt
import _calcPathLoss as cpl

def set_room():

    room = cpl.Room()

    s_p = cpl.Point(2,2)
    s = cpl.Signal(s_p, 15, 100000)
    room.setSignal(s)
    
    a1 = cpl.Point(1,2)
    b1 = cpl.Point(3,4)
    w1 = cpl.Wall(a1, b1, 0.05)
    a2 = cpl.Point(2,3)
    b2 = cpl.Point(4,5)
    w2 = cpl.Wall(a2, b2, 0.1)
    room.addWall(w1)
    room.addWall(w2)


    c1 = cpl.Point(2,3)
    p1 = cpl.Pillar(c1, 0.1)
    c2 = cpl.Point(3,4)
    p2 = cpl.Pillar(c2, 0.2)
    room.addPillar(p1)
    room.addPillar(p2)

    return room


def test_point():
    a = cpl.Point(1,2)
    assert a.getX() == 1
    assert a.getY() == 2
    b = cpl.Point(3,4)
    assert abs(cpl.calcDistance(a, b) - sqrt(8)) < 1e-9

def test_wall():
    a = cpl.Point(1,2)
    b = cpl.Point(3,4)
    w = cpl.Wall(a, b, 0.05)
    assert w.getP1().getX() == 1
    assert w.getP1().getY() == 2
    assert w.getP2().getX() == 3
    assert w.getP2().getY() == 4
    assert w.getLossFactor() == 0.05

def test_pillar():
    a = cpl.Point(2,3)
    p = cpl.Pillar(a, 0.1)
    assert p.getP().getX() == 2
    assert p.getP().getY() == 3
    assert p.getLossFactor() == 0.1

def test_signal():
    a = cpl.Point(2,2)
    s = cpl.Signal(a, 15, 100000)
    assert s.getPoint().getX() == 2
    assert s.getPoint().getY() == 2
    assert s.getPower() == 15
    assert s.getFrequency() == 100000

def test_room():
    a = cpl.Point(1,2)
    b = cpl.Point(3,4)
    w = cpl.Wall(a, b, 0.05)
    c = cpl.Point(2,3)
    p = cpl.Pillar(c, 0.1)
    room = cpl.Room()
    room.addWall(w)
    room.addPillar(p)
    assert room.getWalls()[0].getP1().getX() == 1
    assert room.getWalls()[0].getP1().getY() == 2
    assert room.getWalls()[0].getP2().getX() == 3
    assert room.getWalls()[0].getP2().getY() == 4
    assert room.getWalls()[0].getLossFactor() == 0.05
    assert room.getPillars()[0].getP().getX() == 2
    assert room.getPillars()[0].getP().getY() == 3
    assert room.getPillars()[0].getLossFactor() == 0.1
    s_p = cpl.Point(2,2)
    s = cpl.Signal(s_p, 15, 100000)
    room.setSignal(s)
    assert room.getSignal().getPoint().getX() == 2
    assert room.getSignal().getPoint().getY() == 2
    assert room.getSignal().getPower() == 15
    assert room.getSignal().getFrequency() == 100000
    assert len(room.getWalls()) == 1
    assert len(room.getPillars()) == 1
    s2_p = cpl.Point(2,3)
    s2 = cpl.Signal(s2_p, 20, 200000)
    room.setSignal(s2)
    assert room.getSignal().getPoint().getX() == 2
    assert room.getSignal().getPoint().getY() == 3
    assert room.getSignal().getPower() == 20
    assert room.getSignal().getFrequency() == 200000

    a2 = cpl.Point(2,3)
    b2 = cpl.Point(4,5)
    w2 = cpl.Wall(a2, b2, 0.1)
    c2 = cpl.Point(3,4)
    p2 = cpl.Pillar(c2, 0.2)
    room.addWall(w2)
    room.addPillar(p2)
    assert len(room.getWalls()) == 2
    assert len(room.getPillars()) == 2
    assert room.getWalls()[1].getP1().getX() == 2
    assert room.getWalls()[1].getP1().getY() == 3
    assert room.getWalls()[1].getP2().getX() == 4
    assert room.getWalls()[1].getP2().getY() == 5
    assert room.getWalls()[1].getLossFactor() == 0.1
    assert room.getPillars()[1].getP().getX() == 3
    assert room.getPillars()[1].getP().getY() == 4
    assert room.getPillars()[1].getLossFactor() == 0.2
    
def test_computePathLoss():
    room = set_room()
    for i in range(10):
        for j in range(10):
            p = cpl.Point(i,j)
            ret = room.computePathLoss(p)
            # type double
            print(ret)
            assert type(ret) == float
            assert ret >= 0