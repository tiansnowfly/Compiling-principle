#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define MAX 100
using namespace std;

vector<pair<string, string>> str_array;
bool FIRSTVT[MAX][MAX],LASTVT[MAX][MAX];
char relation_table[MAX][MAX];
map<char, int> Vn, Vt;
int count_Vn = 0, count_Vt = 0;

bool compare(pair<char,int> v1,pair<char,int> v2){
    return v1.second < v2.second;
}
bool isVt(char vt){
    if (((vt >= '!' && vt <= '@') || (vt >= '[' && vt <= '}')) && vt != '|' && vt != '$'){
        return true;
    }
    else
        return false;
}
void make_first(){
    int i, j;
    for (i = 0; i < count_Vn;++i){
        for (j = 0; j < count_Vt+count_Vn;++j){
            FIRSTVT[i][j] = false;
        }
    }
    pair<char,char> vn_vt;
    stack<pair<char,char>> st;
    for (vector<pair<string, string>>::iterator itr = str_array.begin(); itr != str_array.end();++itr){
        char str_temp0 = (*itr).first[0];
        char str_temp1 = (*itr).second[0];
        char str_temp2 = (*itr).second[1];
        if (isVt(str_temp1)){
            FIRSTVT[Vn[str_temp0]][Vt[str_temp1]] = true;
            vn_vt.first = str_temp0;
            vn_vt.second = str_temp1;
            st.push(vn_vt);
        }
        else if(str_temp1>='A'&&str_temp1<='Z'){
            if (isVt(str_temp2)) {
                FIRSTVT[Vn[str_temp0]][Vt[str_temp2]] = true;
                vn_vt.first = str_temp0;
                vn_vt.second = str_temp2;
                st.push(vn_vt);
            }
            else{
                FIRSTVT[Vn[str_temp0]][Vn[str_temp1]+count_Vt] = true;
            }
        }
    }
    pair<char, char> pair_temp;
    while(!st.empty()){
        pair_temp = st.top();
        st.pop();
        for (vector<pair<string, string>>::iterator itr = str_array.begin(); itr != str_array.end(); ++itr) {
            if(FIRSTVT[Vn[(*itr).first[0]]][Vn[pair_temp.first]+count_Vt]==true){
                for (i = 0; i < count_Vt;++i){
                    if (FIRSTVT[Vn[pair_temp.first]][i]==true){
                        FIRSTVT[Vn[(*itr).first[0]]][i] = true;
                    }
                }
            }
        }
    }
    /*for (i = 0; i < count_Vn; ++i){
        for (j = 0; j < count_Vt; ++j){
            cout<<FIRSTVT[i][j]<<" ";
        }
        cout << endl;
    }
    cout<<endl;*/
}
void make_last(){
    int i, j;
    for (i = 0; i < count_Vn; ++i){
        for (j = 0; j < count_Vt + count_Vn; ++j){
            LASTVT[i][j] = false;
        }
    }
    pair<char, char> vn_vt;
    stack<pair<char, char>> st;
    for (vector<pair<string, string>>::iterator itr = str_array.begin(); itr != str_array.end(); ++itr){
        char str_temp0=(*itr).first[0];
        int len = (*itr).second.length();
        char str_temp1=(*itr).second[len-1];
        char str_temp2=(*itr).second[len-2];
        if (isVt(str_temp1))
        {
            LASTVT[Vn[str_temp0]][Vt[str_temp1]] = true;
            vn_vt.first = str_temp0;
            vn_vt.second = str_temp1;
            st.push(vn_vt);
        }
        else if (str_temp1 >= 'A' && str_temp1 <= 'Z'){
            if (isVt(str_temp2))
            {
                LASTVT[Vn[str_temp0]][Vt[str_temp2]] = true;
                vn_vt.first = str_temp0;
                vn_vt.second = str_temp2;
                st.push(vn_vt);
            }
            else{
                LASTVT[Vn[str_temp0]][Vn[str_temp1] + count_Vt] = true;
            }
        }
    }
    pair<char, char> pair_temp;
    while (!st.empty()){
        pair_temp = st.top();
        st.pop();
        for (vector<pair<string, string>>::iterator itr = str_array.begin(); itr != str_array.end(); ++itr){
            if (LASTVT[Vn[(*itr).first[0]]][Vn[pair_temp.first] + count_Vt] == true){
                for (i = 0; i < count_Vt; ++i){
                    if (LASTVT[Vn[pair_temp.first]][i]==true){
                        LASTVT[Vn[(*itr).first[0]]][i] = true;
                    }
                }
            }
        }
    }
    /*for (i = 0; i < count_Vn; ++i){
        for (j = 0; j < count_Vt; ++j){
            cout<<LASTVT[i][j]<<" ";
        }
        cout << endl;
    }*/
}
void make_relation_table(){
    for (vector<pair<string, string>>::iterator itr = str_array.begin(); itr != str_array.end();++itr){
        string right_temp = (*itr).second;
        int right_len = right_temp.length();
        for (int i = 0; i < right_len - 1; ++i){
            bool flag1 = isVt(right_temp[i]);
            bool flag2 = isVt(right_temp[i+1]);
            if(flag1&&flag2){
                relation_table[Vt[right_temp[i]]][Vt[right_temp[i + 1]]] = '=';
            }
            if(flag1&&!flag2){
                if (i < right_len - 2){
                    bool flag3 = isVt(right_temp[i+2]);
                    if(flag3){
                        relation_table[Vt[right_temp[i]]][Vt[right_temp[i + 2]]] = '=';
                    }
                }
            }
            if(flag1&&!flag2){
                for (int j = 0; j < count_Vt;++j){
                    if(FIRSTVT[Vn[right_temp[i+1]]][j]){
                        relation_table[Vt[right_temp[i]]][j] = '<';
                    }
                }
            }
            if(!flag1&&flag2){
                for (int k = 0; k < count_Vt;++k){
                    if(LASTVT[Vn[right_temp[i]]][k])
                        relation_table[k][Vt[right_temp[i+1]]] = '>';
                }
            }
        }
    }
    pair<char, int> map_temp;
    vector<pair<char, int>> vec_map;
    for (map<char, int>::iterator itr = Vt.begin(); itr != Vt.end();++itr){
        map_temp.first=(*itr).first;
        map_temp.second = (*itr).second;
        vec_map.push_back(map_temp);
    }
    ++count_Vt;
    map_temp.first = '$';
    map_temp.second =count_Vt-1;
    vec_map.push_back(map_temp);

    sort(vec_map.begin(), vec_map.end(), compare);

    for (vector<pair<char,int>>::iterator itr = vec_map.begin(); itr != vec_map.end(); ++itr){
        if((*itr).first==')'||(*itr).first=='$'){
            if ((*itr).first == '$'){
                relation_table[count_Vt-1][(*itr).second] = '=';
            }
        }
        else{
            relation_table[count_Vt-1][(*itr).second] = '<';
        }
    }
    for (vector<pair<char, int>>::iterator itr = vec_map.begin(); itr != vec_map.end(); ++itr){
        if ((*itr).first == '(' || (*itr).first == '$'){
            if ((*itr).first == '$'){
                relation_table[(*itr).second][count_Vt-1] = '=';
            }
        }
        else{
            relation_table[(*itr).second][count_Vt-1] = '>';
        }
    }
    //ofstream outfile;
    //outfile.open("cout.txt");
    cout << "------------------------------------" << endl;
    cout << "--operator_priority_analysis_table--" << endl;
    for (int i = 0; i <=count_Vt+1;++i)
        cout << "----";
    cout<< endl;
    cout << " |  "<<" | ";
    for (vector<pair<char,int>>::iterator itr = vec_map.begin(); itr != vec_map.end(); ++itr){
        cout << (*itr).first << " | ";
    }
    cout << endl;
    for (int i = 0; i <= count_Vt+1; ++i)
        cout << "----";
    cout << endl;
    for (vector<pair<char, int>>::iterator itr = vec_map.begin(); itr != vec_map.end(); ++itr){
        cout << " | "<<(*itr).first<<" | ";
        for (int t = 0; t < count_Vt;++t){
            cout << relation_table[(*itr).second][t] << " | ";
        }
        cout << endl;
        for (int i = 0; i <= count_Vt+1; ++i)
            cout << "----";
        cout << endl;
    }
    //outfile.close();
}
bool find_Vn(char ch1){
    for (map<char, int>::iterator itr = Vn.begin(); itr != Vn.end();++itr){
        if((*itr).first==ch1){
            return true;
        }
    }
    return false;
}
bool find_Vt(char ch2){
    for (map<char, int>::iterator itr = Vt.begin(); itr != Vt.end();++itr){
        if((*itr).first==ch2){
            return true;
        }
    }
    return false;
}
void error(){
    cout << "Grammar error!\n";
    system("pause");
    exit(0);
}
int main(){
    ifstream infile;
    infile.open("cin.txt");
    //ofstream outfile;
    //outfile.open("cout.txt");

    string str;
    vector<string> array;
    pair<string, string> pair_array;
    while(getline(infile,str)){
        array.push_back(str);
    }
    for (vector<string>::iterator itr = array.begin(); itr != array.end();++itr){
        pair_array.first = (*itr)[0];
        if((*itr)[0]<='A'&&(*itr)[0]>='Z'){
            error();
        }
        if(!find_Vn((*itr)[0])){
          Vn[(*itr)[0]] = count_Vn;
          ++count_Vn;
        }
        if ((*itr)[1] != '-' && (*itr)[2] != '>') {
            error();
        }
        int temp = 3;
        int strlen = (*itr).length();
        for (int i = 3; i < strlen;++i){
            if ((*itr)[i-1] == '-' && (*itr)[i] == '>') {
                error();
            }
            if((*itr)[i]>='A'&&(*itr)[i]<='Z'){
                if(!find_Vn((*itr)[i])){
                    Vn[(*itr)[i]] = count_Vn;
                    ++count_Vn;
                }
            }
            else if (isVt((*itr)[i]))
            {
                if(!find_Vt((*itr)[i])){
                    Vt[(*itr)[i]] =count_Vt;
                    ++count_Vt;
                }
            }
            if((*itr)[i]=='|'){
                pair_array.second = (*itr).substr(temp,i-temp);
                temp = i + 1;
                str_array.push_back(pair_array);
            }
            if(i==strlen-1){
                pair_array.second = (*itr).substr(temp,strlen+1-temp);
                str_array.push_back(pair_array);
            }
        }
    }
    make_first();
    make_last();
    make_relation_table();
    infile.close();
    //outfile.close();
    system("pause");
    return 0;
}