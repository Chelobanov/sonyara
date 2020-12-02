#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <cmath>
#include <iostream>
#include <string>

extern const float cell_side;

float oscillation(double t, double frequency=1.)
{
    return abs(1 - abs(fmod((M_PI * .05875f * 6.8f * t / frequency - M_PI) / M_PI, 2.)));
}

float norm(sf::Vector2f v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

sf::Vector2f normalize(sf::Vector2f v)
{
    return v / norm(v);
}

class Enemy : public GameObject
{
public:    ////
    float _radius;
    float _speed;
    sf::Vector2f _velocity;
    sf::Vector2f _p1;
    sf::Vector2f _p2;

public:
    Enemy (sf::Vector2f position, float speed, sf::Vector2f p1, sf::Vector2f p2) : GameObject (position, sf::Color(24, 48, 234), std::string("enemy"), 2)
    {
        _radius = .1875f * cell_side; //celled
        _speed = speed;
        _velocity = sf::Vector2f();
        _p1 = p1;
        _p2 = p2;
    }

    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape entity(_radius);
        entity.setPosition(_position - sf::Vector2f(_radius, _radius));
        entity.setFillColor(_color);
        entity.setOutlineColor(sf::Color::Black);
        entity.setOutlineThickness(.0875 * cell_side); //celled

        window.draw(entity);
    }

    virtual void move(double t)
    {
        _position = _p1 + (_p2 - _p1) * oscillation(t, 1. / _speed); 
    }
};

class EnemyLinear : public Enemy
{
public:
    EnemyLinear (sf::Vector2f position, float speed, sf::Vector2f p1, sf::Vector2f p2) : Enemy (position, speed, p1, p2)
    {
        _name = std::string("enemylinear");
    }

    void move(double t)
    {
        _position = _p1 + (_p2 - _p1) * oscillation(t, 1. / _speed); 
    }
};

class EnemyCircular : public Enemy
{
public:
    EnemyCircular (sf::Vector2f position, float speed, sf::Vector2f p1, sf::Vector2f p2) : Enemy (position, speed, p1, p2)
    {
        _name = std::string("enemycircular");
        _p2 = _p2 - _p1;
    }

    void move(double t)
    {
        _position = _p1 + sf::Vector2f(_p2.x * cos(_speed * t) - _p2.y * sin(_speed * t), _p2.x * sin(_speed * t) + _p2.y * cos(_speed * t));
    }
};

class EnemySquare : public Enemy
{
public:
    EnemySquare (sf::Vector2f position, float speed, sf::Vector2f p1, sf::Vector2f p2) : Enemy (position, speed, p1, p2)
    {
        _name = std::string("enemysquare");
        _p2 = _p2 - _p1;
    }

    void move(double t)
    {
        double r = abs(_p2.x) / sin(fmod(t + M_PI / 4., M_PI / 2.) + M_PI / 4.);

        _position = _p1 + sf::Vector2f(r * cos(t), r * sin(t));
    }
};