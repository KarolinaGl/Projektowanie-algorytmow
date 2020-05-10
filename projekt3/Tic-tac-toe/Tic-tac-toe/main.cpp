#include <SFML/Graphics.hpp> 
#include <vector>
#include <iostream>
#include "Board.h"

bool isWon(Board* currentBoard, char mark)
{
    int sameMarksCounter = 0;
    int smallerRange = currentBoard->boardSize - currentBoard->winningLineLength + 1;
    for (int i = 0; i < smallerRange; ++i)
    {
        for (int j = 0; j < currentBoard->boardSize; ++j)
        {
            for (int k = 0; k < currentBoard->winningLineLength; ++k)
            {
                if (currentBoard->board[i + k][j] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard->winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }
    
    for (int i = 0; i < currentBoard->boardSize; ++i)
    {
        for (int j = 0; j < smallerRange; ++j)
        {
            for (int k = 0; k < currentBoard->winningLineLength; ++k)
            {
                if (currentBoard->board[i][j + k] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard->winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }
    
    for (int i = 0; i < smallerRange; ++i)
    {
        for (int j = 0; j < smallerRange; ++j)
        {
            for (int k = 0; k < currentBoard->winningLineLength; ++k)
            {
                if (currentBoard->board[i + k][j + k] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard->winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }

    for (int i = 0; i < smallerRange; ++i)
    {
        for (int j = currentBoard->winningLineLength - 1; j < currentBoard->boardSize; ++j)
        {
            for (int k = 0; k < currentBoard->winningLineLength; ++k)
            {
                if (currentBoard->board[i + k][j - k] == mark)
                    sameMarksCounter++;
            }
            if (sameMarksCounter == currentBoard->winningLineLength)
                return true;
            sameMarksCounter = 0;
        }
    }
    return false;
}


int main()
{
    Board* myBoard = new Board(5, 3);
    int boardSize = myBoard->boardSize;
    
    unsigned int windowXSize = 500;
    unsigned int windowYSize = 500;
    float boardXSize = 400;
    float boardYSize = 400;
    float boardXOffset = 50;
    float boardYOffset = 50;
    float markXOffset = 15;
    float markYOffset = 15;

    sf::RenderWindow window(sf::VideoMode(windowXSize, windowYSize), "Tic-tac-toe");
    sf::RectangleShape boardRectangle(sf::Vector2f(boardXSize, boardYSize));
    boardRectangle.setPosition(boardXOffset, boardYOffset);
    boardRectangle.setFillColor(sf::Color::Transparent);
    boardRectangle.setOutlineThickness(5);
    std::vector<sf::RectangleShape> gridLines;
    std::vector<sf::RectangleShape> verticalGridLines;
    std::vector<sf::RectangleShape> horizontalGridLines;

    for (int i = 0; i <= boardSize; ++i)
    {
        sf::RectangleShape verticalLine(sf::Vector2f(boardYSize, 1));
        verticalLine.rotate(90);
        verticalLine.setPosition(i * boardXSize / boardSize + boardXOffset, boardYOffset);
        gridLines.push_back(verticalLine);
        verticalGridLines.push_back(verticalLine);
    }    
    for (int i = 0; i <= boardSize; ++i)
    {
        sf::RectangleShape horizontalLine(sf::Vector2f(boardXSize, 1));
        horizontalLine.setPosition(boardXOffset, i * boardYSize / boardSize + boardYOffset);
        gridLines.push_back(horizontalLine);
        horizontalGridLines.push_back(horizontalLine);
    }

    int clickCounter = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (event.mouseButton.x > boardXOffset && event.mouseButton.x < windowXSize - boardXOffset
                        && event.mouseButton.y > boardYOffset && event.mouseButton.y < windowYSize - boardYOffset)
                    {
                        int row = 0;
                        int column = 0;
                        for (int i = 0; i < boardSize; ++i)
                        {
                            sf::Vector2f verticalLinePosition = verticalGridLines[i].getPosition();
                            if (event.mouseButton.x > verticalLinePosition.x && event.mouseButton.x < verticalLinePosition.x + boardXSize / boardSize)
                                column = i;
                        }
                        for (int i = 0; i < boardSize; ++i)
                        {
                            sf::Vector2f horizontalLinePosition = horizontalGridLines[i].getPosition();
                            if (event.mouseButton.y > horizontalLinePosition.y && event.mouseButton.y < horizontalLinePosition.y + boardYSize / boardSize)
                                row = i;
                        }
                        if (myBoard->board[row][column] == ' ')
                        {
                            clickCounter++;
                            if (clickCounter % 2 == 0)
                            {
                                myBoard->board[row][column] = 'O';
                                if (isWon(myBoard, 'O'))
                                {
                                    std::cout << "O won\n";
                                    return 0;
                                }
                            }
                            else
                            {
                                myBoard->board[row][column] = 'X';
                                if (isWon(myBoard, 'X'))
                                {
                                    std::cout << "X won\n";
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();

        window.draw(boardRectangle);

        for (unsigned int i = 0; i < gridLines.size(); ++i)
            window.draw(gridLines[i]);

        for (int i = 0; i < boardSize; ++i)
        {
            for (int j = 0; j < boardSize; ++j)
            {
                if (myBoard->board[i][j] == 'X')
                {
                    sf::RectangleShape crossMark1(sf::Vector2f((boardXSize / boardSize - 2 * markXOffset) * sqrt(2), 5));
                    crossMark1.setPosition(boardXOffset + j * boardXSize / boardSize + markXOffset, boardYOffset + i * boardYSize / boardSize + markYOffset);
                    crossMark1.rotate(45);
                    sf::RectangleShape crossMark2(sf::Vector2f((boardXSize / boardSize - 2 * markXOffset) * sqrt(2), 5));
                    crossMark2.setPosition(boardXOffset + (j + 1) * boardXSize / boardSize - markXOffset, boardYOffset + i * boardYSize / boardSize + markXOffset);
                    crossMark2.rotate(135);
                    window.draw(crossMark1);
                    window.draw(crossMark2);
                }
                if (myBoard->board[i][j] == 'O')
                {
                    sf::CircleShape circleMark(boardXSize / (2 * boardSize) - markXOffset, 50);
                    circleMark.setPosition(boardXOffset + j * boardXSize / boardSize + markXOffset, boardYOffset + i * boardYSize / boardSize + markXOffset);
                    circleMark.setFillColor(sf::Color::Transparent);
                    circleMark.setOutlineThickness(5);
                    window.draw(circleMark);
                }
            }
        }
        window.display();
    }
    clickCounter = 0;
    
    return 0;
}
