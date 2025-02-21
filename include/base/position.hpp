#pragma once

struct Position
{
    Position(short y = 0, short x = 0) : y(y), x(x) {}

    short y, x;

    friend inline bool operator==(const Position& pos1, const Position& pos2) {
        return pos1.y == pos2.y && pos1.x == pos2.x;
    }

    friend inline bool operator!=(const Position& pos1, const Position& pos2) {
        return !(pos1 == pos2);
    }

    friend inline bool operator<(const Position& pos1, const Position& pos2) {
        return (pos1.y < pos2.y) || (pos1.y == pos2.y && pos1.x < pos2.x);
    }

    friend inline bool operator>(const Position& pos1, const Position& pos2) {
        return pos2 < pos1;
    }

    friend inline bool operator<=(const Position& pos1, const Position& pos2) {
        return !(pos1 > pos2); 
    }

    friend inline bool operator>=(const Position& pos1, const Position& pos2) {
        return !(pos1 < pos2);
    }

    const Position operator+(const Position& pos) const {
        return Position(y + pos.y, x + pos.x);
    }

    Position& operator+=(const Position& pos) {
        y += pos.y;
        x += pos.x;
        return *this;
    }

    const Position operator-(const Position& pos) const {
        return Position(y - pos.y, x - pos.x);
    }

    const Position operator*(const double& point) const {
        return Position(y * point, x * point);
    }
};
