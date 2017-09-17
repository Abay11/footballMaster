#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

enum LEAGES{RFPL, BL, LL, SA, APL};
const vector<string> LEAGES_NAMES = {"RFPL", "BL", "LL", "SA", "APL"};
const vector<int> LEAGES_SIZE = {16, 18, 20, 20, 20};
enum CLUB_COUNT{FIRST_CLUB, SECOND_CLUB, THIRD_CLUB};
map<int, string> RFPL_TABLE, BL_TABLE, LL_TABLE, SA_TABLE, APL_TABLE;
vector< map<int, string> > TABLES = {RFPL_TABLE, BL_TABLE, LL_TABLE, SA_TABLE, APL_TABLE};

const std::string RFPL_URL = "http://www.eurosport.ru/football/russian-football-premier-league/standing.shtml",
        BL_URL = "http://www.eurosport.ru/football/bundesliga/standing.shtml",
        LL_URL = "http://www.eurosport.ru/football/la-liga/standing.shtml",
        SA_URL = "http://www.eurosport.ru/football/serie-a/standing.shtml",
        APL_URL = "http://www.eurosport.ru/football/premier-league/standing.shtml";

//std::pair<std::string[3], int[3]> Murik[5]; // <club, position>
//std::pair<std::string[3], int[3]> Alim[5];

void getDoc(const string&, int); //url, which champ
void parseDoc(const string&, map<int, string>&, int); //html, champ_table, which

struct Profile{
    string name;
    unsigned int point = 0;
    pair<string, int> CLUBS[5][3]; //championat, clubs

    Profile(const string &str) : name(str){};
};

Profile Murat("Murat");
Profile Alim("Alim");

void initProfiles();

void initProfiles(){
    Murat.CLUBS[RFPL][FIRST_CLUB].first = "Краснодар";
    Murat.CLUBS[RFPL][SECOND_CLUB].first = "ЦСКА";
    Murat.CLUBS[RFPL][THIRD_CLUB].first = "Локомотив";
}

void countPoint(const Profile&, const Profile &);
void countPoint(const Profile &a, const Profile &b){}

int main() {
    initProfiles();

    parseDoc(LEAGES_NAMES[RFPL], TABLES[RFPL], RFPL);

    for (int i = 0; i < 5; ++i) {
        for (auto item : TABLES[i]) {
            for (int j = 0; j < 3; ++j) {
                if(item.second == Murat.CLUBS[i][j].first)
                    Murat.CLUBS[i][j].second = item.first;
            }
        }
    }

    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << Murat.CLUBS[i][j].first << " "  << Murat.CLUBS[i][j].second << endl;
        }
    }

//    for (auto item : TABLES[RFPL]){
//        cout << item.first << " " << item.second << endl;
//    }
    /*getDoc(RFPL_URL, RFPL);
    getDoc(BL_URL, BL);

    parseDoc(LEAGES_NAMES[BL], TABLES[BL], BL);

    for (auto item : TABLES[BL]){
        cout << item.first << " " << item.second << endl;
    }*/
//    std::cout << "curl > /home/adygha/test.html " + RFPL_URL << std::endl;



    return 0;
}

void getDoc(const string& url, const int WHICH){
    std::stringstream stream;
    stream << "curl > " << LEAGES_NAMES[WHICH] << " -# " + url;
    cout << "Соединение с сервером. Пожалуйста ждите...\n";
    system(stream.str().c_str());
}

void parseDoc(const string& html, map<int, string>& table, int which){

    std::string text = "", line, name;

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
            findTitle += text.substr(titPos, 1); titPos++;
        }

        while(text[titPos] != '<'){
            findPoint += text.substr(pointPos, 1); pointPos++;
        }

        findTabLoc += text[locPos];
        if(i > 8)
            findTabLoc += text[locPos + 1];

        table.insert(pair<int, string>(stoi(findTabLoc), findTitle));
        ++i;
    }
    fileHTML.close();
}