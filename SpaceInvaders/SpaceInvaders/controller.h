#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QQmlListProperty>
#include <QList>

#include "bullet.h"
#include "enemy.h"

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QString score READ score WRITE setScore NOTIFY scoreChanged)

    Q_PROPERTY(QQmlListProperty<Bullet> getBullets READ getBullets NOTIFY bulletsChanged)
    Q_PROPERTY(QQmlListProperty<Enemy> getEnemies READ getEnemies NOTIFY enemiesChanged)
public:
    Controller(QObject *obj = nullptr);

    double x();
    double y();

    void setX(double value);
    void setY(double value);

    QString score();
    void setScore(QString score);

    Q_INVOKABLE void moveLeft();

    Q_INVOKABLE void moveRight();

    Q_INVOKABLE void moveUp();

    Q_INVOKABLE void moveDown();

    Q_INVOKABLE void jumpInit();

    Q_INVOKABLE void fireBullet();

    Q_INVOKABLE void stopMovement();

    Q_INVOKABLE QQmlListProperty<Bullet> getBullets();

    Q_INVOKABLE QQmlListProperty<Enemy> getEnemies();

    Q_INVOKABLE void restartGame();

signals:
    void xChanged();
    void yChanged();
    void bulletsChanged();
    void enemiesChanged();
    void scoreChanged();
    void gameOver();

private slots:
    void stateUpdate();
    void addEnemy();
    void destroyBullet(Bullet *bullet);
    void destroyEnemy(Enemy *enemy);
    void movement();

private:
    void checkCollision();
    void checkGameOver();

    double m_x;
    double xMax = 1800 - 50;
    double yMax = 1000 - 85;
    double m_y;
    double speed;
    double jumpInitSpeed = -40;
    double jumpCurrentSpeed = 0;
    double mGravity = 2;
    QTimer tState;
    QTimer tAddEnemy;


    QList<Bullet*> bullets;
    QList<Enemy*> enemies;

    int moveDirection = 0;
    QTimer tMovement;

    QString m_score = "0";
};

#endif // CONTROLLER_H
