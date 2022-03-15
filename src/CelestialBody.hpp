#pragma once

#include "IndexBuffer.h"
#include "Vector.hpp"
#include "VertexBuffer.h"
#include <corecrt.h>
#include <string>
#include <chrono>

using namespace std::chrono;
typedef std::chrono::duration<float> fseconds;

class CelestialBody
{
private:
    std::string m_name;
    int m_radius;
    float m_mass;
    vector m_position;
    vector m_astro_scale;
    vector m_velocity;

public:
    CelestialBody(const std::string &name, int radius, float mass, vector position, vector astro_scale, vector velocity)
        : m_name(name), m_radius(radius), m_mass(mass), m_position(position), m_astro_scale(astro_scale), m_velocity(velocity)
    {
    }
    int name() const
    {
        return (m_name == "Sun") ? 0 : 1;
    }

    int GetRadius() const
    {
        return m_radius;
    }

    float GetMass() const
    {
        return m_mass;
    }

    vector position() const
    {
        return m_position;
    }

    vector astro_position() const
    {
        return m_position * m_astro_scale;
    }

    void update()
    {
    }

    void draw()
    {
    }

    vector apply_force(vector force, fseconds duration)
    {
        m_velocity += duration.count() * force / m_mass;
        return m_velocity;
    }

    vector travel(fseconds duration)
    {
        auto astro_position = m_position * m_astro_scale;
        astro_position += duration.count() * m_velocity;
        m_position = astro_position / m_astro_scale;
        return m_position;
    }

    bool operator==(const CelestialBody right)
    {
        return m_name == right.m_name;
    }
};
