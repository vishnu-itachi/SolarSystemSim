#include "IndexBuffer.h"
#include "Point.hpp"
#include "VertexBuffer.h"
#include <string>

class CelestialBody
{
private:
    std::string m_Name;
    float m_radius;
    float m_mass;
    Point m_position;

public:
    CelestialBody(const std::string &name, float radius, float mass, Point position)
        : m_Name(name), m_radius(radius), m_mass(mass), m_position(position)
    {
    }
    float GetRadius() const
    {
        return m_radius;
    }

    float GetMass() const
    {
        return m_mass;
    }

    Point GetPosition() const
    {
        return m_position;
    }

    void update()
    {
    }

    void draw()
    {
    }
};
