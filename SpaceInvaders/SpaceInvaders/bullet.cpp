#include "bullet.h"

Bullet::Bullet(double x, double y, QObject *obj) : QObject(obj), m_x(x), m_y(y), speed(-10)
{
    connect(&tUpdateBullet, &QTimer::timeout, this, &Bullet::updateBullet );
    tUpdateBullet.start(60);
}

double Bullet::x() { return m_x;}
double Bullet::y() { return m_y;}

void Bullet::setX(double value)
{
    if (value < 0 || value > xMax)
        return;

    m_x = value;
    emit xChanged();
}
void Bullet::setY(double value)
{
    m_y = value;
    emit yChanged();
}

void Bullet::updateBullet()
{
    setY(m_y + speed);
    if (m_y < 0)
        emit destroyBullet(this);
}
