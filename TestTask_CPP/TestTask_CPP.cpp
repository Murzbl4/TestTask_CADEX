#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>
#include "TestTask_CPP.h"


class Circle : public Curve {
private:
    double radius;

public:
    Circle(double r) : radius(r) {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive.");
        }
    }
    double getMinorAxis() const override {
        return radius;
    }
    double getMajorAxis() const override {
        return radius;
    }
    double getStep() const override {
        return radius;
    }

    double getRadius() const override {
        return radius;
    }

    Point3D getPoint(double t) const override {
        double x = radius * std::cos(t);
        double y = radius * std::sin(t);
        double z = 0.0;
        return Point3D(x, y, z);
    }

    Vector3D getDerivative(double t) const override {
        double dx = -radius * std::sin(t);
        double dy = radius * std::cos(t);
        double dz = 0.0;
        return Vector3D(dx, dy, dz);
    }

    void printCoordinatesAndDerivatives() const override {
        std::cout << "Circle - Radius: " << radius << ", Coordinates: (" << radius << ", " << radius << ", " << radius << "), Derivative: (1, 1, 1)" << std::endl;
    }
};

class Ellipse : public Curve {
private:
    double majorAxis;
    double minorAxis;

public:
    Ellipse(double major, double minor) : majorAxis(major), minorAxis(minor) {
        if (majorAxis <= 0 || minorAxis <= 0) {
            throw std::invalid_argument("Axes lengths must be positive.");
        }
    }
    double getStep() const override {
        return majorAxis;
    }
    double getRadius() const override {
        return majorAxis;
    }
    double getMajorAxis() const override {
        return majorAxis;
    }
    double getMinorAxis() const override {
        return minorAxis;
    }

    Point3D getPoint(double t) const override {
        double x = majorAxis * std::cos(t);
        double y = minorAxis * std::sin(t);
        double z = 0.0;
        return Point3D(x, y, z);
    }

    Vector3D getDerivative(double t) const override {
        double dx = -majorAxis * std::sin(t);
        double dy = minorAxis * std::cos(t);
        double dz = 0.0; 
        return Vector3D(dx, dy, dz);
    }

    void printCoordinatesAndDerivatives() const override {
        std::cout << "Ellipse - Major Axis: " << majorAxis << ", Minor Axis: " << minorAxis << ", Coordinates: (" << majorAxis << ", " << minorAxis << ", " << majorAxis << "), Derivative: (1, 1, 1)" << std::endl;
    }
};

class Helix : public Curve {
private:
    double radius;
    double step;

public:
    Helix(double r, double s) : radius(r), step(s) {
        if (radius <= 0 || step <= 0) {
            throw std::invalid_argument("Radius and step must be positive.");
        }
    }
    double getMinorAxis() const override {
        return radius;
    }
    double getMajorAxis() const override {
        return radius;
    }
    double getRadius() const override {
        return radius;
    }
    double getStep() const override {
        return step;
    }

    Point3D getPoint(double t) const override {
        double x = radius * std::cos(t);
        double y = radius * std::sin(t);
        double z = step * t / (2 * M_PI);
        return Point3D(x, y, z);
    }

    Vector3D getDerivative(double t) const override {
        double dx = -radius * std::sin(t);
        double dy = radius * std::cos(t);
        double dz = step / (2 * M_PI);
        return Vector3D(dx, dy, dz);
    }

    void printCoordinatesAndDerivatives() const override {
        std::cout << "Helix - Radius: " << radius << ", Step: " << step << ", Coordinates: (" << radius << ", " << radius << ", " << step << "), Derivative: (1, 1, 1)" << std::endl;
    }
};

class ThreeDHelix {
private:
    std::vector<Curve*> curves;
    std::vector<Circle*> circles;

public:
    ThreeDHelix() {}

