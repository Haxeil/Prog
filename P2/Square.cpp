#include "Square.h"
#include <iostream>

// Método privado para verificar si los vértices forman un cuadrado
bool Square::check(Point2D* vertices) {
    double d01 = Point2D::distance(vertices[0], vertices[1]);
    double d12 = Point2D::distance(vertices[1], vertices[2]);
    double d23 = Point2D::distance(vertices[2], vertices[3]);
    double d30 = Point2D::distance(vertices[3], vertices[0]);

    return (d01 == d12) && (d12 == d23) && (d23 == d30);
}

Square::Square() : Rectangle("blue", new Point2D[4]{ 
    Point2D(-1, 1), Point2D(1, 1), 
    Point2D(1, -1), Point2D(-1, -1) }) {}

Square::Square(std::string color, Point2D* vertices) : Rectangle(color, vertices) {
    if (!check(vertices)) {
        throw std::invalid_argument("Los vértices no forman un cuadrado válido.");
    }
}

void Square::set_vertices(Point2D* vertices) {
    if (!check(vertices)) {
        throw std::invalid_argument("Los vértices no forman un cuadrado válido.");
    }
    Rectangle::set_vertices(vertices);
}

void Square::print()const {
    std::cout << "[Square: ";
    Rectangle::print();
    std::cout << "]" << std::endl;
}

std::ostream& operator<<(std::ostream &out, const Square &square) {
    out << "[Square: ";
    out << static_cast<const Rectangle&>(square);
    out << "]";
    return out;
}
