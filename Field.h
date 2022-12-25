#ifndef CLASS_FIELD_H
#define CLASS_FIELD_H
#include "includes.h"

class Field
{
public:
    Ship::Player me;
    Ship::Player enemy;
    short X = 0, Y = 0;
    Field() { me.defShipsArr(), enemy.defShipsArr(); }

    void showFullField()
    {
        me.showField(0, 0, "me");
        enemy.showField(32, 0, "enemy");
        me.showMiss();
        enemy.showMiss();
        me.showHitZones();
        enemy.showHitZones();
        me.showDestroyedShips("me");
        enemy.showDestroyedShips("enemy");
        setCursor(0, 15);
        setColor(Color::WHITE, Color::BLACK);
    }

    void choice(char variant[2][30], int point) //меню выбора расстановки
    {
        system("cls"); //очищаем консоль
        for (size_t i = 0; i < 2; i++) //создаём цикл для 2-ух элементов
        {
            setCursor(30, 6 + i); //Устанавливаем курсор на нужную позицию
            for (size_t p = 0; p < 30; p++) //создаём цикл для всех 30-ти буковок
            {
                if (i == point) //проверка на выбранный пункт
                {
                    setColor(Color::BLACK, Color::WHITE); //выделяем выбранный пункт
                }
                else //иначе
                {
                    setColor(Color::WHITE, Color::BLACK); //убираем выделение выбранного пункта
                }
                std::cout << variant[i][p]; //выводим пункты в виде тектса
            }
        }
        me.showField(0, 0, "me"); //создаём игровое поле занаво
    }

    int myAttack()
    {
        int result = 1;
        do
        {
            result = 0;
            X = 34; Y = 1;
            int accept = 0;
            do
            {
                showFullField();
                setColor(Color::DARKGRAY, Color::DARKGRAY);
                setCursor(X, Y);
                std::cout << "++";
                int key = _getch();
                switch (key)
                {
                case Keys::UP:
                    if (Y > 1) { --Y; }
                    break;
                case Keys::DOWN:
                    if (Y < 10) { ++Y; }
                    break;
                case Keys::LEFT:
                    if (X > 34) { X -= 2; }
                    break;
                case Keys::RIGHT:
                    if (X < 52) { X += 2; }
                    break;
                case Keys::ENTER:
                    if (!me.isDestroyed(X, Y)) { ++accept; }
                    break;
                }
            } while (accept == 0);
            showFullField();
            if (enemy.shipsPosInArr[Y][X - 32] == 1)
            {
                std::vector<int> coords;
                coords.push_back(X), coords.push_back(Y);
                me.hits.push_back(coords);
            }
            else
            {
                std::vector<int> coords;
                coords.push_back(X), coords.push_back(Y);
                me.missZones.push_back(coords);
            }
            for (int i = 0; i < enemy.allShipsCoords.size(); ++i)
            {
                for (int j = 0; j < enemy.allShipsCoords[i].size(); ++j)
                {
                    if (enemy.allShipsCoords[i][j][0] == X && enemy.allShipsCoords[i][j][1] == Y)
                    {
                        enemy.allShipsCoords[i].erase(enemy.allShipsCoords[i].begin() + j);
                    }
                }
            }
            for (int i = 0; i < enemy.allShipsCoords.size(); ++i)
            {
                if (enemy.allShipsCoords[i].empty())
                {
                    if (enemy.ships[i].isAlive() == true)
                    {
                        enemy.ships[i].changeAlive(!enemy.ships[i].isAlive());
                    }
                }
            }
            setColor(Color::WHITE, Color::BLACK);
            setCursor(0, 15);

            for (auto ship : enemy.ships)
            {
                if (ship.isAlive() == true) { ++result; }
            }
        } while (result && enemy.shipsPosInArr[Y][X - 32] == 1);
        return result;
    }

    int enemyAttack()
    {
        int result = 1;
        do
        {
            result = 0;
            if (me.nextAttack.empty())
            {
                for (int i = 1; i < 11; ++i)
                {
                    for (int j = 2; j < 22; j += 2)
                    {
                        std::vector<int> coords;
                        coords.push_back(j), coords.push_back(i);
                        me.nextAttack.push_back(coords);
                    }
                }
                std::random_shuffle(me.nextAttack.begin(), me.nextAttack.end());
            }
            X = me.nextAttack[0][0], Y = me.nextAttack[0][1];
            if (me.shipsPosInArr[Y][X] == 1)
            {
                std::vector<int> coords;
                coords.push_back(X), coords.push_back(Y);
                enemy.hits.push_back(coords);
            }
            else
            {
                std::vector<int> coords;
                coords.push_back(X), coords.push_back(Y);
                enemy.missZones.push_back(coords);
            }
            for (int i = 0; i < me.allShipsCoords.size(); ++i)
            {
                for (int j = 0; j < me.allShipsCoords[i].size(); ++j)
                {
                    if (me.allShipsCoords[i][j][0] == X && me.allShipsCoords[i][j][1] == Y)
                    {
                        me.allShipsCoords[i].erase(me.allShipsCoords[i].begin() + j);
                    }
                }
            }
            for (int i = 0; i < me.allShipsCoords.size(); ++i)
            {
                if (me.allShipsCoords[i].empty())
                {
                    if (me.ships[i].isAlive() == true)
                    {
                        me.ships[i].changeAlive(!me.ships[i].isAlive());
                    }
                }
            }
            me.nextAttack.erase(me.nextAttack.begin());
            setColor(Color::WHITE, Color::BLACK);
            setCursor(0, 15);
            for (auto ship : me.ships)
            {
                if (ship.isAlive() == true) { ++result; }
            }
        } while (result && me.shipsPosInArr[Y][X] == 1);
        return result;
    }

