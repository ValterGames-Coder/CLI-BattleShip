#pragma once
#include <map>

struct Position
{
    Position(short y = 0, short x = 0)
    {
        this->y = y;
        this->x = x;
    }

    short y, x;

    friend inline bool operator==(const Position& pos1, const Position& pos2) {
        return pos1.y == pos2.y && pos1.x == pos2.x;
    }

    friend inline bool operator!=(const Position& pos1, const Position& pos2) {
        return pos1.y != pos2.y || pos1.x != pos2.x;
    }

    friend inline bool operator<=(const Position& pos1, const Position& pos2) {
        return pos1.y <= pos2.y && pos1.x <= pos2.x;
    }
    
    friend inline bool operator>=(const Position& pos1, const Position& pos2) {
        return pos1.y >= pos2.y && pos1.x >= pos2.x;
    }

    friend inline bool operator<(const Position& pos1, const Position& pos2) {
        return pos1.y < pos2.y || pos1.x < pos2.x;
    }

    friend inline bool operator>(const Position& pos1, const Position& pos2) {
        return pos1.y > pos2.y || pos1.x > pos2.x;
    }

    friend inline bool operator<=(const Position& pos, const short& point) {
        return pos.y <= point && pos.x <= point;
    }

    friend inline bool operator>=(const Position& pos, const short& point) {
        return pos.y >= point && pos.x >= point;
    }

    friend inline bool operator<(const Position& pos, const short& point) {
        return pos.y < point || pos.x < point;
    }

    friend inline bool operator>(const Position& pos, const short& point) {
        return pos.y > point || pos.x > point;
    }

    const Position operator+(const Position& pos) const {
        return {(short)(y + pos.y), (short)(x + pos.x)};
    }

    const Position operator+=(const Position& pos) const {
        return {(short)(y + pos.y), (short)(x + pos.x)};
    }
    
    // const Position operator-(const std::pair<unsigned short, unsigned short> pair) const {
    //     return {(short)(y - pair.first), (short)(x - pair.second)};
    // }
};