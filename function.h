//
// Created by Persist on 2/18/24.
//

#ifndef INC_3DGRAPH_FUNCTION_H
#define INC_3DGRAPH_FUNCTION_H
const double pi = 3.14159265358979;

double one_variable_function(double x) {
    return 0;
}

void origin_function_one(sf::RenderWindow& window, sf::VertexArray& graph, double size, double one_variable_input_function(double), double start, double end, double x_angle,  double y_angle) {
    graph.clear();
    for (double x = start/size; x <= end/size; x += 0.001) {
        double y = one_variable_input_function(x / std::cos(pi * x_angle / 50)) * std::cos(pi * y_angle / 50);
        graph.append(sf::Vertex(sf::Vector2f(x_scale(x, size), y_scale(y, size)), sf::Color::Red));
    }
    window.draw(graph);
}

#endif //INC_3DGRAPH_FUNCTION_H
