#pragma once
#include "Ball.hpp"
#include "Dust.hpp"
#include <vector>

class Physics {

  private:
     void collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const;
    void collideWithBox(std::vector<Ball>& balls, std::vector<Dust>& dusts) const;
    void move(std::vector<Ball>& balls) const;
    void moveDust(std::vector<Dust>& dusts) const;
    void processCollision(Ball& a, Ball& b, double distanceBetweenCenters2) const;
    Point topLeft;
    Point bottomRight;
    double timePerTick;

    public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, std::vector<Dust>& dusts, const size_t ticks) const;
};
