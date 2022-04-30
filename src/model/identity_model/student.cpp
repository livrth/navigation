#include "student.h"
#include "course.h"
#include <fstream>
Student::Student() {
}

Student::Student(string id, string name) {
    this->stu_id = id;
    this->stu_name = name;
}

void Student::query_by_course_name() {
   
}

void Student::query_by_course_table() {
   cout<<endl;
   cout<<"\t\t\t\t\t\t\t\t\t课程表"<<endl;
   cout<<"    ";
   for(int i=1;i<=11;i++)cout<<"    "<<"第"<<i<<"节"<<"    ";
   cout<<endl;
   for(int i=1;i<=5;i++){
       cout<<number_to_date[i]+"|";
       for(int seq=1;seq<=11;seq++){
           if(my_course_table[i][seq]!="NULL"){
               int blank_number=12-my_course_table[i][seq].length();
               cout<<my_course_table[i][seq];
               for(int j=1;j<=blank_number;j++)cout<<" ";
           }
           else{
               int blank_number=12;
               for(int j=1;j<=blank_number;j++)cout<<" ";
           }
           cout<<"|";
       }
       cout<<endl;
   }
   string object_name;
   string object_id;
   cout<<endl<<"请输入想要进入的课程名称："<<endl;
   cin>>object_name;
   while(true){
   if(name_to_id.find(object_name)==name_to_id.end()){
       cout<<"请输入正确的名称："<<endl;
       cin>>object_name;
   }
   else {
       object_id=name_to_id[object_name];
       break;
   }
   }
   course_menu(object_id,object_name,this->stu_id);
   
}

void Student::upload_course_material() {
}

void Student::set_activity_alarm() {
}

void Student::guide_now() {
}

void Student::query_activity() {
}

void Student::upload_home_work() {
}

void Student::update(int root){
    t[root].size=t[t[root].left].size+t[t[root].right].size+t[root].num;
}

int Student::rank(int x,int root){
    if(root){
        if(x<t[root].value)
        return rank(x,t[root].left);
        if(x>t[root].value)
        return rank(x,t[root].right)+t[t[root].left].size+t[root].num;
        return t[t[root].left].size+t[root].num;
    }
    return 1;
}

int Student::kth(int x,int root){
    if(x<=t[t[root].left].size)return kth(x,t[root].left);
    if(x<=t[t[root].left].size+t[root].num)return t[root].value;
    return kth(x-t[t[root].left].size-t[root].num,t[root].right);
}

void Student::insert(int x,int root){
    if(x<t[root].value)
    if(!t[root].left)
    t[t[root].left=++cnt]=Node(0,0,1,x);
    else insert(x,t[root].left);
    else if(x>t[root].value)
    if(!t[root].right)t[t[root].right=++cnt]=Node(0,0,1,x);
    else insert(x,t[root].right);
    else t[root].num++;
    update(root);
}

void Student::init(){
    string courese_table_filename="../../src/model/identity_model/course_table/"+stu_id+"_course_table.txt";
    ifstream ifs;
    ifs.open(courese_table_filename, ios::in);

    if (!ifs.is_open()) {
        cout << "用户文件不存在" << endl;
        ifs.close();
        return;
    }
    
    for(int i=1;i<=5;i++)
    for(int j=1;j<=11;j++)
    my_course_table[i][j]="NULL";


    string date,place,course_name,course_id,campus;
    int seq;
    t[root=++cnt]=Node(0,0,1,2147483647);
    while(ifs >>date>>seq>>place>>course_name>>campus>>course_id){
        int time=0;
        if(date.find("Mon")!=-1){
            time+=0;
            my_course_table[1][seq]=course_name;
        }
        if(date.find("Tue")!=-1){
            time+=24*60;
            my_course_table[2][seq]=course_name;
        }
        if(date.find("Wed")!=-1){
            time+=48*60;
            my_course_table[3][seq]=course_name;
        }
        if(date.find("Thu")!=-1){
            time+=72*60;
            my_course_table[4][seq]=course_name;
        }
        if(date.find("Fri")!=-1){
            time+=96*60;
            my_course_table[5][seq]=course_name;
        }
        time+=course_start_time_table[seq];
        insert(time,root);
        name_to_id[course_name]=course_id;
        time_to_place[time].first=campus; 
        time_to_place[time].second=place;
        time_to_id[time]=course_id;
    }
    ifs.close();
}

void Student::query_by_course_time(){
    int hour;
    int min;
    int date;
    int time;
    cout<<"\n 1:星期一";
    cout<<"\n 2：星期二";
    cout<<"\n 3：星期三";
    cout<<"\n 4：星期四";
    cout<<"\n 5：星期五";
    cout<<"\n 6：星期六";
    cout<<"\n 7：星期日"; 
     cout<<"\n请选择星期：";
    cin>>date;
    cout<<"\n请以格式 小时 ：分钟 输入时间,输入小时后按回车:\n";
    cin>>hour;
    cout<<":";
    cin>>min;
    time=(date-1)*1440+60*hour+min;
    int close_t;
    int r=rank(time,root);
   
    if(r!=cnt){
       close_t=kth(r,root);
    }
    else {close_t=kth(1,root);
    }
    cout<<time_to_place[close_t].first<<" "<<time_to_place[close_t].second;
}

void Student::set_activity(){
}

void Student::course_menu(string object_id,string object_name,string stu_id) {
    Course* cou=new Course(object_id,object_name,stu_id);
    cou->init();            //首先初始化类
    while (true) {
        cou->operMenu();
        int op;
        cin >> op;
        if (op == 1) {  
           cou->submit_homework();
        } else if (op == 2) {
            cou->submit_material();
        } else if (op == 3) {
            cou->download_material();
        } else if (op == 4) {
            cou->query_homework_by_name();
        }else if( op == 5 ) {
            cou->query_homework_by_grades();
        }else if( op == 6 ){
            cou->query_material_by_name();
        }else if( op == 7 ){
            cou->query_material_by_weight();
        }
            else if (op == 0) {
            delete cou;
            cout << "退出成功" << endl;
            system("pause");
            system("cls");
            return;
        } 
        else {
            cout << "\n无法识别的操作, 请重新输入: ";
            system("pause");
            system("cls");
        }
    }
}