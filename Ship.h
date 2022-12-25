#ifndef CLASS_SHIP_H
#define CLASS_SHIP_H

#include "includes.h"

class Ship
{

private:
    int X_, Y_;
    int nDecks_;
    bool horizontal_;
    bool alive_;
public:
    Ship() { X_ = 26, Y_ = 0, nDecks_ = 3, horizontal_ = 0, alive_ = 1; }
    class Player;
    void setShips();
    int getX() { return X_; }
    int getY() { return Y_; }
    void changeDirection(int horizontal) { horizontal_ = horizontal; }
    int isHorizontal() { return horizontal_; }
    bool isAlive() { return alive_; }
    void changeAlive(bool alive) { alive_ = alive; }
    int getDecksNum() { return nDecks_; }
};

class Ship::Player //  ласс дл€ создани€ двух игроков (себ€ и противника)
{
private:
    std::vector<std::vector<int>> closedNums;

    int isClosed(int X, int Y)
    {
        for (auto closedNum : closedNums)
        {
            if (closedNum[0] == X && closedNum[1] == Y) { return 1; }
        }
        return 0;
    }
public:
    std::vector<std::vector<int>>              nextAttack;
    std::vector<std::vector<std::vector<int>>> allShipsCoords;
    std::vector<std::vector<int>>              shipsPosInArr;
    std::vector<std::vector<int>>              missZones;
    std::vector<std::vector<int>>              hits;
    std::vector<std::vector<int>>              smartField;
    Ship ships[10];

    void defShipsArr()
    {
        shipsPosInArr.resize(12);
        for (int i = 0; i < shipsPosInArr.size(); ++i) { shipsPosInArr[i].resize(24); std::fill(shipsPosInArr[i].begin(), shipsPosInArr[i].end(), 0); }
    }

    bool isDestroyed(int X, int Y)
    {
        int isDestroyed = 0;
        for (auto hit : hits)
        {
            if (hit[0] == X && hit[1] == Y) { ++isDestroyed; }
        }
        for (auto miss : missZones)
        {
            if (miss[0] == X && miss[1] == Y) { ++isDestroyed; }
        }
        return isDestroyed;
    }

    void showField(int X, int Y, std::string player)
    {
        int extraX = X, extraY = Y;
        setCursor(extraX, extraY);
        setColor((player == "me") ? Color::GREEN : Color::RED, (player == "me") ? Color::GREEN : Color::RED);
        for (int i = 0; i < 12; ++i) { std::cout << "++"; }
        setColor(Color::WHITE, (player == "me") ? Color::GREEN : Color::RED);
        for (char i = 65; i < 75; ++i) { setCursor(++(++extraX), 0); std::cout << (char)i; }
        extraX = X, extraY = Y;
        setCursor(extraX, ++extraY);
        for (int y = 0; y < 10; ++y)
        {
            setColor((player == "me") ? Color::GREEN : Color::RED, (player == "me") ? Color::GREEN : Color::RED); if (y + 1 != 10) { std::cout << "+"; } setColor(Color::WHITE, (player == "me") ? Color::GREEN : Color::RED), std::cout << y + 1, setColor(Color::WHITE, Color::WHITE);
            for (int i = 0; i < 10; ++i) { std::cout << "++"; }
            setColor((player == "me") ? Color::GREEN : Color::RED, (player == "me") ? Color::GREEN : Color::RED); std::cout << "++";
            setCursor(extraX, ++extraY);
        }
        for (int i = 0; i < 12; ++i) { std::cout << "++"; }
        setCursor(extraX, ++extraY);

        if (player == "me")
        {
            setColor(Color::BLACK, Color::BLACK);
            for (int i = 0; i < 12; ++i)
            {
                for (int j = 0; j < 24; ++j)
                {
                    if (shipsPosInArr[i][j] == 1)
                    {
                        setCursor(X + j, Y + i);
                        std::cout << "+";
                    }
                }
            }
        }
        setCursor(0, 15);
        setColor(Color::WHITE, Color::BLACK);
    }

    int setDecksNum(int nDecks)
    {
        if (nDecks > 5) { return 1; }
        else if (nDecks > 2) { return 2; }
        else if (nDecks > 0) { return 3; }
        else { return 4; }
    }

