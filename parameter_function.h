#ifndef INC_3DGRAPH_PARAMETER_FUNCTION_H
#define INC_3DGRAPH_PARAMETER_FUNCTION_H

#include <complex>

struct Point {
    double x;
    double y;
    double z;
};


//Input parameter function, like x = f(t), y = g(t).
Point parameter_function(double t) {
    Point output;
    output.x = cos(t);
    output.y = sin(t);
    output.z = t/10;
    return output;
}


void parameter_function_graph(sf::RenderWindow &window, sf::VertexArray &graph,
                          double size, Point (*parameter_input_function)(double),
                          double x_angle, double y_angle) {
    sf::Color color = sf::Color(255, 0, 255, 255);
    graph.clear();
    Point p;
    double x, y;
    double t_start = 0;
    double t_end = 100;
    double phi = pi * y_angle / 120;
    double theta = pi * x_angle / 120;

    for (double t = t_start; t <= t_end; t += 0.01) {
        p = parameter_input_function(t);
        x = -p.x * sin(theta) + p.y * cos(theta);
        y = sin(phi) * (-p.x * cos(theta) - p.y * sin(theta)) + p.z * cos(phi);
        graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), color));
    }
    window.draw(graph);
}


#endif //INC_3DGRAPH_PARAMETER_FUNCTION_H
