#ifndef _BODY_DEFINED
#define _BODY_DEFINED

#include <iostream>
#include <cmath>
#include <tuple>
#include <fstream>

typedef std::tuple<double, double, double> vector_3d;

constexpr int X = 0;
constexpr int Y = 1;
constexpr int Z = 2;

constexpr double xScale = 1.0;
constexpr double yScale = 1.0;
constexpr double zScale = 1.0;

constexpr double G = 0.00000000006674;

inline vector_3d zero_vect() {
    return (vector_3d)std::make_tuple(0.0, 0.0, 0.0);
}

class Body {
public:
    int id;
    double mass;
    vector_3d pos;
    vector_3d acc;
    vector_3d vel;

    Body();
    Body(int id, double mass, const vector_3d& pos);
    Body(int id, double mass, const vector_3d& pos, const vector_3d& acc, const vector_3d& vel);
    Body(double mass, double x, double y, double z, double vx, double vy, double vz) 
        : id(0), mass(mass), pos(std::make_tuple(x, y, z)), acc(zero_vect()), vel(std::make_tuple(vx, vy, vz)) {}

    friend std::ostream& operator<<(std::ostream& out, const Body& b);

    double distance(const Body& b);
    vector_3d force(const Body& b);
    void apply(const vector_3d f);
    void move(double t);
    void logBody(std::ofstream& f);
};

inline Body center_of_mass(Body bodies[], int n) {
    double totalMass = 0;
    vector_3d cmPos = zero_vect();
    for (int i = 0; i < n; i++) {
        std::get<X>(cmPos) += (bodies[i].mass * std::get<X>(bodies[i].pos));
        std::get<Y>(cmPos) += (bodies[i].mass * std::get<Y>(bodies[i].pos));
        std::get<Z>(cmPos) += (bodies[i].mass * std::get<Z>(bodies[i].pos));
        totalMass += bodies[i].mass;
    }
    std::get<X>(cmPos) /= totalMass;
    std::get<Y>(cmPos) /= totalMass;
    std::get<Z>(cmPos) /= totalMass;
    Body b = Body(0, totalMass, cmPos, zero_vect(), zero_vect());
    return b;
}

inline Body getBody(std::ifstream& f) {
    int id;
    double mass;
    double posx, posy, posz;
    double accx, accy, accz;
    double velx, vely, velz;
    f >> id >> mass;
    f >> posx >> posy >> posz;
    f >> accx >> accy >> accz;
    f >> velx >> vely >> velz;
    vector_3d pos = std::make_tuple(posx, posy, posz);
    vector_3d acc = std::make_tuple(accx, accy, accz);
    vector_3d vel = std::make_tuple(velx, vely, velz);
    return Body(id, mass, pos, acc, vel);
}

#endif // _BODY_DEFINED
