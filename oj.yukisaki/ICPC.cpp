#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int duration_time=0,problem_count=0,team_num=0,problem_num=0;
bool Have_Started=0,Have_Freezed=0;
string* team_rank;
struct key_team{
    int ac_num,P,ac_time[27]={0};
    string team_name;
    bool operator <(const key_team& b) const
    {
        if (ac_num>b.ac_num) return 1;
        if (ac_num<b.ac_num) return 0;
        if (P<b.P) return 1;
        if (P>b.P) return 0;
        for (int i=ac_num;i>=1;--i) {
            if (ac_time[i] < b.ac_time[i]) return 1;
            if (ac_time[i] > b.ac_time[i]) return 0;
        }
        if (team_name<b.team_name) return 1;
        return 0;
    }
};
struct team{
    string name="";
    int all=0,ac=0,wa=0,tle=0,re=0,pro[27]={0},acpro[27]={0},wapro[27]={0},tlepro[27]={0},repro[27]={0};
    int freeze=0,accepted=0,rank=0,P=0,ac_time[27]={0},sub[27]={0},fresub[27]={0};
    bool have_ac[27]={0},have_freezed[27]={0};
    vector<int> fpro[27];
};

struct problem{
    string team_name,status,problem_name;
    int sub_time;
};

unordered_map<string,team> map_name_team;
unordered_map<string,key_team> map_name_key;
vector<problem> pro;
vector<string> team_name_v;
set<key_team> set_team;
set<key_team> set_fteam;

void init();
void End();
void AddTeam();
void Start();
void Submit();
void Flush(bool ff);//only when ff==1 will print
void Freeze();
void Scroll();
void Query_rank();
void Query_sub();
void index_insert(string& status,unordered_map<string,team>::iterator tmp,int &number,int &problem_num);//insert a index of a problem into the index_lisk
void print(int & cnt);
int main() {
//    freopen("bigger.in","r",stdin);
//    freopen("libro.out","w",stdout);
    string s;
    init();
    while (1){
        cin>>s;
        if (s.find("END")!=string::npos) {End();break;}
        else
        if (s.find("ADDTEAM")!=string::npos) AddTeam();
        else
        if (s.find("START")!=string::npos) Start();
        else
        if (s.find("SUBMIT")!=string::npos) Submit();
        else
        if (s.find("FLUSH")!=string::npos) Flush(1);
        else
        if (s.find("FREEZE")!=string::npos) Freeze();
        else
        if (s.find("SCROLL")!=string::npos) Scroll();
        else
        if (s.find("QUERY_R")!=string::npos) Query_rank();
        else
        if (s.find("QUERY_S")!=string::npos) Query_sub();
    }
//    fclose(stdin);
//    fclose(stdout);
    return 0;
}

