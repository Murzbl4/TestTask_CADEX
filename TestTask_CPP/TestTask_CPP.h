#ifndef TestTank_CPP_H
#define TestTank_CPP_H

class Point3D {
private:
    double x;
    double y;
    double z;

public:
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};

class Vector3D {
private:
    double x;
    double y;
    double z;

public:
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }
};
class Curve {
public:
    virtual ~Curve() {}

    virtual double getRadius() const = 0;
    virtual double getMinorAxis() const = 0;
    virtual double getMajorAxis() const = 0;
    virtual double getStep() const = 0;
    virtual Point3D getPoint(double t) const = 0;
    virtual Vector3D getDerivative(double t) const = 0;
    virtual void printCoordinatesAndDerivatives() const = 0;
};
#endif 