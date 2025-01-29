#include "Drawing.h"

// Constructor
Drawing::Drawing() {}

// Destructor
Drawing::~Drawing() {
    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

// Métodos de la clase
void Drawing::add_front(Shape* shape) {
    shapes.insert(shapes.begin(), shape);
}

void Drawing::add_back(Shape* shape) {
    shapes.push_back(shape);
}

void Drawing::print_all() const {
    for (const Shape* shape : shapes) {
        shape->print();
    }
}

double Drawing::get_area_all_circles() const {
    double total_area = 0.0;
    for (const Shape* shape : shapes) {
        const Circle* circle = dynamic_cast<const Circle*>(shape);
        if (circle) {
            total_area += circle->area();
        }
    }
    return total_area;
}

void Drawing::move_squares(double incX, double incY) {
    for (Shape* shape : shapes) {
        Square* square = dynamic_cast<Square*>(shape);
        if (square) {
            square->translate(incX, incY);
        }
    }
}
