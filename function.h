#ifndef INC_3DGRAPH_FUNCTION_H
#define INC_3DGRAPH_FUNCTION_H
#include <complex>

const double pi = 3.14159265358979;


double one_variable_function_complex(double x, double y, bool complex_type) {
    std::complex<double> z(x, y);
    std::complex<double> a(0, 1);

    //Write one-varable complex function.
    std::complex<double> function_value = tan(z);

    double result;
    if (complex_type == true)
        result = function_value.real();
    else
        result = function_value.imag();

    return result;
}

double two_variable_real_function(double x, double y) {
    double z = (x -5)*(x-5) + (y-3)*(y-3);

    return z;
}


void origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size, double one_variable_input_function(double, double, bool), double view_center_x, double view_center_y, double x_angle, double y_angle, bool complex_type) {
    sf::Color transparentRed = sf::Color(0, 0, 255, 100);
    double psy = pi * y_angle / 120;
    double theta = pi * x_angle / 120;
    double length = 0.1;

    double x_start = view_center_x - 5;
    double x_end = view_center_x + 5;
    double y_start = view_center_y - 5;
    double y_end = view_center_y + 5;

    for (double x = x_start; x <= x_end; x += length) {
        for (double y = y_start; y <= y_end; y += length) {
            double z = one_variable_input_function(x, y, complex_type);

            double x_final = -x*sin(theta) + y*cos(theta);
            double y_final = sin(psy) * (-x*cos(theta) - y*sin(theta)) + z*cos(psy);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size) , y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }

    for (double y = y_start; y <= y_end; y += length) {
        for (double x = x_start; x <= x_end; x += length) {
            double z = one_variable_input_function(x, y, complex_type);

            double x_final = -x*sin(theta) + y*cos(theta);
            double y_final = sin(psy) * (-x*cos(theta) - y*sin(theta)) + z*cos(psy);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size) , y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }
}

void origin_function_two(sf::RenderWindow& window, sf::VertexArray& graph, double size, double two_variable_input_function(double, double), double view_center_x, double view_center_y, double x_angle, double y_angle) {
    sf::Color color = sf::Color(255, 0, 0, 180);
    double psy = pi * y_angle / 120;
    double theta = pi * x_angle / 120;
    double length = 0.1;

    double x_start = view_center_x - 5;
    double x_end = view_center_x + 5;
    double y_start = view_center_y - 5;
    double y_end = view_center_y + 5;


    for (double x = x_start; x <= x_end; x += length) {
        for (double y = y_start; y <= y_end; y += length) {
            double z = two_variable_input_function(x, y);

            double x_final = -x*sin(theta) + y*cos(theta);
            double y_final = sin(psy) * (-x*cos(theta) - y*sin(theta)) + z*cos(psy);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size) , y_scale(y_final, size)), color));
        }
        window.draw(graph);
        graph.clear();
    }

    for (double y = y_start; y <= y_end; y += length) {
        for (double x = x_start; x <= x_end; x += length) {
            double z = two_variable_input_function(x, y);

            double x_final = -x*sin(theta) + y*cos(theta);
            double y_final = sin(psy) * (-x*cos(theta) - y*sin(theta)) + z*cos(psy);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size) , y_scale(y_final, size)), color));
        }
        window.draw(graph);
        graph.clear();
    }
}


#endif //INC_3DGRAPH_FUNCTION_H
