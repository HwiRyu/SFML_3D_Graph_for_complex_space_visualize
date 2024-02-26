#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "scale.h"
#include "function.h"

int main() {
    // Window initial setting-------------------------------------------------------
    const int width = 1200;
    const int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "3D Graph");
//    sf::VertexArray EulerGraph(sf::LineStrip);
    sf::VertexArray origin(sf::LineStrip);
//    sf::VertexArray parameter(sf::LineStrip);
//    sf::VertexArray parameter_point(sf::LineStrip);

    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Monaco.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::View graphView(sf::FloatRect(-600.0f, -400.0f, 1200.0f, 800.0f));
    window.setView(graphView);
//
//    sf::Text stepSizeText("", font, 12);
//    stepSizeText.setPosition(300, -388);
//    stepSizeText.setFillColor(sf::Color::Black);
//
//    sf::Text initial_point("", font, 12);
//    initial_point.setPosition(300, -400);
//    initial_point.setFillColor(sf::Color::Black);
//
//    sf::Text tracer_on("", font, 12);
//    tracer_on.setPosition(300, -364);
//    tracer_on.setFillColor(sf::Color::Black);
//
//    sf::Text current_t_value("", font, 12);
//    current_t_value.setPosition(300, -376);
//    current_t_value.setFillColor(sf::Color::Black);

    //-----------------------------------------------------------------------------

    //Initialize
    double startX = 0;
    double startY = 0;
    double size = 30;
    double step = -3.50;
    double stepSize = 0.03;  // Initialize stepSize
    bool tracer = false;
    float xValue;
    float yValue;
    double t_value = 0;
    double move_UD = 0;
    double move_RL = 0;
    double x_angle = 0;
    double y_angle = 0;
    const double pi = 3.14159265358979;

    sf::Clock clock;
    sf::Clock clock_t;

    sf::Time lastClickTime = sf::Time::Zero;
    sf::Vector2i lastMousePos; // 마지막 마우스 위치 저장
    sf::Vector2f startPoint; // 초기 클릭 위치 저장
    sf::Time elapsedTime;
    bool increaseValue = false;

    // Main loop
    while (window.isOpen()) {
        elapsedTime = clock_t.getElapsedTime();
        if (increaseValue && elapsedTime.asSeconds() >= 0.001f) {
            t_value += 0.001f; // 간격을 1초로 변경함
            clock_t.restart();
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            //In euler_method, control step size.
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        y_angle -= 1;
                        break;
                    case sf::Keyboard::Down:
                        y_angle += 1;
                        break;
                    case sf::Keyboard::Left:
                        x_angle -= 1;
                        break;
                    case sf::Keyboard::Right:
                        x_angle += 1;
                        break;
                    case sf::Keyboard::W:
                        if (!tracer)
                            size += 5;
                        break;
                    case sf::Keyboard::S:
                        if (!tracer)
                            size -= 5;
                        break;
//                    case sf::Keyboard::T:
//                        tracer = !tracer;  // Toggle tracer when 'T' is pressed
//                        break;
                    case sf::Keyboard::Q:
                        if (!tracer)
                            t_value -= 0.01;
                        break;
                    case sf::Keyboard::E:
                        if (!tracer)
                            t_value += 0.01;
                        break;
                    case sf::Keyboard::R:
                        //Initialize
                        startX = 0;
                        startY = 0;
                        size = 30;
                        step = -3.50;
                        stepSize = 0.03;  // Initialize stepSize
                        tracer = false;
                        xValue = 0;
                        yValue = 0;
                        t_value = 0;
                        increaseValue = true;
                        window.display();
                        window.clear();

                    case sf::Keyboard::F:
                        if (!tracer)
                            if (!increaseValue)
                                increaseValue = true;
                            else
                                increaseValue = false;
                        break;

//                    case sf::Keyboard::Up:
//                        if (!tracer)
//                            move_UD += 1;
//                        break;
//                    case sf::Keyboard::Down:
//                        if (!tracer)
//                            move_UD -= 1;
//                        break;
//                    case sf::Keyboard::Right:
//                        if (!tracer)
//                            move_RL += 1;
//                        break;
//                    case sf::Keyboard::Left:
//                        if (!tracer)
//                            move_RL -= 1;
//                        break;
                    default:
                        break;
                }
                if (step <= 0) {
                    stepSize = std::exp(step);
                } else {
                    stepSize = std::max(step * 1 + 1.0, 1.0);
                }
                if (stepSize <= 0.001)
                    step = -6.90;
                size = (size < 5) ? 5 : ((size > 150.0) ? 150.0 : size);

            }


            //Choose Initial point in window
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Time currentTime = clock.getElapsedTime();
                    lastMousePos = sf::Mouse::getPosition(window);
                    startPoint = window.mapPixelToCoords(lastMousePos); // 초기 클릭 위치 저장
                    if (currentTime - lastClickTime < sf::seconds(0.2)) {
                        startX = x_scale(startPoint.x, 1 / size );
                        startY = y_scale(startPoint.y, 1 / size);
                    }
                    lastClickTime = currentTime;
//                    if (-10000000 <=origin_function_parameter(window, parameter, size, parameter_function, t_value, x_scale(startPoint.x, 1 / size), y_scale(startPoint.y, 1 / size)))
//                        t_value = origin_function_parameter(window, parameter, size, parameter_function, t_value, x_scale(startPoint.x, 1 / size), y_scale(startPoint.y, 1 / size));
                }
            }

