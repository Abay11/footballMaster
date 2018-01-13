//
// Created by adygha on 9/18/17.
//

#ifndef FOOTBALL_MASTER_FOOTBALL_MASTER_H
#define FOOTBALL_MASTER_FOOTBALL_MASTER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <zconf.h>

#include <map>

#include <vector>

using namespace std;

enum LEAGES{RFPL, BL, LL, SA, APL};
enum CLUB_COUNT{FIRST_CLUB, SECOND_CLUB, THIRD_CLUB};
multimap<int, pair<int, string>> RFPL_TABLE, BL_TABLE, LL_TABLE, SA_TABLE, APL_TABLE; // posit, point, title
vector< multimap<int, pair<int, string> > > TABLES = {RFPL_TABLE, BL_TABLE, LL_TABLE, SA_TABLE, APL_TABLE};

const std::string RFPL_URL = "https://www.eurosport.ru/football/russian-football-premier-league/standing.shtml",
        BL_URL = "https://www.eurosport.ru/football/bundesliga/standing.shtml",
        LL_URL = "https://www.eurosport.ru/football/la-liga/standing.shtml",
        SA_URL = "https://www.eurosport.ru/football/serie-a/standing.shtml",
        APL_URL = "https://www.eurosport.ru/football/premier-league/standing.shtml";

const vector<string> LEAGES_NAMES = {"RFPL", "BundesLiga", "LaLiga", "SeriaA", "APL"};
const vector<string> URLs = {RFPL_URL, BL_URL, LL_URL, SA_URL, APL_URL};

const vector<int> LEAGES_SIZE = {16, 18, 20, 20, 20};

void getDoc(const string&, int); //url, which champ
void parseDoc(const string&, multimap<int, pair<int, string> >&, int); //html, champ_table, which

struct Profile{
    string name;
    unsigned int point[5];
    pair<string, pair<int, int> > CLUBS[5][3]; //club, posit, point

    Profile(const string &str) : name(str){};
};

Profile Murat("Murat");
Profile Alim("Alim");

void printPlayersStat(const Profile& prof){
    for(auto item : TABLES)
        if(item.size() == 0)
            for (int i = 0; i < 5; ++i)
                parseDoc(LEAGES_NAMES[i], item, i);
    cout << prof.name << ":" << endl;
    cout.width(13); cout << left << "Championat";
    cout.width(7); cout << "Pos.";
    cout.width(7); cout << left << "Point";
    cout.width(5); cout << "Club" << endl;

    map<int, pair<int, string> >temp[5]; //pos, point, title

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i].insert(pair<int, pair<int, string> >(
                    prof.CLUBS[i][j].second.first,
                    pair<int, string>(prof.CLUBS[i][j].second.second,
                                      prof.CLUBS[i][j].first) )
            );
        }
    }

    int i = 0;
    for (auto now : temp) {
        cout.width(13);
        cout << left;
        cout << LEAGES_NAMES[i];
        for (auto item : now) {
            cout.width(7);
            string str = to_string(item.first) + ".";
            cout << left << str;

            cout.width(7);
            str = to_string(item.second.first) + ".";
            cout << left << str;

            cout << item.second.second << endl;

            cout.width(13); cout << "";
        }
        cout << endl;
        ++i;
    }
}


void getDoc(const string& url, const int WHICH){
    ifstream file;
    file.open(LEAGES_NAMES[WHICH]);
    if(!file.good()){ //check file existance
        std::stringstream stream;
        stream << "curl > " << LEAGES_NAMES[WHICH] << " -# " + url;
        cout << "Соединение с сервером. Попытка скачать данные " << LEAGES_NAMES[WHICH] << ". Пожалуйста ждите...\n";
        system(stream.str().c_str());
    }
}

void parseDoc(const string& html, multimap<int, pair<int, string> >& table, int which){
    std::string text = "", line, name;

    getDoc(URLs[which], which);
    ifstream fileHTML(LEAGES_NAMES[which]);

    while(getline(fileHTML, line)){
        text += line;
        text += '\n';
    }

    int i = 0, locPos = 0, titPos = 0, pointPos = 0; //iter, posit of position at table in text, title posit in text, posit of point

    const string searchPosition = "<td class=\"standing-table__cell standing-table__cell--position\">";
    const string searchTitle = "<span class=\"text\">";
    const string searchPoint = "table__cell-value--main\">";

    while(i < LEAGES_SIZE[which]) {

        locPos = text.find(searchPosition, locPos) + searchPosition.length();
        titPos = text.find(searchTitle, titPos) + searchTitle.length();
        pointPos = text.find(searchPoint, pointPos) + searchPoint.length();

        string findTabLoc = "", findTitle = "", findPoint = "";


        while(text[titPos] != '<'){
            findTitle += text.substr(titPos, 1);
            titPos++;

        }

        while(text[pointPos] != '<'){
            if(pointPos < text.size())findPoint += text.substr(pointPos, 1); pointPos++;
        }

        findTabLoc += text[locPos];
        if(i > 8)
            findTabLoc += text[locPos + 1];

        table.insert(pair<int, pair<int, string> >(stoi(findTabLoc), pair<int, string>(stoi(findPoint), findTitle) ) );
        ++i;
    }
    fileHTML.close();
}

