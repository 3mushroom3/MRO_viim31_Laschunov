#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <utility>

// Определение класса Point
class Point {
public:
    explicit Point(int dimensions) : coordinates(dimensions) {}

    void setCoordinate(int index, double value) {
        coordinates[index] = value;
    }

    double getCoordinate(int index) const {
        return coordinates[index];
    }

    const std::vector<double>& getCoordinates() const {
        return coordinates;
    }

    int getDimensions() const {
        return coordinates.size();
    }

    // Добавляем единичный элемент для смещения (bias)
    std::vector<double> getAugmentedCoordinates() const {
        std::vector<double> augmented = coordinates;
        augmented.push_back(1.0); // добавляем bias
        return augmented;
    }

private:
    std::vector<double> coordinates;
};

// Определение класса Space
class Space {
public:
    Space(int pointCount, int dimensions, double minX, double maxX, double minY, double maxY)
        : minX(minX), maxX(maxX), minY(minY), maxY(maxY) {
        points.reserve(pointCount);
        generatePoints(pointCount);
    }

    void generatePoints(int pointCount) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distX(minX, maxX);
        std::uniform_real_distribution<> distY(minY, maxY);

        for (int i = 0; i < pointCount; ++i) {
            Point point(2);
            point.setCoordinate(0, distX(gen));
            point.setCoordinate(1, distY(gen));
            points.push_back(point);
        }
    }

    const Point& getPoint(int index) const {
        return points[index];
    }

    const std::vector<Point>& getPoints() const {
        return points;
    }

    int getPointCount() const {
        return points.size();
    }

    Point calculateCenter() const {
        int dimensions = points[0].getDimensions();
        Point center(dimensions);
        for (const auto& point : points) {
            for (int i = 0; i < dimensions; ++i) {
                center.setCoordinate(i, center.getCoordinate(i) + point.getCoordinate(i));
            }
        }
        for (int i = 0; i < dimensions; ++i) {
            center.setCoordinate(i, center.getCoordinate(i) / points.size());
        }
        return center;
    }

    static double calculateDistance(const Point& p1, const Point& p2) {
        double distance = 0.0;
        int dimensions = p1.getDimensions();
        for (int i = 0; i < dimensions; ++i) {
            distance += std::pow(p1.getCoordinate(i) - p2.getCoordinate(i), 2);
        }
        return std::sqrt(distance);
    }

    static double calculateManhattanDistance(const Point& p1, const Point& p2) {
        double distance = 0.0;
        int dimensions = p1.getDimensions();
        for (int i = 0; i < dimensions; ++i) {
            distance += std::abs(p1.getCoordinate(i) - p2.getCoordinate(i));
        }
        return distance;
    }

private:
    std::vector<Point> points;
    double minX, maxX, minY, maxY;
};