    void generateRandomCurves(int numCircles, int numEllipses, int numHelices) {
        curves.clear();

        for (int i = 0; i < numCircles; ++i) {
            double radius = getRandomRadius();
            Circle* myCircle = new Circle(radius);
            curves.push_back(new Circle(radius)); 
            
        }

        for (int i = 0; i < numEllipses; ++i) {
            double majorAxis = getRandomRadius();
            double minorAxis = getRandomRadius();
            curves.push_back(new Ellipse(majorAxis, minorAxis));
        }

        for (int i = 0; i < numHelices; ++i) {
            double radius = getRandomRadius();
            double step = getRandomRadius();
            curves.push_back(new Helix(radius, step));
        }
    }

    double getRandomRadius() const {
        return (std::rand() % 100 + 1) / 10.0;
    }

    void printCoordinatesAndDerivatives(double t) const {
        for (Curve* curve : curves) {
            Point3D point = curve->getPoint(t);
            Vector3D derivative = curve->getDerivative(t);
            Circle* circle_cast = dynamic_cast<Circle*>(curve);
            if (circle_cast != nullptr) {
                std::cout << "Circle - Radius: " << curve->getRadius()
                    << ", Coordinates: (" << point.getX() << ", " << point.getY() << ", " << point.getZ()
                    << "), Derivative: (" << derivative.getX() << ", " << derivative.getY() << ", " << derivative.getZ() << ")" << std::endl;
            }
            Ellipse* Ellipse_cast = dynamic_cast<Ellipse*>(curve);
            if (Ellipse_cast != nullptr) {
                std::cout << "Ellipse - MajorAxis: " << curve->getMajorAxis() << ", " << "MinorAxis: " << curve->getMinorAxis()
                    << ", Coordinates: (" << point.getX() << ", " << point.getY() << ", " << point.getZ()
                    << "), Derivative: (" << derivative.getX() << ", " << derivative.getY() << ", " << derivative.getZ() << ")" << std::endl;
            }
            Helix* Helix_cast = dynamic_cast<Helix*>(curve);
            if (Helix_cast != nullptr) {
                std::cout << "Helix - Radius: " << curve->getRadius()<<", "<< "Step: " <<curve->getStep()
                    << ", Coordinates: (" << point.getX() << ", " << point.getY() << ", " << point.getZ()
                    << "), Derivative: (" << derivative.getX() << ", " << derivative.getY() << ", " << derivative.getZ() << ")" << std::endl;
            }
        }
    }

    void sortCurvesByRadius() {
        for (Curve* curve : curves) {
            Circle* circle = dynamic_cast<Circle*>(curve);
            if (circle != nullptr) {
                circles.push_back(circle);
            }
        }
        std::sort(circles.begin(), circles.end(), [](const Circle* a, const Circle* b) {
            return a->getRadius() < b->getRadius();
            });
    }

    double getParallelSumOfRadii() const {
        double sumOfRadii = 0.0;

        #pragma omp parallel for reduction(+:sumOfRadii)
        for (int i = 0; i < circles.size(); ++i) {
            sumOfRadii += circles[i]->getRadius();
        }
        return sumOfRadii;
    }

    ~ThreeDHelix() {
        for (Curve* curve : curves) {
            delete curve;
        }
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int count_Circle = 0;
    int count_Ellipse = 0;
    int count_Helix = 0;
    std::cout << "Enter the number of Circle" << std::endl;
    std::cin >> count_Circle;
    std::cout << "Enter the number of Ellipse" << std::endl;
    std::cin >> count_Ellipse;
    std::cout << "Enter the number of Helix" << std::endl;
    std::cin >> count_Helix;

    ThreeDHelix helix;
    helix.generateRandomCurves(count_Circle, count_Ellipse, count_Helix);

    helix.printCoordinatesAndDerivatives(M_PI / 4);

    helix.sortCurvesByRadius();

    double parallelSumOfRadii = helix.getParallelSumOfRadii();

    std::cout << "Parallel sum of radii: " << parallelSumOfRadii << std::endl;
    std::cout << "Press any key to exit...";
    std::cin.get();

    return 0;
}