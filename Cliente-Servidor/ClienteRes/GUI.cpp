#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class GUI{
public:
    //Different rectangles
    RectangleShape codeBackground, standardOutput, appLog, RLV, lineHighlight;
    Vector2f vCodeBackground, vStandardOutput, vAppLog, vRLV;

    //Buttons
    RectangleShape button;
    RectangleShape button2;

    //ButtonColors
    Color idleColor, idleColor2, activeColor, activeColor2;

    //Booleans to check what is selected
    bool codeBool = false, stdoutBool = false, appLogBool = false;

    int limit = 0;

    GUI()
    {
        //Define the background for the code editing area
        vCodeBackground.x = 930;
        vCodeBackground.y = 530;
        codeBackground.setSize(vCodeBackground);
        codeBackground.setPosition(0, 30);
        codeBackground.setFillColor(Color(60,60,60,255));
        codeBackground.setOutlineColor(Color::Black);
        codeBackground.setOutlineThickness(2);

        //Define the background for the stdout area
        vStandardOutput.x = 930;
        vStandardOutput.y = 230;
        standardOutput.setSize(vStandardOutput);
        standardOutput.setPosition(0, 530);
        standardOutput.setFillColor(Color(120,120,120,255));
        standardOutput.setOutlineColor(Color::Black);
        standardOutput.setOutlineThickness(2);

        //Define the background for the application log area
        vAppLog.x = 930;
        vAppLog.y = 230;
        appLog.setSize(vAppLog);
        appLog.setPosition(0, 760);
        appLog.setFillColor(Color(40,40,40,255));
        appLog.setOutlineColor(Color::Black);
        appLog.setOutlineThickness(2);

        //Define the background for the RAM Live Viewer area
        vRLV.x = 470;
        vRLV.y = 1050;
        RLV.setSize(vRLV);
        RLV.setPosition(930, 0);
        RLV.setFillColor(Color(255,255,255,255));
        RLV.setOutlineColor(Color::Black);
        RLV.setOutlineThickness(2);

        //Define the buttons for running and stopping the code
        button.setPosition(0,0);
        button.setSize(Vector2f(100, 30));
        idleColor = Color::Blue;
        activeColor = Color::Green;
        button.setFillColor(idleColor);
        button2.setPosition(120, 0);
        button2.setSize(Vector2f (100, 30));
        idleColor2 = Color::Red;
        activeColor2 = Color::Blue;
        button2.setFillColor(idleColor2);

        //Define the line highlighter
        lineHighlight.setSize(Vector2f(930, 17));
        lineHighlight.setPosition(0,30);
        lineHighlight.setFillColor(Color(255,255,0,0));


    }

    //Define function to draw all the different areas to the window
    void Render(RenderWindow* window, const Text& code, const Text& line, const Font& font, const Text& terminal) const
    {
        Text text, text2;
        text.setString("RUN");
        text.setFillColor(Color::White);
        text.setCharacterSize(15);
        text.setPosition(35,5);
        text.setFont(font);
        text2.setString("STOP");
        text2.setFillColor(Color::White);
        text2.setCharacterSize(15);
        text2.setPosition(155, 5);
        text2.setFont(font);
        window->draw(codeBackground);
        window->draw(code);
        window->draw(line);
        window->draw(standardOutput);
        window->draw(terminal);
        window->draw(appLog);
        window->draw(RLV);
        window->draw(button);
        window->draw(button2);
        window->draw(text);
        window->draw(text2);
        window->draw(lineHighlight);
    }

    //Define function that returns a boolean to highlight the line code
    bool lineUpdater(const string& action)
    {
        if (action == "down" && lineHighlight.getPosition().y < 421)
        {
            lineHighlight.setPosition(lineHighlight.getPosition().x, lineHighlight.getPosition().y + 17);
        }
        else if (action == "down" && lineHighlight.getPosition().y >= 421)
        {
            return true;
        }
        else if (action == "nothing")
        {
            lineHighlight.setFillColor(Color(255,255,0,150));
        }
        else if (action == "erase")
        {
            lineHighlight.setFillColor(Color(255, 255, 0, 0));
        }
        return false;
    }

    //Define function to check for presses in the buttons or backgrounds
    int update(Vector2f mousePos)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            //Check if its the run button
            if (button.getGlobalBounds().contains(mousePos))
            {
                if (limit == 0)
                {
                    button.setFillColor(activeColor);
                    limit = 1;
                    return 1;
                }
            }
            //Check if its the stop button
            else if (button2.getGlobalBounds().contains(mousePos))
            {
                if (limit == 0)
                {
                    button2.setFillColor(activeColor2);
                    limit = 1;
                    lineUpdater("erase");
                    lineHighlight.setPosition(lineHighlight.getPosition().x, 30);
                    return 2;
                }
            }
            //Check if its the code background
            else if (codeBackground.getGlobalBounds().contains(mousePos))
            {
                if (limit == 0)
                {
                    limit = 1;
                    codeBool = true;
                    stdoutBool = false;
                    appLogBool = false;
                }
            }
            //Check if its the stdout background
            else if (standardOutput.getGlobalBounds().contains(mousePos))
            {
                if (limit == 0)
                {
                    limit = 1;
                    stdoutBool = true;
                    codeBool = false;
                }
            }
            //Check if its the application log background
            else if (appLog.getGlobalBounds().contains(mousePos))
            {
                if (limit == 0)
                {
                    limit = 1;
                    appLogBool = true;
                    stdoutBool = false;
                    codeBool = false;
                }
            }
        }
        else
        {
            button.setFillColor(idleColor);
            button2.setFillColor(idleColor2);
            limit = 0;
            return 0;
        }
        return false;
    }
};