#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class GUI{
public:
    //Different rectangles
    RectangleShape codeBackground, standardOutput, appLog, RLV, lineHighlight;
    RectangleShape RLVline1, RLVline2, RLVline3, RLVline4, RLVline5, RLVline6, RLVline7, RLVline8, RLVline9,
                    RLVline10, RLVline11, RLVline12, RLVline13, RLVline14, RLVline15, RLVline16, RLVline17;
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
        vRLV.x = 780;
        vRLV.y = 1050;
        RLV.setSize(vRLV);
        RLV.setPosition(930, 0);
        RLV.setFillColor(Color(255,255,255,255));
        RLV.setOutlineColor(Color::Black);
        RLV.setOutlineThickness(2);

        //Define the RAM Live Viewer grid
        RLVline1.setSize(Vector2f(5, 1050));
        RLVline1.setFillColor(Color::Black);
        RLVline1.setPosition(1150, 35);

        RLVline2.setSize(Vector2f(5, 1050));
        RLVline2.setFillColor(Color::Black);
        RLVline2.setPosition(1370, 35);

        RLVline3.setSize(Vector2f(5, 1050));
        RLVline3.setFillColor(Color::Black);
        RLVline3.setPosition(1495, 35);

        RLVline4.setSize(Vector2f(780, 91));
        RLVline4.setFillColor(Color(0,0,0,0));
        RLVline4.setOutlineColor(Color::Black);
        RLVline4.setOutlineThickness(2);
        RLVline4.setPosition(930, 35);

        RLVline5.setSize(Vector2f(780, 91));
        RLVline5.setFillColor(Color(0,0,0,0));
        RLVline5.setOutlineColor(Color::Black);
        RLVline5.setOutlineThickness(2);
        RLVline5.setPosition(930, 80.5);

        RLVline6.setSize(Vector2f(780, 91));
        RLVline6.setFillColor(Color(0,0,0,0));
        RLVline6.setOutlineColor(Color::Black);
        RLVline6.setOutlineThickness(2);
        RLVline6.setPosition(930, 173.5);

        RLVline7.setSize(Vector2f(780, 91));
        RLVline7.setFillColor(Color(0,0,0,0));
        RLVline7.setOutlineColor(Color::Black);
        RLVline7.setOutlineThickness(2);
        RLVline7.setPosition(930, 219);

        RLVline8.setSize(Vector2f(780, 91));
        RLVline8.setFillColor(Color(0,0,0,0));
        RLVline8.setOutlineColor(Color::Black);
        RLVline8.setOutlineThickness(2);
        RLVline8.setPosition(930, 312);

        RLVline9.setSize(Vector2f(780, 91));
        RLVline9.setFillColor(Color(0,0,0,0));
        RLVline9.setOutlineColor(Color::Black);
        RLVline9.setOutlineThickness(2);
        RLVline9.setPosition(930, 357.5);

        RLVline10.setSize(Vector2f(780, 91));
        RLVline10.setFillColor(Color(0,0,0,0));
        RLVline10.setOutlineColor(Color::Black);
        RLVline10.setOutlineThickness(2);
        RLVline10.setPosition(930, 450.5);

        RLVline11.setSize(Vector2f(780, 93));
        RLVline11.setFillColor(Color(0,0,0,0));
        RLVline11.setOutlineColor(Color::Black);
        RLVline11.setOutlineThickness(2);
        RLVline11.setPosition(930, 498);

        RLVline12.setSize(Vector2f(780, 91));
        RLVline12.setFillColor(Color(0,0,0,0));
        RLVline12.setOutlineColor(Color::Black);
        RLVline12.setOutlineThickness(2);
        RLVline12.setPosition(930, 593);

        RLVline13.setSize(Vector2f(780, 91));
        RLVline13.setFillColor(Color(0,0,0,0));
        RLVline13.setOutlineColor(Color::Black);
        RLVline13.setOutlineThickness(2);
        RLVline13.setPosition(930, 638.5);

        RLVline14.setSize(Vector2f(780, 91));
        RLVline14.setFillColor(Color(0,0,0,0));
        RLVline14.setOutlineColor(Color::Black);
        RLVline14.setOutlineThickness(2);
        RLVline14.setPosition(930, 731.5);

        RLVline15.setSize(Vector2f(780, 91));
        RLVline15.setFillColor(Color(0,0,0,0));
        RLVline15.setOutlineColor(Color::Black);
        RLVline15.setOutlineThickness(2);
        RLVline15.setPosition(930, 777);

        RLVline16.setSize(Vector2f(780, 91));
        RLVline16.setFillColor(Color(0,0,0,0));
        RLVline16.setOutlineColor(Color::Black);
        RLVline16.setOutlineThickness(2);
        RLVline16.setPosition(930, 870);

        RLVline17.setSize(Vector2f(780, 91));
        RLVline17.setFillColor(Color(0,0,0,0));
        RLVline17.setOutlineColor(Color::Black);
        RLVline17.setOutlineThickness(2);
        RLVline17.setPosition(930, 917.5);

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
    void Render(RenderWindow* window, const Text& code, const Text& line, const Font& font, const Text& terminal, const Text& appLogT, const Text& RLVAddr,
                const Text& RLVVal, const Text& RLVVar, const Text& RLVRef) const
    {
        Text text, text2, RLVT;
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
        RLVT.setString("RAM LIVE VIEWER");
        RLVT.setFillColor(Color::Black);
        RLVT.setCharacterSize(20);
        RLVT.setPosition(940, 5);
        RLVT.setFont(font);
        window->draw(codeBackground);
        window->draw(code);
        window->draw(line);
        window->draw(standardOutput);
        window->draw(terminal);
        window->draw(appLog);
        window->draw(appLogT);
        window->draw(RLV);
        window->draw(RLVT);
        window->draw(RLVAddr);
        window->draw(RLVVal);
        window->draw(RLVVar);
        window->draw(RLVRef);
        window->draw(RLVline1);
        window->draw(RLVline2);
        window->draw(RLVline3);
        window->draw(RLVline4);
        window->draw(RLVline5);
        window->draw(RLVline6);
        window->draw(RLVline7);
        window->draw(RLVline8);
        window->draw(RLVline9);
        window->draw(RLVline10);
        window->draw(RLVline11);
        window->draw(RLVline12);
        window->draw(RLVline13);
        window->draw(RLVline14);
        window->draw(RLVline15);
        window->draw(RLVline16);
        window->draw(RLVline17);
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