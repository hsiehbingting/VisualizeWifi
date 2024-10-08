import pytest
from _calc_path_loss import calc_path_loss

def test_calc_path_loss1():
    a = calc_path_loss(0, 0, 1, 1)
    assert type(a) == float
    assert a >= 0

def test_calc_path_loss2():
    a = calc_path_loss(0, 1, 1, 2)
    assert type(a) == float
    assert a >= 0