// Lab7_TD.cpp : This file contains the 'main' function. Program execution begins and ends there. //

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    RenderWindow window(VideoMode(800, 600), "Bounce");
    World world(Vector2f(0, 1));

    PhysicsCircle ball;
    ball.setCenter(Vector2f(50, 50));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);

    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    PhysicsRectangle leftWall, rightWall, topWall;

    leftWall.setSize(Vector2f(20, 600));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    rightWall.setSize(Vector2f(20, 600));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    topWall.setSize(Vector2f(800, 20));
    topWall.setCenter(Vector2f(400, 10));
    topWall.setStatic(true);
    world.AddPhysicsBody(topWall);

    PhysicsRectangle centerBox;
    centerBox.setSize(Vector2f(100, 100));
    centerBox.setCenter(Vector2f(400, 300));
    centerBox.setStatic(true);
    world.AddPhysicsBody(centerBox);

    int thudCount(0);
    int bangCount(0);

    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    leftWall.onCollision = rightWall.onCollision = topWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount << endl;
        thudCount++;
    };

    centerBox.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        bangCount++;
        cout << "bang " << bangCount << endl;
        if (bangCount >= 3) {
            exit(0);
        }
    };

    ball.applyImpulse(Vector2f(0.1f, 0.2f));

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (window.isOpen()) {
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        window.clear(Color(0, 0, 0));
        window.draw(ball);
        window.draw(floor);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(topWall);
        window.draw(centerBox);
        window.display();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
