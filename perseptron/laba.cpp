#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits> // for numeric_limits



class Point {
public:
    double x, y;
    int label; // 0 or 1 (class label)

    Point(double x, double y, int label) : x(x), y(y), label(label) {}
};

class Perceptron {
public:
    double w1, w2, b; // weights and bias

    Perceptron() : w1(0.0), w2(0.0), b(0.0) {}

    int activate(double sum) {
        return (sum >= 0) ? 1 : 0;
    }

    int predict(const Point& p) {
        double sum = w1 * p.x + w2 * p.y + b;
        return activate(sum);
    }

    void train(const std::vector<Point>& points, double learning_rate, int epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (const auto& p : points) {
                int prediction = predict(p);
                int error = p.label - prediction;
                w1 += learning_rate * error * p.x;
                w2 += learning_rate * error * p.y;
                b += learning_rate * error;
            }
        }
    }
};

std::vector<Point> loadPointsFromFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            double x, y;
            int label;
            ss >> x >> y >> label;
            if (ss) { // Check if the line was successfully parsed
                points.emplace_back(x, y, label);
            } else {
                std::cerr << "Warning: Skipping invalid line: " << line << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
    }
    return points;
}

int main() {
    // Predefined training data
    std::vector<Point> training_points = {
        {1.0, 2.0, 0},
        {2.0, 1.0, 0},
        {1.5, 1.5, 0},
        {4.0, 5.0, 1},
        {5.0, 4.0, 1},
        {4.5, 4.5, 1}
    };


    Perceptron perceptron;
    perceptron.train(training_points, 0.1, 100);

    std::cout << "Trained perceptron weights: w1 = " << perceptron.w1
              << ", w2 = " << perceptron.w2 << ", b = " << perceptron.b << std::endl;

    std::string filename;
    std::cout << "Enter the filename containing your points (x y label): ";
    std::cin >> filename;

    std::vector<Point> user_points = loadPointsFromFile(filename);

    for (const auto& p : user_points) {
        int prediction = perceptron.predict(p);
        std::cout << "Point (" << p.x << ", " << p.y << ") predicted as class: " << prediction << std::endl;
    }

    //Optional: Add a check for invalid input from file
    if(std::cin.fail()){
        std::cout << "Invalid input. Please enter numbers only." << std::endl;
        std::cin.clear(); // clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
    }


    return 0;
}
