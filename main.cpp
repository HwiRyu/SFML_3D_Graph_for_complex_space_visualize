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
    sf::VertexArray one(sf::LineStrip);
    sf::VertexArray two(sf::LineStrip);

//    sf::VertexArray parameter(sf::LineStrip);
//    sf::VertexArray parameter_point(sf::LineStrip);

    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Monaco.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::View graphView(sf::FloatRect(-600.0f, -400.0f, 1200.0f, 800.0f));
    window.setView(graphView);

    sf::Text infor_function("", font, 12);
    infor_function.setFillColor(sf::Color::Black);

    sf::Text temporary("", font, 12);
    temporary.setFillColor(sf::Color::Black);

    sf::Text anlges("", font, 12);
    anlges.setFillColor(sf::Color::Black);

    //-----------------------------------------------------------------------------

    //Initialize
    double startX = 0;
    double startY = 0;
    double size = 30;
    double t_value = 0;
    double move_UD = 0;
    double move_RL = 0;
    double x_angle = 20;
    double y_angle = 5;
    const double pi = 3.14159265358979;
    bool complex_type = true;
    bool real_graph_on = false;
    bool domain_fixed = true;

    sf::Clock clock;
    sf::Clock clock_t;

    sf::Time lastClickTime = sf::Time::Zero;
    sf::Vector2i lastMousePos; // 마지막 마우스 위치 저장
    sf::Vector2f startPoint; // 초기 클릭 위치 저장

    // Main loop
    while (window.isOpen()) {
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
                        x_angle += 1;
                        break;
                    case sf::Keyboard::Right:
                        x_angle -= 1;
                        break;
                    case sf::Keyboard::F:
                        if (domain_fixed == true)
                            domain_fixed = false;
                        else
                            domain_fixed = true;
                        break;
                    case sf::Keyboard::I:
                        if (complex_type == true)
                            complex_type = false;
                        else
                            complex_type = true;
                        break;
//                    case sf::Keyboard::T:
//                        tracer = !tracer;  // Toggle tracer when 'T' is pressed
//                        break;
                    case sf::Keyboard::W:
                            size += 5;
                        break;
                    case sf::Keyboard::S:
                            size -= 5;
                        break;
                    case sf::Keyboard::O:
                        if (real_graph_on == true)
                            real_graph_on = false;
                        else
                            real_graph_on = true;
                        break;
                    default:
                        break;
                }
                size = (size < 5) ? 5 : ((size > 150.0) ? 150.0 : size);
            }


            //Choose Initial point in window
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Time currentTime = clock.getElapsedTime();
                    lastMousePos = sf::Mouse::getPosition(window);
                    startPoint = window.mapPixelToCoords(lastMousePos); // 초기 클릭 위치 저장
//                    if (currentTime - lastClickTime < sf::seconds(0.2)) {
//                        startX = x_scale(startPoint.x, 1 / size );
//                        startY = y_scale(startPoint.y, 1 / size);
//                    }
                    lastClickTime = currentTime;
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

                }
            }
        }
