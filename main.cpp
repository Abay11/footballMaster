#include "football_master.h"
#include <cstdlib>
#include <ctime>
#include <zconf.h>
#include <cstring>
#include <string>
#include <iostream>

bool getUserAnswer(){
    system("clear");
    string c;
    cout << "ФУТБОЛЬНЫЙ МАСТЕР. Главная страница\n\n";

    cout << "1. Показать таблицу 1 игрока\n";
    cout << "2. Показать таблицу 2 игрока\n";
    cout << "3. Показать сравнительный результат игроков\n";
    cout << "4. Обновить данные\n";
    cout << "0. Выход\n";

    cout << "\nВведите одну из команд: ";

    cin >> c;

    initProfiles();

    switch(stoi(c)){
        case 0:
            cout << "Давай, до свидания!\n";
            sleep(2);
            system("clear");
            return false;
            break;
        case 1:
            for (int i = 0; i < 5; ++i) getDoc(URLs[i], i);
            for (int i = 0; i < 5; ++i) parseDoc(LEAGES_NAMES[i], TABLES[i], i);
            initPoints();
            system("clear");
            printPlayersStat(Murat);
            getline(cin, c); getline(cin, c);
            system("clear");
            getUserAnswer();
            break;
        case 2:
            for (int i = 0; i < 5; ++i) getDoc(URLs[i], i);
            for (int i = 0; i < 5; ++i) parseDoc(LEAGES_NAMES[i], TABLES[i], i);
            initPoints();
            system("clear");
            printPlayersStat(Alim);
            getline(cin, c); getline(cin, c);
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
            getline(cin, c); getline(cin, c);
            system("clear");
            getUserAnswer();
        case 4:
            system("clear");
            removeFiles();
            for (int i = 0; i < 5; ++i) getDoc(URLs[i], i);
            parsed = false;
            for (int i = 0; i < 5; ++i) parseDoc(LEAGES_NAMES[i], TABLES[i], i);
            initPoints();
            cout << "\nДанные успешно обновлены!\n";
            sleep(2);
            system("clear");
            getUserAnswer();
            break;
        default:
            system("clear");
            cout << "Кажется вы не поняли. Попробуйте еще раз. Мы ожидаем другой результат\n";
            sleep(2);
            getUserAnswer();
    }
}

int main() {
//    do {}while(getUserAnswer());

//    removeFiles();

    for (int i = 0; i < 5; ++i) {
        getDoc(URLs[i], i);
    }

    for (int i = 0; i < 5; ++i) {
        parseDoc(LEAGES_NAMES[i], TABLES[i], i);
    }

    /*for(auto item : TABLES){
        for (auto now : item) {
            cout << now.first << " " << now.second.second << " " << now.second.first << endl;
        }
        cout << endl << endl;
    }*/


    initProfiles();
    initPoints();

//    printPlayersStat(Murat);
//    printPlayersStat(Alim);

    countPoint(Murat, Alim);

    getTotalScore(Murat, Alim);
    return 0;
}
