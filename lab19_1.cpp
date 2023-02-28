#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    char format[] = "%[^:]: %d %d %d";
    int a,b,c;
    char d[100];
    while(getline(source,textline))
    {
        sscanf(textline.c_str(),format,d,&a,&b,&c);
        names.push_back(d);
        int sum = a+b+c;
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command, string &key){
    string e;
    char comman[100],kea[100];
    cout << "Please input your command: "; 
    getline(cin,e);
    if(toUpperStr(e) == "EXIT")
    {
        command = e;
    }
    else
    {
        e.insert(e.size(),"!");
        char format2[] = "%[^ !] %[^!]!";
        sscanf(e.c_str(),format2,comman,kea);
        command = comman;
        key = kea;
    }
}

void searchName(vector<string> names ,vector<int> scores ,vector<char> grades ,string key){
    int f = 0;
    string ke = toUpperStr(key);
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<scores.size();i++)
    {
        string nam = toUpperStr(names[i]);
        if(nam==ke)
        {
            cout << names[i] << "\'s score = " << scores[i] << "\n";
            cout << names[i] << "\'s grade = " << grades[i] << "\n";
            f+=1;
        } 
    }
    if(f == 0 ) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names ,vector<int> scores ,vector<char> grades ,string key){
    int f = 0;
    string ke = toUpperStr(key);
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<scores.size();i++)
    {
        string gra;
        gra.push_back(grades[i]);
        if(gra==ke)
        {
            cout << names[i] << " (" << scores[i] << ")\n";
            f+=1;
        } 
    }
    if(f == 0 ) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
