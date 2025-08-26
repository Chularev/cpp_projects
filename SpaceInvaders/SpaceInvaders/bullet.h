#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>

class Bullet : public QObject
{
    Q_OBJECT


    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
public:
    Bullet(double x, double y, QObject *obj = nullptr);

    double x();
    double y();

    void setX(double value);
    void setY(double value);

signals:
    void xChanged();
    void yChanged();
    void destroyBullet(Bullet *bullet);

private slots:
    void updateBullet();

private:
    double m_x;
    double xMax = 1800 - 50;
    double yMax = 1000 - 50;
    double m_y;
    double speed;

    QTimer tUpdateBullet;
};

#endif // BULLET_H