    void setShips()
    {
        int nDecks{};
        for (int i = 0; i < 10; ++i)
        {
            showField(0, 0, "me");
            short X = 2, Y = 1;
            nDecks = setDecksNum(i);
            int accept = 0;
            setColor(Color::DARKGRAY, Color::DARKGRAY);
            for (int j = 0; j < nDecks; ++j)
            {
                ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j);
                std::cout << "++";
            }
            int key = _getch();
            do
            {
                int key = _getch();
                showField(0, 0, "me");
                switch (key)
                {
                case Keys::UP:
                    if (Y > 1)
                    {
                        setColor(Color::WHITE, Color::WHITE);
                        for (int j = 0; j < nDecks; ++j) { ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j), std::cout << "++"; }
                        --Y;
                    }
                    break;
                case Keys::DOWN:
                    if (Y < ((ships[i].isHorizontal()) ? (10) : (11 - nDecks)))
                    {
                        setColor(Color::WHITE, Color::WHITE);
                        for (int j = 0; j < nDecks; ++j) { ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j), std::cout << "++"; }
                        ++Y;
                    }
                    break;
                case Keys::LEFT:
                    if (X > 2)
                    {
                        setColor(Color::WHITE, Color::WHITE);
                        for (int j = 0; j < nDecks; ++j) { ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j), std::cout << "++"; }
                        X -= 2;
                    }
                    break;
                case Keys::RIGHT:
                    if (X < (ships[i].isHorizontal() ? (22 - nDecks * 2) : 20))
                    {
                        setColor(Color::WHITE, Color::WHITE);
                        for (int j = 0; j < nDecks; ++j) { ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j), std::cout << "++"; }
                        X += 2;
                    }
                    break;
                case Keys::R:
                    if ((ships[i].isHorizontal() && (Y + nDecks - 1 < 11)) || (!ships[i].isHorizontal() && (X + nDecks * 2 - 1 < 22)))
                    {
                        ships[i].changeDirection(!ships[i].isHorizontal());
                        setColor(Color::WHITE, Color::WHITE);
                        for (int j = 0; j < nDecks; ++j) { !ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j), std::cout << "++"; }
                    }
                    break;
                case Keys::ENTER:
                    int counter = 0;
                    for (int j = 0; j < nDecks; ++j)
                    {
                        if (isClosed(ships[i].isHorizontal() ? X + j * 2 : X, ships[i].isHorizontal() ? Y : Y + j))
                        {
                            ++counter;
                        }
                    }
                    if (counter == 0)
                    {
                        ++accept;
                        for (int j = (Y - 1); j < Y - 1 + (ships[i].horizontal_ ? 3 : nDecks + 2); ++j)
                        {
                            for (int z = (X - 2); z < X - 2 + (ships[i].horizontal_ ? nDecks + 2 : 3) * 2; ++z)
                            {
                                std::vector<int> coords;
                                coords.push_back(z), coords.push_back(j);
                                closedNums.push_back(coords);
                            }
                        }
                    }
                    break;
                }
                showField(0, 0, "me");
                setColor(Color::DARKGRAY, Color::DARKGRAY);
                for (int j = 0; j < nDecks; ++j) { ships[i].isHorizontal() ? setCursor(X + j * 2, Y) : setCursor(X, Y + j), std::cout << "++"; }
            } while (accept < 1);
            ships[i].X_ = X, ships[i].Y_ = Y, ships[i].nDecks_ = nDecks;
            for (int j = 0; j < (ships[i].horizontal_ ? ships[i].nDecks_ * 2 : ships[i].nDecks_); ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    shipsPosInArr[ships[i].isHorizontal() ? ships[i].getY() : ships[i].getY() + j][ships[i].isHorizontal() ? ships[i].getX() + j : ships[i].getX() + k] = 1;
                }
            }
        }
        allShipsCoords.resize(10);
        for (int i = 0; i < 10; ++i)
        {
            if (ships[i].nDecks_ == 4) { allShipsCoords[i].resize(4); }
            else if (ships[i].nDecks_ == 3) { allShipsCoords[i].resize(3); }
            else if (ships[i].nDecks_ == 2) { allShipsCoords[i].resize(2); }
            else { allShipsCoords[i].resize(1); }
            for (int j = 0; j < (ships[i].horizontal_ ? ships[i].nDecks_ * 2 : ships[i].nDecks_); ships[i].horizontal_ ? (j += 2) : ++j)
            {
                std::vector<int> coords;
                coords.push_back(ships[i].horizontal_ ? ships[i].getX() + j : ships[i].getX()), coords.push_back(ships[i].horizontal_ ? ships[i].getY() : ships[i].getY() + j);
                allShipsCoords[i].push_back(coords);
            }
        }
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < allShipsCoords[i].size(); ++j)
            {
                if (allShipsCoords[i][j].empty())
                {
                    allShipsCoords[i].erase(allShipsCoords[i].begin() + j);
                    --j;
                }
            }
        }
        setColor(Color::WHITE, Color::BLACK);
    }

    void setShipsWithBot(std::string player)
    {
        for (int k = 0; k < 10; ++k)
        {
            ships[k].nDecks_ = setDecksNum(k);
            ships[k].horizontal_ = rand() % 2;
            ships[k].Y_ = ships[k].horizontal_ ? 1 + rand() % 10 : 1 + rand() % (10 - ships[k].nDecks_);
            ships[k].X_ = ships[k].horizontal_ ? (2 + rand() % (10 - ships[k].nDecks_)) * 2 : (1 + rand() % 10) * 2;
            int counter = 0;
            for (int i = ships[k].Y_; i < ships[k].Y_ + (ships[k].isHorizontal() ? 1 : ships[k].nDecks_); ++i)
            {
                for (int j = ships[k].X_; j < ships[k].X_ + (ships[k].isHorizontal() ? ships[k].nDecks_ * 2 : 2); ++j)
                {
                    if (isClosed(j, i)) { ++counter; }
                }
            }
            if (counter != 0) { --k; }
            else
            {
                for (int i = (ships[k].Y_ - 1); i < ships[k].Y_ - 1 + (ships[k].horizontal_ ? 3 : ships[k].nDecks_ + 2); ++i)
                {
                    for (int j = (ships[k].X_ - 2); j < ships[k].X_ - 2 + (ships[k].horizontal_ ? ships[k].nDecks_ + 2 : 3) * 2; ++j)
                    {
                        std::vector<int> coords;
                        coords.push_back(j), coords.push_back(i);
                        closedNums.push_back(coords);
                    }
                }
                for (int i = ships[k].Y_; i < ships[k].Y_ + (ships[k].isHorizontal() ? 1 : ships[k].nDecks_); ++i)
                {
                    for (int j = ships[k].X_; j < ships[k].X_ + (ships[k].isHorizontal() ? ships[k].nDecks_ * 2 : 2); ++j)
                    {
                        shipsPosInArr[i][j] = 1;
                    }
                }
            }
        }
        allShipsCoords.resize(10);
        for (int i = 0; i < 10; ++i)
        {
            if (ships[i].nDecks_ == 4) { allShipsCoords[i].resize(4); }
            else if (ships[i].nDecks_ == 3) { allShipsCoords[i].resize(3); }
            else if (ships[i].nDecks_ == 2) { allShipsCoords[i].resize(2); }
            else { allShipsCoords[i].resize(1); }
            for (int j = 0; j < (ships[i].horizontal_ ? ships[i].nDecks_ * 2 : ships[i].nDecks_); ships[i].horizontal_ ? (j += 2) : ++j)
            {
                std::vector<int> coords;
                coords.push_back((ships[i].horizontal_ ? ships[i].getX() + j : ships[i].getX()) + ((player == "enemy") ? 32 : 0)), coords.push_back(ships[i].horizontal_ ? ships[i].getY() : ships[i].getY() + j);
                allShipsCoords[i].push_back(coords);
            }
        }
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < allShipsCoords[i].size(); ++j)
            {
                if (allShipsCoords[i][j].empty())
                {
                    allShipsCoords[i].erase(allShipsCoords[i].begin() + j);
                    --j;
                }
            }
        }
        showField(0, 0, player);
        setCursor(0, 15);
    }

    void showHitZones()
    {
        setColor(Color::CYAN, Color::CYAN);
        for (auto hit : hits)
        {
            setCursor(hit[0], hit[1]);
            std::cout << "++";
        }
    }

    void showMiss()
    {
        setColor(Color::LIGHTGRAY, Color::LIGHTGRAY);
        for (auto miss : missZones)
        {
            setCursor(miss[0], miss[1]);
            std::cout << "++";
        }
    }

    void showDestroyedShips(std::string player)
    {
        setColor(Color::RED, Color::RED);
        int X, Y;
        for (Ship ship : ships)
        {
            if (!ship.isAlive())
            {
                X = ship.getX() + (player == "enemy" ? 32 : 0), Y = ship.getY();
                for (int i = 0; i < ship.getDecksNum(); ++i)
                {
                    setCursor(X, Y);
                    std::cout << "++";
                    if (ship.isHorizontal()) { X += 2; }
                    else { ++Y; }
                }
            }
        }
    }
};
#endif // !CLASS_SHIP_H



