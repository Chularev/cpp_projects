#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QTimer>

class Enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int type READ type)
public:
    Enemy(QObject *obj = nullptr);

    double x() const;
    double y() const;
    int type() const;

    void setX(double value);
    void setY(double value);

signals:
    void xChanged();
    void yChanged();

private slots:
    void updateEnemy();

private:
    double m_x;
    double xMax = 1800 - 50;
    double yMax = 1000 - 50;
    double m_y;
    double speed;

    int m_type = rand() % 5;

    QTimer tUpdateEnemy;
};

#endif // ENEMY_H
