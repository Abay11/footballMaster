#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

enum LEAGES{RFPL, BL, LL, SA, APL};
const vector<string> LEAGES_NAMES = {"RFPL", "BL", "LL", "SA", "APL"};
const vector<int> LEAGES_SIZE = {16, 18, 20, 20, 20};
enum CLUB_COUNT{FIRST_CLUB, SECOND_CLUB, THIRD_CLUB};
map<int, pair<int, string> > RFPL_TABLE, BL_TABLE, LL_TABLE, SA_TABLE, APL_TABLE; // posit, point, title
vector< map<int, pair<int, string> > > TABLES = {RFPL_TABLE, BL_TABLE, LL_TABLE, SA_TABLE, APL_TABLE};

const std::string RFPL_URL = "http://www.eurosport.ru/football/russian-football-premier-league/standing.shtml",
        BL_URL = "http://www.eurosport.ru/football/bundesliga/standing.shtml",
        LL_URL = "http://www.eurosport.ru/football/la-liga/standing.shtml",
        SA_URL = "http://www.eurosport.ru/football/serie-a/standing.shtml",
        APL_URL = "http://www.eurosport.ru/football/premier-league/standing.shtml";
const vector<string> URLs = {RFPL_URL, BL_URL, LL_URL, SA_URL, APL_URL};

//std::pair<std::string[3], int[3]> Murik[5]; // <club, position>
//std::pair<std::string[3], int[3]> Alim[5];

void getDoc(const string&, int); //url, which champ
void parseDoc(const string&, map<int, pair<int, string> >&, int); //html, champ_table, which

struct Profile{
    string name;
    unsigned int point[5];
    pair<string, pair<int, int> > CLUBS[5][3]; //club, posit, point

    Profile(const string &str) : name(str){};
};

Profile Murat("Murat");
Profile Alim("Alim");

void initProfiles();

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

void countPoint(Profile&, Profile&);
void countPoint(Profile &a, Profile &b){
    for (int i = 0; i < 5; ++i) {
            a.point[i] = 0; b.point[i] = 0;
        for (int j = 0; j < 3; ++j) {
            a.point[i] += a.CLUBS[i][j].second.second;
            b.point[i] += b.CLUBS[i][j].second.second;
        }
    }
}


bool getTotalScore(const Profile&, const Profile&);
bool getTotalScore(const Profile &a, const Profile &b){
    int aScore = 0, bScore = 0;
    for (int i = 0; i < 5; ++i) {
        cout << LEAGES_NAMES[i] << ": ";
        if(a.point[i] > b.point[i]){
            cout << a.name << " выиграл с " << a.point[i] << " очками. ";
            cout << b.name << " проиграл с " << b.point[i] << " очками.\n";
            ++aScore;
        }
        else if(a.point[i] < b.point[i]){
            cout << b.name << " выиграл с " << b.point[i] << " очками. ";
            cout << a.name << " проиграл с " << a.point[i] << " очками.\n";
            ++bScore;
        }
        else{
            cout << "У игроков поровну - " << a.point[i] << " очка. За этот чемпионат очки не начисляются.\n";
        }
    }
    cout << "Общий счет: " << aScore << " : " << bScore;
    return aScore > bScore;
}

int main() {

    for (int i = 0; i < 5; ++i) {
        getDoc(URLs[i], i);
    }

    for (int i = 0; i < 5; ++i) {
        parseDoc(LEAGES_NAMES[i], TABLES[i], i);
    }

    initProfiles();

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

    countPoint(Murat, Alim);

    getTotalScore(Murat, Alim);

/*    for (int i = 0; i < 5; ++i) {
        cout << LEAGES_NAMES[i] << ": \n";
        for (int j = 0; j < 3; ++j) {
            //1. POSIT 2. TITLE 3. POINTS
            cout << Murat.CLUBS[i][j].second.first << ". " << left << Murat.CLUBS[i][j].first << " " << Murat.CLUBS[i][j].second.second << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < 5; ++i) {
        cout << LEAGES_NAMES[i] << ": \n";
        for (int j = 0; j < 3; ++j) {
            //1. POSIT 2. TITLE 3. POINTS
            cout << Alim.CLUBS[i][j].second.first << ". " << left << Alim.CLUBS[i][j].first << " " << Alim.CLUBS[i][j].second.second << endl;
        }
        cout << endl;
    }*/
    return 0;
}

void getDoc(const string& url, const int WHICH){
    ifstream file;
    file.open( (LEAGES_NAMES[WHICH] ) );
    if(!file.is_open()) {
        std::stringstream stream;
        stream << "curl > " << LEAGES_NAMES[WHICH] << " -# " + url;
        cout << "Соединение с сервером. Попытка скачать " << LEAGES_NAMES[WHICH] << ". Пожалуйста ждите...\n";
        system(stream.str().c_str());
    }
}

void parseDoc(const string& html, map<int, pair<int, string> >& table, int which){

    std::string text = "", line, name;

    ifstream fileHTML(LEAGES_NAMES[which]);
    if(!fileHTML.is_open()){
        cerr << "Ошибка открытия файла.\n";
        return;
    }

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