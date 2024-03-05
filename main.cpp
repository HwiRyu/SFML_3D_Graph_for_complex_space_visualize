#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include "scale.h"
#include "function.h"
#include "complex_function.h"
#include "parameter_function.h"

int main() {
    // Window initial setting-------------------------------------------------------
    const int width = 1200;
    const int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "3D Graph");

    //일변수 복소함수, 이변수 실함수
    sf::VertexArray one(sf::LineStrip);
    sf::VertexArray two(sf::LineStrip);
    sf::VertexArray three(sf::LineStrip);


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
    double size = 30;
    double x_angle = 20;
    double y_angle = 5;
    const double pi = 3.14159265358979;
    bool complex_type = true;
    bool complex_graph_on = true;
    bool real_graph_on = false;
    bool domain_fixed = true;
    int complex_swich = 0;

    sf::Clock clock;
    sf::Clock clock_t;

    sf::Time lastClickTime = sf::Time::Zero;
    sf::Vector2i lastMousePos;
    sf::Vector2f startPoint;

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
                        if (domain_fixed)
                            domain_fixed = false;
                        else
                            domain_fixed = true;
                        break;
                    case sf::Keyboard::I:
                        complex_swich += 1;
                        break;
                    case sf::Keyboard::W:
                            size += 5;
                        break;
                    case sf::Keyboard::S:
                            size -= 5;
                        break;
                    case sf::Keyboard::O:
                        if (real_graph_on)
                            real_graph_on = false;
                        else
                            real_graph_on = true;



                        break;
                    default:
                        break;
                }
                size = (size < 5) ? 5 : ((size > 200.0) ? 200.0 : size);
            }


            //Choose Initial point in window
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Time currentTime = clock.getElapsedTime();
                    lastMousePos = sf::Mouse::getPosition(window);
                    startPoint = window.mapPixelToCoords(lastMousePos); // 초기 클릭 위치 저장
                    lastClickTime = currentTime;
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i newMousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f delta = window.mapPixelToCoords(newMousePos) - window.mapPixelToCoords(lastMousePos);
                    graphView.move(-delta); // 시야 이동
                    window.setView(graphView); // 뷰 설정 업데이트
                    lastMousePos = newMousePos; // 새로운 마우스 위치 저장

                }
            }
        }

        if (complex_swich > 2) {
            complex_swich = 0;
        }

        switch(complex_swich) {
            case 0:
                complex_graph_on = true;
                complex_type = true;
                break;
            case 1:
                complex_graph_on = true;
                complex_type = false;
                break;
            case 2:
                complex_graph_on = false;
                break;
        }



            window.clear(sf::Color::White);

        //시야각
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
        double center_x = -view_center_x * sin(theta) - cos(theta) * view_center_y / sin(psy);
        double center_y = view_center_x * cos(theta) - sin(theta) * view_center_y / sin(psy);
        double current_center_x;
        double current_center_y;

        if (0.01 * pi < psy && psy < 1.99 * pi && !domain_fixed) {
            current_center_x = center_x;
            current_center_y = center_y;
        }
//Graph Show
        if (complex_graph_on)
            origin_function_one(window, one, size, one_variable_function_complex, current_center_x, current_center_y, x_angle, y_angle, complex_type);
        if (real_graph_on)
            origin_function_two(window, two, size, two_variable_real_function, current_center_x, current_center_y, x_angle, y_angle);
        parameter_function_graph(window, three, size, parameter_function, x_angle, y_angle);

        int length_axes = 30 * size;

        sf::VertexArray axe1(sf::Lines);
        axe1.append(sf::Vertex(sf::Vector2f(0.0f, 0.0f), sf::Color::Green));
        axe1.append(sf::Vertex(sf::Vector2f(-length_axes * std::sin(theta) , length_axes * (std::sin(psy)) * (std::cos(theta))), sf::Color::Green));

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

        if (complex_type)
            infor_function.setString("z = Re(f(x+yi))");
        else
            infor_function.setString("z = Im(f(x+yi))");
        if (!complex_graph_on)
            infor_function.setString("None");
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