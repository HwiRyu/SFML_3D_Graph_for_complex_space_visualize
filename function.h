#ifndef INC_3DGRAPH_FUNCTION_H
#define INC_3DGRAPH_FUNCTION_H
#include <complex>

const double pi = 3.14159265358979;


double one_variable_function(double x, double y, bool complex_type) {
    std::complex<double> z(x, y);

    //Write one-varable complex function.
    std::complex<double> function_value = exp(z);

    double result;

    if (complex_type == true)
        result = function_value.real();
    else
        result = function_value.imag();

    return result;
}

void origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size, double one_variable_input_function(double, double, bool), double start, double end, double x_angle, double y_angle, bool complex_type) {
    sf::Color transparentRed = sf::Color(0, 0, 255, 100);
    double psy = pi * y_angle / 120;
    double theta = pi * x_angle / 120;
    double length = 0.1;

    for (double x = start; x <= end; x += length) {
        for (double y = start; y <= end; y += length) {
            double z = one_variable_input_function(x, y, complex_type);

            // Adjust the transformed coordinates to fit with the axes
            double x_final = x * std::sin(theta) + y * std::cos(theta);
            double y_final = z * std::cos(psy) + (x * std::cos(theta) - y * std::sin(theta))* std::sin(psy);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size) , y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }
//    axe1.append(sf::Vertex(sf::Vector2f(400 * std::sin(theta) , -400 * (std::sin(psy)) * (std::cos(theta))), sf::Color::Red));

    for (double y = start; y <= end; y += length) {
        for (double x = start; x <= end; x += length) {
            double z = one_variable_input_function(x, y, complex_type);

            // Adjust the transformed coordinates to fit with the axes
            double x_final = x * std::sin(theta) + y * std::cos(theta);
            double y_final = z * std::cos(psy) + (x * std::cos(theta) - y * std::sin(theta))* std::sin(psy);
            graph.append(sf::Vertex(sf::Vector2f(x_scale(x_final, size) , y_scale(y_final, size)), transparentRed));
        }
        window.draw(graph);
        graph.clear();
    }
}
//            double x_transformed = x_scale(x, size);
//            double y_transformed = x_scale(y, size);
//            double z_transformed = y_scale(z, size);

//            double x_final = x * (pow(std::sin(psy),2)-1)  * std::cos(theta) * std::sin(theta) +
//                             y * (pow(std::sin(psy) * std::sin(theta) , 2) + pow(std::cos(theta),2)) +
//                             z * (-std::sin(psy) * std::cos(psy) * std::sin(theta));
//
//            double y_final = x * -std::cos(psy) * std::sin(theta) * std::cos(theta) +
//                             y * -std::sin(psy)*cos(psy)*sin(theta) +
//                             z * pow(std::cos(psy),2);



#endif //INC_3DGRAPH_FUNCTION_H
