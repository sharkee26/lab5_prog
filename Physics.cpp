#include "Physics.h"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::moveDust(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        if (dust.getIsAlive()) {
            Point newPos = dust.getCenter() + dust.getVelocity().vector() * timePerTick;
            dust.setCenter(newPos);
        }
    }
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dusts, const size_t ticks) const {
    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        moveDust(dusts); // Добавляем движение частиц
        collideWithBox(balls, dusts);
        collideBalls(balls, dusts);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            // Проверяем флаги isCollidable перед обработкой столкновения
            if (!a->getIsCollidable() && !b->getIsCollidable()) {
                continue; // Оба шара не сталкиваются
            }
            const double distanceBetweenCenters2 = distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 = collisionDistance * collisionDistance;
            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
                // Создание частиц при столкновении
                for (int i = 0; i < 10; i++) {
                    double angle = (i * 2 * M_PI / 10); 
                    Velocity particleVelocity(100 * i, angle); // Скорость больше, чем у шара
                    Dust dust(particleVelocity, a->getCenter(), a->getRadius() / 3, Color(0, 0, 0), 0.15); // Установка скорости и времени жизни
                    dusts.push_back(dust);
                }
            }
        }
    }
}
int MAX_PARTICLES = 5;
void Physics::collideWithBox(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (Ball& ball : balls) {
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };
        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);

            // Создание частиц при столкновении со стеной
            for (int i = 0; i < 5; i++) {
                double angle = (i * 2 * M_PI / 5); // Разделяем угол на 5 частей
                Velocity particleVelocity(800, angle); // Скорость больше, чем у шара
                Dust dust(particleVelocity, p, r / 5, Color(0, 0, 0), 1.25); // Установка скорости и времени жизни
                dusts.push_back(dust);
            }
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);

            // Создание частиц при столкновении со стеной
            for (int i = 0; i < 5; i++) {
                double angle = (i * 2 * M_PI / 5); // Разделяем угол на 5 частей
                Velocity particleVelocity(800, angle); // Скорость больше, чем у шара
                Dust dust(particleVelocity, p, r / 5, Color(0, 0, 0), 1.25); // Установка скорости и времени жизни
                dusts.push_back(dust);
            }
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b, double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal = (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);
    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();
    // коэффициент p учитывает скорость обоих мячей
    const double p = 2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());
    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}
