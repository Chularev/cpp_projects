#include "enemy.h"

Enemy::Enemy(QObject *obj) : QObject(obj),
    speed(1),
    m_x(rand() % 1750),
    m_y(-20)

{
    connect(&tUpdateEnemy, &QTimer::timeout, this, &Enemy::updateEnemy );
    tUpdateEnemy.start(20);
}

double Enemy::x() const { return m_x;}
double Enemy::y() const { return m_y;}

int Enemy::type() const
{
    return m_type;
}

void Enemy::setX(double value)
{
    if (value < 0 || value > xMax)
        return;

    m_x = value;
    emit xChanged();
}
void Enemy::setY(double value)
{
    m_y = value;
    emit yChanged();
}

void Enemy::updateEnemy()
{
    setY(m_y + speed);
}
