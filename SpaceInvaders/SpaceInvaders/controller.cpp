#include <QDebug>
#include "controller.h"

Controller::Controller(QObject *obj) : QObject(obj), m_x(1800/2), m_y(930), speed(10)
{
    connect(&tState, &QTimer::timeout, this, &Controller::stateUpdate);
    tState.start(60);

    connect(&tAddEnemy, &QTimer::timeout, this, &Controller::addEnemy);
    tAddEnemy.start(1000);

    connect(&tMovement, &QTimer::timeout, this, &Controller::movement);
}

double Controller::x() { return m_x;}
double Controller::y() { return m_y;}

void Controller::setX(double value)
{
    if (value < 0 || value > xMax)
        return;

    m_x = value;
    emit xChanged();
}
void Controller::setY(double value)
{
    if (value < 0 || value > yMax)
        return;

    m_y = value;
    emit yChanged();
}

void Controller::setScore(QString score)
{
    m_score = score;
    emit scoreChanged();
}

QString Controller::score()
{
    return m_score;
}
void Controller::moveLeft()
{
    moveDirection = 1;
    tMovement.start(20);
}
void Controller::moveRight()
{
    moveDirection = 2;
    tMovement.start(20);
}

void Controller::moveUp()
{
    setY(m_y - speed);
}

void Controller::moveDown()
{
    setY(m_y + speed);
}

void Controller::jumpInit()
{
    if (m_y < yMax/2)
    {
        return;
    }
    jumpCurrentSpeed = jumpInitSpeed;
}

void Controller::fireBullet()
{
    auto bullet = new Bullet(m_x + 20, m_y - 25, this);
    connect(bullet, &Bullet::destroyBullet, this, &Controller::destroyBullet);
    bullets.push_back(bullet);
    qInfo() << "Bullet push";
    emit bulletsChanged();
}

void Controller::stopMovement()
{
    moveDirection = 0;
    tMovement.stop();
}

void Controller::destroyBullet(Bullet *bullet)
{
    int index = bullets.indexOf(bullet);
    if (index != -1)
    {
        bullets.removeAt(index);
        delete bullet;
        emit bulletsChanged();
        qInfo() << "Bullet destroy";
    }
}
void Controller::destroyEnemy(Enemy *enemy)
{
    int index = enemies.indexOf(enemy);
    if (index != -1)
    {
        enemies.removeAt(index);
        delete enemy;
        emit enemiesChanged();
        qInfo() << "Enemy destroy";
    }

}

void Controller::movement()
{
    if (moveDirection == 1)
        setX(m_x - speed);
    else
        setX(m_x + speed);

}
void Controller::addEnemy()
{
    enemies.push_back(new Enemy);
    emit enemiesChanged();

}

QQmlListProperty <Bullet> Controller::getBullets()
{
    return QQmlListProperty(this, &bullets);
}

QQmlListProperty <Enemy> Controller::getEnemies()
{
    return QQmlListProperty(this, &enemies);
}

void Controller::restartGame()
{
    for (auto e: enemies)
        delete e;

    enemies.clear();

    emit enemiesChanged();

    for (auto b: bullets)
        delete b;

    bullets.clear();

    emit bulletsChanged();

    setScore("0");

    setX(1800/2);
    setY(930);
}

void Controller::stateUpdate()
{
    checkGameOver();
    checkCollision();

    if (m_y + jumpCurrentSpeed > yMax)
    {
        setY(yMax);
        return;
    }
    setY(m_y + jumpCurrentSpeed);
    jumpCurrentSpeed += mGravity;
}

void Controller::checkCollision()
{
    for(int i = bullets.size() - 1; i >= 0; i--)
    {
        Bullet *bullet = bullets[i];        
        double bulletLeft = bullet->x();
        double bulletRight = bullet->x() + 10;
        double bulletTop = bullet->y();
        double bulletBottom = bullet->y() + 30;

        for (int j = enemies.size() - 1; j >= 0; j--)
        {

            Enemy *enemy = enemies[j];

            double enemyLeft = enemy->x();
            double enemyRight = enemy->x() + 40;
            double enemyTop = enemy->y();
            double enemyBottom = enemy->y() + 40;

            if (bulletRight > enemyLeft && bulletLeft < enemyRight &&
                bulletTop < enemyBottom && bulletBottom > enemyTop)
            {
                destroyBullet(bullet);
                destroyEnemy(enemy);
                setScore(QString::number(m_score.toInt() + 10));
                break;
            }

        }
    }
}

void Controller::checkGameOver()
{
    double playerLeft = m_x;
    double playerRight = m_x + 50;
    double playerTop = m_y;
    double playerBottom = m_y + 50;

    for (const Enemy* enemy : enemies)
    {
        if(enemy->y() > yMax)
        {
            emit gameOver();
            return;
        }

        double enemyLeft = enemy->x();
        double enemyRight = enemy->x() + 40;
        double enemyTop = enemy->y();
        double enemyBottom = enemy->y() + 40;

        if (enemyRight > playerLeft && enemyLeft < playerRight &&
            enemyTop < playerBottom && enemyBottom > playerTop)
        {
            emit gameOver();
            return;
        }
    }
}
