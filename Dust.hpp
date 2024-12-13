#pragma once
#include "Point.h"
#include "Color.h"
#include "Velocity.h"
#include "Painter.h"

class Dust {
public:
    Dust(Velocity velocity, Point center, double radius, Color color, double lifetime);
    bool getIsAlive() const;
    void update(double deltaTime);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool isCollidable; // Новое поле
    double lifetime;
    bool isAlive = true; // Флаг для отслеживания жизни частицы
};