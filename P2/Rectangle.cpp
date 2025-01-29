#include "Rectangle.h"
#include <cmath>

bool Rectangle::check(Point2D* vertices) {
    double d01 = Point2D::distance(vertices[0], vertices[1]);
    double d23 = Point2D::distance(vertices[2], vertices[3]);
    double d12 = Point2D::distance(vertices[1], vertices[2]);
    double d30 = Point2D::distance(vertices[3], vertices[0]);

    return (d01 == d23) && (d12 == d30);
}

Rectangle::Rectangle() : Shape("red") {
    vs = new Point2D[N_VERTICES]{
        Point2D(-1, 0.5), Point2D(1, 0.5),
        Point2D(1, -0.5), Point2D(-1, -0.5)
    };
}

Rectangle::Rectangle(std::string color, Point2D* vertices) : Shape(color) {
    if (!check(vertices)) {
        throw std::invalid_argument("Los vértices no forman un rectángulo válido.");
    }
    vs = new Point2D[N_VERTICES];
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i] = vertices[i];
    }
}

Rectangle::Rectangle(const Rectangle &r) : Shape(r.color) {
    vs = new Point2D[N_VERTICES];
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i] = r.vs[i];
    }
}

Rectangle::~Rectangle() {
    delete[] vs;
}

Point2D Rectangle::get_vertex(int ind) const {
    if (ind < 0 || ind >= N_VERTICES) {
        throw std::out_of_range("Índice fuera de rango.");
    }
    return vs[ind];
}

Point2D Rectangle::operator[](int ind) const {
    return get_vertex(ind);
}

void Rectangle::set_vertices(Point2D* vertices) {
    if (!check(vertices)) {
        throw std::invalid_argument("Los vértices no forman un rectángulo válido.");
    }
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i] = vertices[i];
    }
}

Rectangle& Rectangle::operator=(const Rectangle &r) {
    if (this != &r) {
        color = r.color;
        for (int i = 0; i < N_VERTICES; i++) {
            vs[i] = r.vs[i];
        }
    }
    return *this;
}

double Rectangle::area() const {
    double width = Point2D::distance(vs[0], vs[1]);
    double height = Point2D::distance(vs[1], vs[2]);
    return width * height;
}

// Cálculo del perímetro
double Rectangle::perimeter() const {
    double width = Point2D::distance(vs[0], vs[1]);
    double height = Point2D::distance(vs[1], vs[2]);
    return 2 * (width + height);
}

// Traslación del rectángulo
void Rectangle::translate(double incX, double incY) {
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i].x += incX;
        vs[i].y += incY;
    }
}

void Rectangle::print() {
    std::cout << "[Rectangle: color = " << color;
    for (int i = 0; i < N_VERTICES; i++) {
        std::cout << "; v" << i << " = (" << vs[i].x << "," << vs[i].x << ")";
    }
    std::cout << "]" << std::endl;
}

std::ostream& operator<<(std::ostream &out, const Rectangle &r) {
    out << "[Rectangle: color = " << r.color;
    for (int i = 0; i < Rectangle::N_VERTICES; i++) {
        out << "; v" << i << " = (" << r.vs[i].x << "," << r.vs[i].y << ")";
    }
    out << "]";
    return out;
}
