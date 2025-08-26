#include "controller.h"
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    Controller controller;

    for (int i = 0; i < 10'000; i++)
    {

        controller.moveLeft();
        controller.moveRight();
        controller.moveDown();
        controller.jumpInit();
        if (i % 10)
            controller.fireBullet();

        controller.getBullets();
        controller.getEnemies();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