void init(){
    map_name_team.clear();
    map_name_key.clear();
    pro.clear();
    pro.push_back({"","","",0});
    team_name_v.clear();
    team_name_v.push_back("");
    return;
}
void End(){
    cout<<"[Info]Competition ends.\n";
    delete [] team_rank;
    return;
}
void Start(){
    int duration_time_tmp=0,problem_count_tmp=0;
    string s;
    //get duration_time
    cin>>s;
    cin>>duration_time_tmp;
    //get problem_count
    cin>>s;
    cin>>problem_count_tmp;
    if (!Have_Started){
        duration_time=duration_time_tmp;
        problem_count=problem_count_tmp;
        team_rank=new string [team_num+5];
        Have_Started=1;
        Flush(0);
        cout<<"[Info]Competition starts.\n";
    }
    else cout<<"[Error]Start failed: competition has started.\n";
    return;
}
void AddTeam(){
    if (Have_Started) {cout<<"[Error]Add failed: competition has started.\n";return ;}
    string ss;
    cin>>ss;
    if (map_name_team.count(ss)==1) {
        cout << "[Error]Add failed: duplicated team name.\n";
        return;
    }
    team_name_v.push_back(ss);
    ++team_num;
    team tmp;
    tmp.name=ss;
    map_name_team[ss]=tmp;
    key_team pre;
    pre.ac_num=0;
    pre.P=0;
    pre.team_name=ss;
    map_name_key[ss]=pre;
    set_team.insert(pre);
    cout<<"[Info]Add successfully.\n";
    return;
}
void Submit(){
    //get problem_name,team_name,etc
    string s;
    string problem_name;
    cin>>problem_name;
    cin>>s;
    string team_name;
    cin>>team_name;
    cin>>s;
    string status;
    cin>>status;
    cin>>s;
    int sub_time;
    cin>>sub_time;
    int number=problem_name[0]-'A';
    //get the team
    unordered_map<string,team>::iterator tmp_team=map_name_team.find(team_name);
    unordered_map<string,key_team>::iterator tmp_key=map_name_key.find(team_name);
    //record the submission
    problem tmp_problem;
    tmp_problem.team_name=team_name;
    tmp_problem.problem_name=problem_name;
    tmp_problem.sub_time=sub_time;
    tmp_problem.status=status;
    pro.push_back(tmp_problem);
    ++problem_num;
    //change according to the submission
    if (!Have_Freezed) {
        if (status == "Accepted") {
            if (!tmp_team->second.have_ac[number]){
                set_team.erase(tmp_key->second);
                tmp_team->second.accepted++;
                tmp_team->second.P += sub_time+20*tmp_team->second.sub[number];
                tmp_team->second.ac_time[tmp_team->second.accepted] = sub_time;
                tmp_key->second.ac_time[tmp_team->second.accepted]=sub_time;
                tmp_key->second.ac_num = tmp_team->second.accepted;
                tmp_key->second.P = tmp_team->second.P;
                tmp_team->second.have_ac[number] = 1;
                set_team.insert(tmp_key->second);
            }
        } else {
            if (!tmp_team->second.have_ac[number]) {
                tmp_team->second.sub[number]++;
            }
        }
    }
    else {
        tmp_team->second.fpro[number].push_back(problem_num);
        if (! tmp_team->second.have_freezed[number]) {
            tmp_team->second.have_freezed[number] = 1;
            ++tmp_team->second.freeze;
        }
        tmp_team->second.fresub[number]++;
    }
    //change the index
    index_insert(status,tmp_team,number,problem_num);
    return;
}
void index_insert(string& stat,unordered_map<string,team>::iterator tmp,int &number,int &problem_num) {
    //according to the status
    if (stat == "Accepted") {
        tmp->second.ac=problem_num;
    } else if (stat == "Wrong_Answer") {
        tmp->second.wa=problem_num;
    } else if (stat == "Runtime_Error") {
        tmp->second.re=problem_num;
    } else if (stat == "Time_Limit_Exceed") {
        tmp->second.tle=problem_num;
    }
    //according to the problem
    tmp->second.pro[number]=problem_num;
    //according to both
    if (stat == "Accepted") {
        tmp->second.acpro[number]=problem_num;
    } else if (stat == "Wrong_Answer") {
        tmp->second.wapro[number]=problem_num;
    } else if (stat == "Runtime_Error") {
        tmp->second.repro[number]=problem_num;
    } else if (stat == "Time_Limit_Exceed") {
        tmp->second.tlepro[number]=problem_num;
    }
    tmp->second.all=problem_num;
    return;
}