void initProfiles(){
    Murat.CLUBS[RFPL][FIRST_CLUB].first = "Краснодар";
    Murat.CLUBS[RFPL][SECOND_CLUB].first = "ЦСКА";
    Murat.CLUBS[RFPL][THIRD_CLUB].first = "Локомотив";

    Alim.CLUBS[RFPL][FIRST_CLUB].first = "Зенит";
    Alim.CLUBS[RFPL][SECOND_CLUB].first = "Рубин";
    Alim.CLUBS[RFPL][THIRD_CLUB].first = "Спартак";

    Murat.CLUBS[BL][FIRST_CLUB].first = "РБ Лейпциг";
    Murat.CLUBS[BL][SECOND_CLUB].first = "Шальке 04";
    Murat.CLUBS[BL][THIRD_CLUB].first = "Ганновер";

    Alim.CLUBS[BL][FIRST_CLUB].first = "Бавария Мюнхен";
    Alim.CLUBS[BL][SECOND_CLUB].first = "Боруссия Дортмунд";
    Alim.CLUBS[BL][THIRD_CLUB].first = "Хоффенхайм";

    Murat.CLUBS[LL][FIRST_CLUB].first = "Барселона";
    Murat.CLUBS[LL][SECOND_CLUB].first = "Атлетико Мадрид";
    Murat.CLUBS[LL][THIRD_CLUB].first = "Валенсия";

    Alim.CLUBS[LL][FIRST_CLUB].first = "Реал Мадрид";
    Alim.CLUBS[LL][SECOND_CLUB].first = "Севилья";
    Alim.CLUBS[LL][THIRD_CLUB].first = "Атлетик Бильбао";

    Murat.CLUBS[SA][FIRST_CLUB].first = "Милан";
    Murat.CLUBS[SA][SECOND_CLUB].first = "Наполи";
    Murat.CLUBS[SA][THIRD_CLUB].first = "Торино";

    Alim.CLUBS[SA][FIRST_CLUB].first = "Ювентус";
    Alim.CLUBS[SA][SECOND_CLUB].first = "Интер";
    Alim.CLUBS[SA][THIRD_CLUB].first = "Лацио";

    Murat.CLUBS[APL][FIRST_CLUB].first = "Манчестер Юнайтед";
    Murat.CLUBS[APL][SECOND_CLUB].first = "Челси";
    Murat.CLUBS[APL][THIRD_CLUB].first = "Ливерпуль";

    Alim.CLUBS[APL][FIRST_CLUB].first = "Манчестер Сити";
    Alim.CLUBS[APL][SECOND_CLUB].first = "Тоттенхэм";
    Alim.CLUBS[APL][THIRD_CLUB].first = "Арсенал";
}

void countPoint(Profile &a, Profile &b){
    for (int i = 0; i < 5; ++i) {
        a.point[i] = 0; b.point[i] = 0;
        for (int j = 0; j < 3; ++j) {
            a.point[i] += a.CLUBS[i][j].second.second;
            b.point[i] += b.CLUBS[i][j].second.second;
        }
    }
}

bool getTotalScore(const Profile &a, const Profile &b){
    int aScore = 0, bScore = 0;
    const Profile *winner;
    for (int i = 0; i < 5; ++i) {
        cout << LEAGES_NAMES[i] << endl;
        if(a.point[i] > b.point[i]){
            cout << a.name << " выиграл с " << a.point[i] << " очками. ";
            cout << b.name << " проиграл с " << b.point[i] << " очками.\n\n";
            winner = &a;
            ++aScore;
        }
        else if(a.point[i] < b.point[i]){
            cout << b.name << " выиграл с " << b.point[i] << " очками. ";
            cout << a.name << " проиграл с " << a.point[i] << " очками.\n\n";
            ++bScore;
            winner = &b;
        }
        else{
            winner = NULL;
            cout << "У игроков поровну - " << a.point[i] << " очка. За этот чемпионат очки не начисляются.\n\n";
        }
    }
    cout << "Общий счет: " << aScore << " - " << bScore;
    if(winner != NULL) cout << " в пользу " << winner->name;
    cout << endl;
    return aScore > bScore;
}

void removeFiles(){
    for (int i = 0; i < 5; ++i) {
        remove(LEAGES_NAMES[i].c_str());
    }
}

void initPoints(){

    for (int i = 0; i < 5; ++i)
        if (TABLES[i].size() == 0)
            parseDoc(LEAGES_NAMES[i], TABLES[i], i);

    for (int i = 0; i < 5; ++i) {
        for (auto item : TABLES[i]) {
            for (int j = 0; j < 3; ++j) {
                if(item.second.second == Murat.CLUBS[i][j].first) { //TABLE.second.STRING
                    Murat.CLUBS[i][j].second.first = item.first; //posit
                    Murat.CLUBS[i][j].second.second = item.second.first; //point
                }
                else if(item.second.second == Alim.CLUBS[i][j].first){
                    Alim.CLUBS[i][j].second.first = item.first; //posit
                    Alim.CLUBS[i][j].second.second = item.second.first; //point
                }
            }
        }
    }
}

void printStanding(int which){
    if(TABLES[which].size() == 0) {
        parseDoc(LEAGES_NAMES[which], TABLES[which], which);
    }
    cout.width(5);
    cout << left << "Pos.";
    cout.width(7);
    cout << "Point";
    cout << left << "Club" << endl;
    for (auto now : TABLES[which]) {
        cout.width(5);
        string t = to_string(now.first) + ".";
        cout << left << t;
        cout.width(7);
        cout << left << now.second.first;
        cout << now.second.second << endl;
    }
}

#endif //FOOTBALL_MASTER_FOOTBALL_MASTER_H
