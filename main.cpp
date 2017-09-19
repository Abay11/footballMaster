#include "football_master.h"
#include <cstdlib>
#include <ctime>
#include <zconf.h>
#include <cstring>
#include <string>
#include <iostream>

bool getUserAnswer(){
    system("clear");
    int c; string temp;
    cout << "ФУТБОЛЬНЫЙ МАСТЕР. Главная страница\n\n";

    cout << "1. Показать таблицу 1 игрока\n";
    cout << "2. Показать таблицу 2 игрока\n";
    cout << "3. Показать сравнительный результат игроков\n";
    cout << "4. Показать турную таблицу\n";
    cout << "5. Обновить данные\n";
    cout << "0. Выход\n";

    cout << "\nВведите одну из команд: ";

    cin >> c;

    initProfiles();

    switch((c)){
        case 0:
            system("clear");
            system("exit");
            return false;
            break;
        case 1:
            initPoints();
            system("clear");
            printPlayersStat(Murat);
            getline(cin, temp); getline(cin, temp);
            system("clear");
            getUserAnswer();
            break;
        case 2:
            initPoints();
            system("clear");
            printPlayersStat(Alim);
            getline(cin, temp); getline(cin, temp);
            system("clear");
            getUserAnswer();
            break;
        case 3:
            for (int i = 0; i < 5; ++i) getDoc(URLs[i], i);
            for (int i = 0; i < 5; ++i) parseDoc(LEAGES_NAMES[i], TABLES[i], i);
            initPoints();
            system("clear");
            countPoint(Murat, Alim);
            getTotalScore(Murat, Alim);
            getline(cin, temp); getline(cin, temp);
            system("clear");
            getUserAnswer();
            break;
        case 4:
            system("clear");
            cout << "1. РФПЛ" << endl;
            cout << "2. Бундес Лига" << endl;
            cout << "3. Ла Лига" << endl;
            cout << "4. Серия А" << endl;
            cout << "5. АПЛ" << endl;
            cout << "0. Вернуться назад" << endl;
            cout << "Сделайте свой выбор: " << endl;

            cin >> c;

            if((c) == 0)
                getUserAnswer();
            else if(c > 0 && c <= 5){
                system("clear");
                printStanding(c - 1);
                getline(cin, temp); getline(cin, temp);
                getUserAnswer();

            }
            else {
                cout << "Ты несерьезный человек... Возвращаю тебя на главную";
                sleep(2);
                getUserAnswer();
            }
            break;
        case 5:
            system("clear");
            removeFiles();
            for (int i = 0; i < 5; ++i) getDoc(URLs[i], i);
            parsed = false;
            for (int i = 0; i < 5; ++i) parseDoc(LEAGES_NAMES[i], TABLES[i], i);
            initPoints();
            cout << "\nДанные успешно обновлены!\n";
            for (int i = 0; i < 5; ++i) TABLES[i].clear();
            sleep(2);
            system("clear");
            getUserAnswer();
            break;
        default:
            system("clear");
            cout << "Кажется вы не поняли. Попробуйте еще раз. Мы ожидаем другой результат\n";
            sleep(2);
            getUserAnswer();
            break;
    }
}


int main() {
 /*   for (int i = 0; i < 5; ++i) {
        getDoc(URLs[i], i);
    }
    for (int i = 0; i < 5; ++i) {
        parseDoc(LEAGES_NAMES[i], TABLES[i], i);
    }

    printStanding(2);*/
    do{}
    while(getUserAnswer());
    return 0;
}
