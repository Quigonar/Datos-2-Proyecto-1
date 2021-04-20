#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class GUI{
public:
    //Different rectangles
    RectangleShape codeBackground;
    RectangleShape standardOutput;
    RectangleShape appLog;
    RectangleShape RLV;
    RectangleShape lineHighlight;

    Vector2f vCodeBackground;
    Vector2f vStandardOutput;
    Vector2f vAppLog;
    Vector2f vRLV;

    //Run button
    RectangleShape button;
    Font font;
    Text text;
    Color idleColor;
    Color activeColor;
    int limit = 0;

    GUI()
    {
        vCodeBackground.x = 930;
        vCodeBackground.y = 530;
        codeBackground.setSize(vCodeBackground);
        codeBackground.setPosition(0, 30);
        codeBackground.setFillColor(Color(60,60,60,255));
        codeBackground.setOutlineColor(Color::Black);
        codeBackground.setOutlineThickness(2);

        vStandardOutput.x = 930;
        vStandardOutput.y = 120;
        standardOutput.setSize(vStandardOutput);
        standardOutput.setPosition(0, 560);
        standardOutput.setFillColor(Color(120,120,120,255));
        standardOutput.setOutlineColor(Color::Black);
        standardOutput.setOutlineThickness(2);

        vAppLog.x = 930;
        vAppLog.y = 120;
        appLog.setSize(vAppLog);
        appLog.setPosition(0, 680);
        appLog.setFillColor(Color(40,40,40,255));
        appLog.setOutlineColor(Color::Black);
        appLog.setOutlineThickness(2);

        vRLV.x = 470;
        vRLV.y = 800;
        RLV.setSize(vRLV);
        RLV.setPosition(930, 0);
        RLV.setFillColor(Color(255,255,255,255));
        RLV.setOutlineColor(Color::Black);
        RLV.setOutlineThickness(2);

        button.setPosition(0,0);
        button.setSize(Vector2f(100, 30));
        if (!font.loadFromFile("arial.ttf"))
            text.setFont(font);
        text.setString("RUN");
        text.setFillColor(Color::White);
        text.setCharacterSize(15);
        text.setPosition(40,10);
        idleColor = Color::Blue;
        activeColor = Color::Red;
        button.setFillColor(idleColor);

        lineHighlight.setSize(Vector2f(930, 17));
        lineHighlight.setPosition(0,30);
        lineHighlight.setFillColor(Color(255,255,0,0));


    }

    void Render(RenderWindow* window, const Text& code, const Text& line) const
    {
        window->draw(codeBackground);
        window->draw(code);
        window->draw(line);
        window->draw(standardOutput);
        window->draw(appLog);
        window->draw(RLV);
        window->draw(button);
        window->draw(text);
        window->draw(lineHighlight);
    }

    void lineUpdater(const string& action)
    {
        if (action == "down")
        {
            lineHighlight.setPosition(lineHighlight.getPosition().x, lineHighlight.getPosition().y + 17);
        }
        else if (action == "nothing")
        {
            lineHighlight.setFillColor(Color(255,255,0,150));
        }
    }

    bool update(Vector2f mousePos)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (button.getGlobalBounds().contains(mousePos))
            {
                if (limit == 0)
                {
                    button.setFillColor(activeColor);
                    limit = 1;
                    return true;
                }
            }
        }
        else
        {
            button.setFillColor(idleColor);
            limit = 0;
            return false;
        }
        return false;
    }
};