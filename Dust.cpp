#include "Dust.hpp"
#include <cmath>
/// @brief Конструктор класса Dust. 
/// @param velocity Скорость частицы.
/// @param center Центральная точка частицы.
/// @param radius Радиус частицы.
/// @param color Цвет частицы.
/// @param lifetime Время жизни частицы.
Dust::Dust(Velocity velocity, Point center, double radius, Color color, double lifetime) 
: velocity(velocity), center(center), radius(radius), color(color), lifetime(lifetime) {}

//жива ли частица?
bool Dust::getIsAlive() const {
    return isAlive;
}

void Dust::update(double deltaTime) {
    lifetime -= deltaTime;
    if (lifetime <= 0) {
        isAlive = false; // Устанавливаем флаг для удаления
    }
}

/// @brief Задает скорость объекта
/// @param velocity значение скорости
void Dust::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

/// @brief Возваращает скорость объекта
/// @return скорость объекта
Velocity Dust::getVelocity() const {
    return velocity;
}

/// @brief Выполняет отрисовку объекта
/// @details объект Dust абстрагирован от способа отображения пикселей на экране, знаком с интерфейсом, который предоставляет Painter (выполняется путем вызова painter.draw(...))
/// @param painter контекст отрисовки
void Dust::draw(Painter& painter) const {
    painter.draw(center, radius, color);
}

/// @brief Задает координаты центра объекта
/// @param center центр объекта
void Dust::setCenter(const Point& center) {
    this->center = center;
}

/// @brief Возвращает координаты центра объекта
/// @return центр объекта
Point Dust::getCenter() const {
    return center;
}

/// @brief Возвращает радиус объекта
/// @return радиус объекта
double Dust::getRadius() const {
    return radius;
}