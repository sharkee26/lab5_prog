#pragma once
#include "Painter.h"
#include "Point.h"
#include "Color.h"//подключаем цвета
#include "Velocity.h"

class Ball {
public:
    Ball(Velocity velocity, Point center, double radius, Color color, bool isCollidable); //добавляем конструктор
    bool getIsCollidable() const; //
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;

private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool isCollidable; // состояние возможности столкновения
};