//            size *= std::cos(x_angle);

            if (event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f delta = window.mapPixelToCoords(newMousePos) - window.mapPixelToCoords(lastMousePos);
                    graphView.move(-delta); // 시야 이동
                    window.setView(graphView); // 뷰 설정 업데이트
                    lastMousePos = newMousePos; // 새로운 마우스 위치 저장

//                    stepSizeText.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 388);
//                    initial_point.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 400);
//                    current_t_value.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 376);
//                    tracer_on.setPosition(graphView.getCenter().x + 300, graphView.getCenter().y - 364);

                }
            }
        }
//        stepSizeText.setString("Step Size: " + std::to_string(stepSize));
//        initial_point.setString("Initial value: x =" + std::to_string(startX) + ", y =" + std::to_string(startY));
//        tracer_on.setString("Tracer mode On");
//        current_t_value.setString("t = "+ std::to_string(t_value));

        double x_fmod = graphView.getCenter().x - fmod(graphView.getCenter().x , size);
        double y_fmod =  graphView.getCenter().y - fmod(graphView.getCenter().y, size);
        double x_start = -500 + fmod(500,size) + x_fmod;
        double x_end = 600 + fmod(600,size)+ x_fmod;
        double y_start = -400 + fmod(400,size) + y_fmod;
        double y_end = 400 + fmod(400,size) + y_fmod;




        window.clear(sf::Color::White);
//        // Clear the window
//        if (!tracer){
//            window.clear(sf::Color::White);
//            window.draw(stepSizeText);
//            window.draw(initial_point);
//            window.draw(current_t_value);
//        }
//        else {
//            window.draw(tracer_on);
//        }

        origin_function_one(window, origin, size, one_variable_function, x_start, x_end, x_angle, y_angle);
//
//        sf::VertexArray axes(sf::Lines);
//
//        axes.append(sf::Vertex(sf::Vector2f(-(600.0f - graphView.getCenter().x), 0.0f), sf::Color::Black));
//        axes.append(sf::Vertex(sf::Vector2f(600.0f + graphView.getCenter().x, 0.0f), sf::Color::Black));
//        axes.append(sf::Vertex(sf::Vector2f(0.0f, -400.0f + graphView.getCenter().y), sf::Color::Black));
//        axes.append(sf::Vertex(sf::Vector2f(0.0f, 400.0f + graphView.getCenter().y), sf::Color::Black));
//
////        axes.append(sf::Vertex(sf::Vector2f(131.0f, std::sin(pi) * (400.0f + graphView.getCenter().y)), sf::Color::Black));
//
//        double neo_x = abs(size * (std::cos(pi * x_angle / 50)));
//        double neo_y = abs(size * (std::cos(pi * y_angle / 50)));
//
//
//        if (neo_x > 0.01)
//            for (double i = 0; i <= x_end; i += neo_x) {
//                axes.append(sf::Vertex(sf::Vector2f( i, -3), sf::Color::Black));
//                axes.append(sf::Vertex(sf::Vector2f(i, 3), sf::Color::Black));
//            }
//
//
//        if (neo_y > 0.01)
//            for (double i = 0; i >= -y_end; i -= neo_y) {
//                axes.append(sf::Vertex(sf::Vector2f(-3,i), sf::Color::Black));
//                axes.append(sf::Vertex(sf::Vector2f(3,i), sf::Color::Black));
//            }
//
//        window.draw(axes);

        sf::VertexArray axe1(sf::Lines);
        axe1.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe1.append(sf::Vertex(sf::Vector2f(400 * std::sin(pi * x_angle / 50) , 400 * (std::sin(pi * y_angle / 50)) * (std::cos(pi * x_angle / 50))), sf::Color::Black));

        sf::VertexArray axe2(sf::Lines);
        axe2.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe2.append(sf::Vertex(sf::Vector2f(400 * std::cos(pi * x_angle / 50) , 400 * (std::sin(pi * y_angle / 50)) * (std::sin(-pi * x_angle / 50))), sf::Color::Black));

        sf::VertexArray axe3(sf::Lines);
        axe3.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe3.append(sf::Vertex(sf::Vector2f(-400 * std::sin(pi * x_angle / 50), -400 * (std::sin(pi * y_angle / 50)) * (std::cos(pi * x_angle / 50))), sf::Color::Red));

        sf::VertexArray axe4(sf::Lines);
        axe4.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe4.append(sf::Vertex(sf::Vector2f(-400 * std::cos(pi * x_angle / 50) , -400 * (std::sin(pi * y_angle / 50)) * (std::sin(-pi * x_angle / 50))), sf::Color::Black));

        sf::VertexArray axe5(sf::Lines);
        axe5.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe5.append(sf::Vertex(sf::Vector2f(0.0f, 400 * (std::cos(pi * y_angle / 50))), sf::Color::Black));

        sf::VertexArray axe6(sf::Lines);
        axe6.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe6.append(sf::Vertex(sf::Vector2f(0.0f, -400 * (std::cos(pi * y_angle / 50))), sf::Color::Black));

        window.draw(axe1);
        window.draw(axe2);
        window.draw(axe3);
        window.draw(axe4);

        window.draw(axe5);
        window.draw(axe6);

        // Display the contents of the window
        window.display();
    }

    return 0;
}