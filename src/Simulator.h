#pragma once

#include "CelestialBody.hpp"
#include <chrono>
#include <map>
#include <ratio>
#include <thread>
#include <vector>


using namespace std::chrono;
typedef std::chrono::duration<float> fseconds;

class Simulator
{
private:
    std::vector<CelestialBody> _bodies;
    fseconds _time_step{10ms};

public:
    Simulator()
    {
    }

    Simulator(std::vector<CelestialBody> &bodies) : _bodies(bodies)
    {
    }

    Simulator(std::vector<CelestialBody> &bodies, std::chrono::milliseconds time_step)
        : _bodies(bodies), _time_step(time_step)
    {
    }

    std::vector<CelestialBody> &bodies()
    {
        return _bodies;
    }

    void forward()
    {

        for (auto &bodya : _bodies)
        {
            bodya.travel(_time_step);
        }

        std::map<std::string, vector> forces;
        // double G = pow(10, -11);
        double G = pow(10, -4);
        for (auto &bodya : _bodies)
        {
            forces[bodya.name()] = vector();
            for (auto bodyb : _bodies)
            {
                if (bodya == bodyb)
                    continue;
                vector separation = bodyb.astro_position() - bodya.astro_position();
                vector force =
                    separation.direction() * G * bodya.GetMass() * bodyb.GetMass() / pow(separation.magnitude(), 2);
                forces[bodya.name()] += force;
            }
            bodya.apply_force(forces[bodya.name()], _time_step);
        }
    }

    void wait()
    {
        std::this_thread::sleep_for(duration_cast<milliseconds>(_time_step));
    }
};