void Query_sub(){
    string s;
    string team_name;
    cin>>team_name;
    string stat="",problems="";
    cin>>s;
    cin>>s;
    s+=' ';
    if (s.find("PROBLEM=")!=string::npos){
        std::size_t i=s.find("PROBLEM=");
        i+=8;
        for (;s[i]!=' ';++i) problems+=s[i];
    }
    cin>>s;
    cin>>s;
    s+=' ';
    if (s.find("STATUS=")!=string::npos){
        std::size_t i=s.find("STATUS=");
        i+=7;
        for (;s[i]!=' ';++i) stat+=s[i];
    }
    if (map_name_team.count(team_name) == 0) {
        cout<<"[Error]Query submission failed: cannot find the team.\n";
        return;
    }
    unordered_map<string,team>::iterator tmp_team=map_name_team.find(team_name);
    int ans=0;
    if (stat=="ALL" && problems=="ALL"){
        ans=tmp_team->second.all;
    }else if (stat!="ALL" && problems=="ALL"){
        if (stat=="Accepted")
            ans=tmp_team->second.ac;
        else
        if (stat=="Runtime_Error")
            ans=tmp_team->second.re;
        else
        if (stat=="Time_Limit_Exceed")
            ans=tmp_team->second.tle;
        else
        if (stat=="Wrong_Answer")
            ans=tmp_team->second.wa;
    }else if (stat=="ALL" && problems!="ALL"){
        ans=tmp_team->second.pro[problems[0]-'A'];
    }else {
        if (stat=="Accepted")
            ans=tmp_team->second.acpro[problems[0]-'A'];
        else
        if (stat=="Runtime_Error")
            ans=tmp_team->second.repro[problems[0]-'A'];
        else
        if (stat=="Time_Limit_Exceed")
            ans=tmp_team->second.tlepro[problems[0]-'A'];
        else
        if (stat=="Wrong_Answer")
            ans=tmp_team->second.wapro[problems[0]-'A'];
    }
    printf("[Info]Complete query submission.\n");
    if (ans==0) printf("Cannot find any submission.\n");
    else {
        cout<<pro[ans].team_name<<' '<<pro[ans].problem_name<<' '<<pro[ans].status<<' '<<pro[ans].sub_time<<'\n';
    }
    return;
    //cout<<team_name<<'\n'<<stat<<'\n'<<problems<<'\n';
}
void Flush(bool ff){
    int rank=0;
    string team_name;
    for (set<key_team>::iterator it=set_team.begin();it!=set_team.end();it++){
        team_name=it->team_name;
        unordered_map<string,team>::iterator tmp_team=map_name_team.find(team_name);
        tmp_team->second.rank=++rank;
        team_rank[rank]=it->team_name;
    }
    if (ff) cout<<"[Info]Flush scoreboard.\n";
    return;
}
void Query_rank(){
    string team_name;
    cin>>team_name;
    if (map_name_team.count(team_name) == 0) {
        cout<<"[Error]Query ranking failed: cannot find the team.\n";
        return;
    }
    cout<<"[Info]Complete query ranking.\n";
    unordered_map<string,team>::iterator tmp=map_name_team.find(team_name);
    if (Have_Freezed) cout<<"[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled.\n";
    cout<<tmp->second.name<<" NOW AT RANKING "<<tmp->second.rank<<'\n';
    return;
}
void Freeze(){
    if (Have_Freezed) cout<<"[Error]Freeze failed: scoreboard has been frozen.\n";
    else {
        cout<<"[Info]Freeze scoreboard.\n";
        Have_Freezed=1;
        for (int i=1;i<=team_num;++i){
            unordered_map<string,team>::iterator tmp=map_name_team.find(team_name_v[i]);
            tmp->second.freeze=0;
            for (int j=0;j<problem_count;++j) {
                tmp->second.fresub[j]=0;
                tmp->second.have_freezed[j]=0;
                tmp->second.fpro[j].clear();
            }
        }
    }
    return;
}
void Scroll(){
    if (!Have_Freezed) {
        cout<<"[Error]Scroll failed: scoreboard has not been frozen.\n";
        return;
    }
    set_fteam.clear();
    Have_Freezed=0;
    Flush(0);
    cout<<"[Info]Scroll scoreboard.\n";
    int cnt=0;//record the number of the teams which have frozen submissions;
    print(cnt);
    //scroll
    while (cnt){
        key_team p=*(set_fteam.rbegin());
        unordered_map<string,key_team>::iterator tmp_key=map_name_key.find(p.team_name);
        unordered_map<string,team>::iterator tmp=map_name_team.find(p.team_name);
        int j=0;
        for (;j<problem_count;++j)
            if (tmp->second.have_freezed[j]) break;
        tmp->second.have_freezed[j]=0;
        --tmp->second.freeze;
        if (tmp->second.have_ac[j]) {
            /*for (pro_index *i = ptr->fpro[j]; i != nullptr; pre_i = i, i = i->next, delete pre_i)
                index_insert(pro[i->pt].st, ptr, j, i->pt);*/
            if (!tmp->second.freeze) {set_fteam.erase(p);cnt--;}
        }
        else {
            bool flag_ac=0;int sub=0,ac_time;
            for (int i=tmp->second.fpro[j].size()-1;i >= 0;--i) {
                int v=tmp->second.fpro[j][i];
                if (pro[v].status=="Accepted"){
                    flag_ac=1;sub=0;ac_time=pro[v].sub_time;
                }else sub++;
                /*index_insert(pro[i->pt].st, ptr, j, i->pt);*/
            }
            if (flag_ac) {
                tmp->second.sub[j]+=sub;
                tmp->second.accepted++;
                tmp->second.ac_time[tmp->second.accepted]=ac_time;
                tmp->second.have_ac[j]=1;
                tmp->second.P+=20*tmp->second.sub[j]+ac_time;
                sort(tmp->second.ac_time+1,tmp->second.ac_time+tmp->second.accepted+1);
                tmp_key->second.ac_num++;
                tmp_key->second.ac_time[tmp->second.accepted]=ac_time;
                tmp_key->second.P+=20*tmp->second.sub[j]+ac_time;
                sort(tmp_key->second.ac_time+1,tmp_key->second.ac_time+tmp->second.accepted+1);
                set_fteam.erase(p);
                if (tmp->second.freeze){
                    set_fteam.insert(tmp_key->second);
                } else cnt--;
                set<key_team>::iterator it=set_team.lower_bound(tmp_key->second);
                if (p.team_name != (*it).team_name)
                    cout<<tmp_key->second.team_name<<' '<<(*it).team_name<<' '<<tmp_key->second.ac_num<<' '<<tmp_key->second.P<<'\n';
                set_team.erase(p);
                set_team.insert(tmp_key->second);
            }else {
                tmp->second.sub[j]+=sub;
                if (!tmp->second.freeze){
                    cnt--;
                    set_fteam.erase(p);
                }
            }
        }
    }
    Flush(0);
    print(cnt);
    return;
}

void print(int & cnt){
    unordered_map<string,team>::iterator tmp;
    for (int i=1;i<=team_num;++i) {
        tmp=map_name_team.find(team_rank[i]);
        if (tmp->second.freeze) {
            unordered_map<string,key_team>::iterator now=map_name_key.find(team_rank[i]);
            set_fteam.insert(now->second);
            ++cnt;
        }
        cout<<tmp->second.name<<' '<<i<<' '<<tmp->second.accepted<<' '<<tmp->second.P;
        for (int j=0;j<problem_count;++j){
            if (tmp->second.have_ac[j]){
                if (tmp->second.sub[j]) cout<<" +"<<tmp->second.sub[j];
                else cout<<" +";
            } else
            if (!tmp->second.have_freezed[j]){
                if (tmp->second.sub[j]) cout<<" -"<<tmp->second.sub[j];
                else cout<<" .";
            }else{
                if (tmp->second.sub[j]) cout<<" -"<<tmp->second.sub[j]<<'/'<<tmp->second.fresub[j];
                else cout<<' '<<tmp->second.sub[j]<<'/'<<tmp->second.fresub[j];
            }
        }
        cout<<'\n';
    }
}