    int smartEnemyAttack()
    {
        int result = 1;
        do
        {
            result = 0;
            if (me.smartField.empty())
            {
                me.smartField.resize(12);
                for (int i = 0; i < me.smartField.size(); ++i)
                {
                    me.smartField[i].resize(24);
                    std::fill(me.smartField[i].begin(), me.smartField[i].end(), 0);
                    if (i != 0 && i != 11)
                    {
                        for (int j = 2; j < me.smartField[i].size() - 2; j += 2)
                        {
                            me.smartField[i][j] = 1;
                        }
                    }
                }
            }
            int max_weight = 0;
            for (int i = 0; i < me.smartField.size(); ++i)
            {
                for (int j = 0; j < me.smartField[i].size(); ++j)
                {
                    if (me.smartField[i][j] > max_weight)
                    {
                        max_weight = me.smartField[i][j];
                    }
                }
            }
            for (int i = 1; i < me.smartField.size() - 1; ++i)
            {
                for (int j = 2; j < me.smartField[i].size() - 2; j += 2)
                {
                    if (me.smartField[i][j] == max_weight)
                    {
                        std::vector<int> coords;
                        coords.push_back(j), coords.push_back(i);
                        me.nextAttack.push_back(coords);
                    }
                }
            }
            std::random_shuffle(me.nextAttack.begin(), me.nextAttack.end());

            X = me.nextAttack[0][0], Y = me.nextAttack[0][1];
            if (me.shipsPosInArr[Y][X] == 1)
            {
                std::vector<int> coords;
                coords.push_back(X), coords.push_back(Y);
                enemy.hits.push_back(coords);
                for (int i = ((Y > 1) ? (Y - 1) : Y); i < ((Y < 10) ? Y + 2 : Y); ++i)
                {
                    for (int j = (X > 2 ? X - 2 : X); j < (X < 20 ? X + 3 : X); j += 2)
                    {
                        if ((i == Y - 1 && j == X - 2) || (i == Y + 1 && j == X + 2) || (i == Y + 1 && j == X - 2) || (i == Y - 1 && j == X + 2) || (i == Y && j == X))
                        {
                            me.smartField[i][j] *= 0;
                        }
                        else { me.smartField[i][j] *= 10; }
                    }
                }
            }
            else
            {
                std::vector<int> coords;
                coords.push_back(X), coords.push_back(Y);
                enemy.missZones.push_back(coords);
                me.smartField[Y][X] *= 0;
            }
            for (int i = 0; i < me.allShipsCoords.size(); ++i)
            {
                for (int j = 0; j < me.allShipsCoords[i].size(); ++j)
                {
                    if (me.allShipsCoords[i][j][0] == X && me.allShipsCoords[i][j][1] == Y)
                    {
                        me.allShipsCoords[i].erase(me.allShipsCoords[i].begin() + j);
                    }
                }
            }
            for (int i = 0; i < me.allShipsCoords.size(); ++i)
            {
                if (me.allShipsCoords[i].empty())
                {
                    if (me.ships[i].isAlive() == true)
                    {
                        me.ships[i].changeAlive(!me.ships[i].isAlive());
                        for (int j = (me.ships[i].getY() - 1); j < me.ships[i].getY() - 1 + (me.ships[i].isHorizontal() ? 3 : me.ships[i].getDecksNum() + 2); ++j)
                        {
                            for (int z = (me.ships[i].getX() - 2); z < me.ships[i].getX() - 2 + (me.ships[i].isHorizontal() ? me.ships[i].getDecksNum() + 2 : 3) * 2; ++z)
                            {
                                me.smartField[j][z] = 0;
                            }
                        }
                    }
                }
            }
            me.nextAttack.clear();
            setColor(Color::WHITE, Color::BLACK);
            setCursor(0, 15);
            for (auto ship : me.ships)
            {
                if (ship.isAlive() == true) { ++result; }
            }
        } while (result && me.shipsPosInArr[Y][X] == 1);
        return result;
    }
};

#endif //!CLASS_FIELD_H