//        stepSizeText.setString("Step Size: " + std::to_string(stepSize));

        double x_fmod = graphView.getCenter().x - fmod(graphView.getCenter().x , size);
        double y_fmod =  graphView.getCenter().y - fmod(graphView.getCenter().y, size);
        double x_start = -500 + fmod(500,size) + x_fmod;
        double x_end = 600 + fmod(600,size)+ x_fmod;
        double y_start = -400 + fmod(400,size) + y_fmod;
        double y_end = 400 + fmod(400,size) + y_fmod;

        window.clear(sf::Color::White);

        double psy = pi * y_angle / 120;
        double theta = pi * (x_angle / 120);

        psy = std::fmod(psy, 2 * pi);
        theta = std::fmod(theta, 2 * pi);

        if (psy < 0) {
            psy += 2 * pi;
        }
        if (theta < 0) {
            theta += 2 * pi;
        }


        double view_center_x = graphView.getCenter().x/(size);
        double view_center_y = -graphView.getCenter().y/(size);
        double center_x;
        double center_y;
        double current_center_x;
        double current_center_y;

        center_x = -view_center_x * sin(theta) - cos(theta) * view_center_y / sin(psy);
        center_y = -view_center_x * cos(theta) + sin(theta) * view_center_y / sin(psy);

        if (0.01 * pi < psy && psy < 1.99 * pi && domain_fixed == false) {
            current_center_x = center_x;
            current_center_y = center_y;
        }

        origin_function_one(window, one, size, one_variable_function_complex, current_center_x, current_center_y, x_angle, y_angle, complex_type);

        if (real_graph_on == true)
            origin_function_two(window, two, size, two_variable_real_function, -10, 10, x_angle, y_angle);

        int length_axes = 30 * size;

        sf::VertexArray axe1(sf::Lines);
        axe1.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Red));
        axe1.append(sf::Vertex(sf::Vector2f(-length_axes * std::sin(theta) , length_axes * (std::sin(psy)) * (std::cos(theta))), sf::Color::Red));

        sf::VertexArray axe2(sf::Lines);
        axe2.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe2.append(sf::Vertex(sf::Vector2f(-length_axes * std::cos(theta) , length_axes * (std::sin(psy)) * (-std::sin(theta))), sf::Color::Black));

        sf::VertexArray axe3(sf::Lines);
        axe3.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe3.append(sf::Vertex(sf::Vector2f(length_axes * std::sin(theta), -length_axes * (std::sin(psy)) * (std::cos(theta))), sf::Color::Black));

        sf::VertexArray axe4(sf::Lines);
        axe4.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe4.append(sf::Vertex(sf::Vector2f(length_axes * std::cos(theta) , -length_axes * (std::sin(psy)) * (-std::sin(theta))), sf::Color::Black));

        sf::VertexArray axe5(sf::Lines);
        axe5.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Black));
        axe5.append(sf::Vertex(sf::Vector2f(0.0f, length_axes * (std::cos(psy))), sf::Color::Black));

        sf::VertexArray axe6(sf::Lines);
        axe6.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Red));
        axe6.append(sf::Vertex(sf::Vector2f(0.0f, -length_axes * (std::cos(psy))), sf::Color::Red));

        sf::VertexArray axe_x_dot(sf::Lines);
        for (double i = -30* size; i <= 30 * size; i += 1 * size ) {
            axe_x_dot.append(sf::Vertex(sf::Vector2f(i * std::sin(theta), 10 - i * (std::sin(psy)) * (std::cos(theta))), sf::Color::Black));
            axe_x_dot.append(sf::Vertex(sf::Vector2f(i * std::sin(theta), -10 - i * (std::sin(psy)) * (std::cos(theta))), sf::Color::Black));
        }

        sf::VertexArray axe_y_dot(sf::Lines);
        for (double i = -30* size; i <= 30 * size; i += 1 * size ) {
            axe_y_dot.append(sf::Vertex(sf::Vector2f(i * std::cos(theta), 10 + i * (std::sin(psy)) * (std::sin(theta))), sf::Color::Black));
            axe_y_dot.append(sf::Vertex(sf::Vector2f(i * std::cos(theta), -10 + i * (std::sin(psy)) * (std::sin(theta))), sf::Color::Black));
        }

        sf::VertexArray axe_z_dot(sf::Lines);
        for (double i = -30 * size; i <= 30 * size; i += 1 * size ) {
            axe_y_dot.append(sf::Vertex(sf::Vector2f(-10, i * std::cos(psy)), sf::Color::Black));
            axe_y_dot.append(sf::Vertex(sf::Vector2f(10, i * std::cos(psy)), sf::Color::Black));
        }

        if (complex_type == true)
            infor_function.setString("z = Re(f(x+yi))");
        else
            infor_function.setString("z = Im(f(x+yi))");

        temporary.setString("domain: x = " + std::to_string(center_x) + ", y = " +std::to_string(center_y));
        std::string x_str = std::to_string(std::round(std::stod(std::to_string(theta/pi)) * 100) / 100);
        std::string y_str = std::to_string(std::round(std::stod(std::to_string(psy/pi)) * 100) / 100);

        anlges.setString(x_str + "pi," + y_str + "pi");

        infor_function.setPosition(graphView.getCenter().x + 480, graphView.getCenter().y - 390);
        temporary.setPosition(graphView.getCenter().x + 340, graphView.getCenter().y - 378);
        anlges.setPosition(graphView.getCenter().x + 450, graphView.getCenter().y - 366);



        window.draw(axe1);
        window.draw(axe2);
        window.draw(axe3);
        window.draw(axe4);
        window.draw(axe5);
        window.draw(axe6);
        window.draw(axe_x_dot);
        window.draw(axe_y_dot);
        window.draw(infor_function);
        window.draw(temporary);
        window.draw(anlges);
        window.display();
    }

    return 0;
}