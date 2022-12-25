//sea_battle

#include "includes.h" // —одержатс€ все нужные инклюды

int main()
{
    setlocale(LC_ALL, "ru");
    std::random_device rd;
    std::mt19937 g(rd());
    srand(time(NULL));
    system("cls");
    Field field;
    char variant1[2][30] = { "AUTOMATIC PLACEMENT", "MANUAL PLACEMENT" };
    char variant2[2][30] = { "DUMB BOT", "SMART BOT" };
    int A = 0, change = 0, automaticPlacement = 1, smartBot = 0;
    int x = 1, y = 0;
    field.me.showField(0, 0, "me"); //создаЄм игровое поле
    field.choice(variant1, change);
    int key;
    do //запускаем цикл
    {
        key = _getch(); //получаем номер нажатой клавиши
        switch (key) //запускаем свитч
        {
        case Keys::UP: //если нажали "—трелочка вверх"
            if (y > 0) //если "y" больше 0
            {
                y--; //вычитаем из значение по "y" 1
                change = y; //выбранный пункт
                field.choice(variant1, change); //вывод пунктов на экран
            }
            break;
        case Keys::DOWN: //если нажали "—трелочка вниз"
            if (y < 1) //если "y" меньше 1
            {
                y++; //прибавл€ем к значению по "y" 1
                change = y; //выбранный пункт
                field.choice(variant1, change); //вывод пунктов на экран
            }
            break;
        case Keys::ENTER:
            do
            {
                switch (change)
                {
                case 0: // ксли 0
                    automaticPlacement = true; //автоматическа€ расстанвкоа
                    A++; //чтобы заврешить цикл
                    break;
                case 1:
                    automaticPlacement = false; //ручна€ расстановка
                    A++; //чтобы заврешить цикл
                    y++; //прибавл€ем к значению по "y" 1
                    break;
                }
            } while (key != Keys::ENTER);
        }
    } while (A < 1);
    A = 0, change = 0;
    x = 1, y = 0;
    system("cls");

    field.me.showField(0, 0, "me"); //создаЄм игровое поле
    field.choice(variant2, change);
    do //запускаем цикл
    {
        key = _getch(); //получаем номер нажатой клавиши
        switch (key) //запускаем свитч
        {
        case Keys::UP: //если нажали "—трелочка вверх"
            if (y > 0) //если "y" больше 0
            {
                y--; //вычитаем из значение по "y" 1
                change = y; //выбранный пункт
                field.choice(variant2, change); //вывод пунктов на экран
            }
            break;
        case Keys::DOWN: //если нажали "—трелочка вниз"
            if (y < 1) //если "y" меньше 1
            {
                y++; //прибавл€ем к значению по "y" 1
                change = y; //выбранный пункт
                field.choice(variant2, change); //вывод пунктов на экран
            }
            break;
        case Keys::ENTER:
            do
            {
                switch (change)
                {
                case 0: // ксли 0
                    smartBot = false; //автоматическа€ расстанвкоа
                    A++; //чтобы заврешить цикл
                    break;
                case 1:
                    smartBot = true; //ручна€ расстановка
                    A++; //чтобы заврешить цикл
                    y++; //прибавл€ем к значению по "y" 1
                    break;
                }
            } while (key != Keys::ENTER);
        }
    } while (A < 1);
    A = 0;
    system("cls");

    if (automaticPlacement)
    {
        field.me.setShipsWithBot("me");
    }
    else
    {
        field.me.setShips();
    }
    field.enemy.setShipsWithBot("enemy");

    field.showFullField();
    int i = 2;
    for (;; ++i)
    {
        if (i % 2 == 0) { if (!field.myAttack()) { break; } }
        else
        {
            if (smartBot) { if (!field.smartEnemyAttack()) { break; } }
            else { if (!field.enemyAttack()) { break; }; }
        }
    }
    field.showFullField();
    setCursor(0, 15);
    if (i % 2 == 0) { std::cout << "YOU WON!!!\n"; }
    else { std::cout << "Your ships are destroyed, the enemy has won.\n"; }
    system("PAUSE");
    return 0;
}
