#include "football_master.h"


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
            initPoints();
            system("clear");
            countPoint(Murat, Alim);
            getTotalScore(Murat, Alim);
            getline(cin, temp); getline(cin, temp);
            system("clear");
            getUserAnswer();
            break;
        case 4:
            while(true) {
                system("clear");
                cout << "1. РФПЛ" << endl;
                cout << "2. Бундес Лига" << endl;
                cout << "3. Ла Лига" << endl;
                cout << "4. Серия А" << endl;
                cout << "5. АПЛ" << endl;
                cout << "0. Вернуться назад" << endl;
                cout << "Сделайте свой выбор: ";

                cin >> c;

                if ((c) == 0)
                    break;
                else if (c > 0 && c <= 5) {
                    system("clear");
                    printStanding(c - 1);
                    getline(cin, temp); getline(cin, temp);
                } else {
                    cout << "\nНесерьезный ты человек... Возвращаю тебя на главную\n";
                    sleep(2);
                    system("clear");
                    break;
                }
            }
            getUserAnswer();
            break;
        case 5:
            system("clear");
            removeFiles();
            for (int i = 0; i < 5; ++i) TABLES[i].clear();
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
            break;
    }
}


int main() {
    getUserAnswer();
    return 0;
}
