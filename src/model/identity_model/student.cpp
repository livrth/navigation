#include "student.h"

#include <fstream>

#include "course.h"
#include "guide.h"
Student::Student() {
}

Student::Student(string id, string name, string group) {
    this->stu_id = id;
    this->stu_name = name;
    this->group_id = group;
}

void Student::query_by_course_name() {
}

void Student::query_by_course_table() {
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t课程表" << endl;
    cout << "    ";
    for (int i = 1; i <= 11; i++) cout << "    "
                                       << "第" << i << "节"
                                       << "    ";
    cout << endl;
    for (int i = 1; i <= 5; i++) {
        cout << number_to_date[i] + "|";
        for (int seq = 1; seq <= 11; seq++) {
            if (my_course_table[i][seq] != "NULL") {
                int blank_number = 12 - my_course_table[i][seq].length();
                cout << my_course_table[i][seq];
                for (int j = 1; j <= blank_number; j++) cout << " ";
            } else {
                int blank_number = 12;
                for (int j = 1; j <= blank_number; j++) cout << " ";
            }
            cout << "|";
        }
        cout << endl;
    }
    string object_name;
    string object_id;
    cout << endl
         << "请输入想要进入的课程名称：" << endl;
    cin >> object_name;
    while (true) {
        if (name_to_id.find(object_name) == name_to_id.end()) {
            cout << "请输入正确的名称：" << endl;
            cin >> object_name;
        } else {
            object_id = name_to_id[object_name];
            break;
        }
    }
    course_menu(object_id, object_name, this->stu_id);
}

// void Student::upload_course_material() {
// }

//和 navigation_model 交互
void Student::guide_now() {
    cout << endl;
    cout << "请输入您当前所在的校区(沙河/西土城): ";
    string campus_now_in;
    cin >> campus_now_in;

    Guide guide(campus_now_in, this->stu_id);
    // guide.build_graph(campus_now_in);  //建图
    guide.guideOperMenu();
    cout << "请输入您需要导航的模式: ";
    int op;
    cin >> op;
    if (op == 1) {
        guide.print_path_by_course();
    } else if (op == 2) {
        guide.print_path_by_location();
    } else if (op == 3) {
        guide.print_path_by_time();
    } else if (op == 0) {
        cout << "退出成功" << endl;
        system("pause");
        system("cls");
        return;
    } else {
        cout << "\n无法识别的操作, 请重新输入: ";
        system("pause");
        system("cls");
    }
}

// void Student::upload_home_work() {
// }

void Student::update(int root, Node *t) {
    t[root].size = t[t[root].left].size + t[t[root].right].size + t[root].num;
}

int Student::rank(int x, int root, Node *t) {
    if (root) {
        if (x < t[root].value)
            return rank(x, t[root].left, t);
        if (x > t[root].value)
            return rank(x, t[root].right, t) + t[t[root].left].size + t[root].num;
        return t[t[root].left].size + t[root].num;
    }
    return 1;
}

int Student::kth(int x, int root, Node *t) {
    if (x <= t[t[root].left].size) return kth(x, t[root].left, t);
    if (x <= t[t[root].left].size + t[root].num) return t[root].value;
    return kth(x - t[t[root].left].size - t[root].num, t[root].right, t);
}

void Student::insert(int x, int root, Node *t, int &cnt) {
    if (x < t[root].value)
        if (!t[root].left)
            t[t[root].left = ++cnt] = Node(0, 0, 1, x);
        else
            insert(x, t[root].left, t, cnt);
    else if (x > t[root].value)
        if (!t[root].right)
            t[t[root].right = ++cnt] = Node(0, 0, 1, x);
        else
            insert(x, t[root].right, t, cnt);
    else
        t[root].num++;
    update(root, t);
}

void Student::init() {
    string courese_table_filename = "../../src/model/identity_model/course_table/" + stu_id + "_course_table.txt";
    ifstream ifs;
    ifs.open(courese_table_filename, ios::in);
    if (!ifs.is_open()) {
        cout << "用户课程文件不存在" << endl;
        ifs.close();
        return;
    }
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 11; j++)
            my_course_table[i][j] = "NULL";
    string date, place, course_name, course_id, campus;
    int seq, building_id;
    t1[root = ++cnt1] = Node(0, 0, 1, 2147483647);
    while (ifs >> date >> seq >> place >> course_name >> campus >> course_id >> building_id) {
        int time = 0;
        if (date.find("Mon") != std::string::npos) {
            time += 0;
            my_course_table[1][seq] = course_name;
        } else if (date.find("Tue") != std::string::npos) {
            time += 24 * 60;
            my_course_table[2][seq] = course_name;
        } else if (date.find("Wed") != std::string::npos) {
            time += 48 * 60;
            my_course_table[3][seq] = course_name;
        } else if (date.find("Thu") != std::string::npos) {
            time += 72 * 60;
            my_course_table[4][seq] = course_name;
        } else if (date.find("Fri") != std::string::npos) {
            time += 96 * 60;
            my_course_table[5][seq] = course_name;
        }
        time += course_start_time_table[seq];
        insert(time, root, t1, cnt1);
        name_to_id[course_name] = course_id;
        time_to_place[time].first = campus;
        time_to_place[time].second = place;
    }
    ifs.close();

    ifstream ifs1;
    string activity_table_filename = "../../src/model/identity_model/activity_table/" + stu_id + "_activity_table.txt";
    ifs1.open(activity_table_filename, ios::in);
    if (!ifs1.is_open()) {
        cout << "用户活动文件不存在" << endl;
        ifs1.close();
        return;
    }
    t2[root = ++cnt2] = Node(0, 0, 1, 2147483647);
    single_activity x;
    while (ifs1 >> x.date >> x.sh >> x.sm >> x.fh >> x.fm >> x.place >> x.name >> x.clock_state) {
        x.porc = 'p';
        name_to_activity[x.name].push_back(x);
        int time = x.sh * 60 + x.sm;
        if (x.date.find("Mon") != std::string::npos) {
            time += 0;
        } else if (x.date.find("Tue") != std::string::npos) {
            time += 24 * 60;
        } else if (x.date.find("Wed") != std::string::npos) {
            time += 48 * 60;
        } else if (x.date.find("Thu") != std::string::npos) {
            time += 72 * 60;
        } else if (x.date.find("Fri") != std::string::npos) {
            time += 96 * 60;
        } else if (x.date.find("Sar") != std::string::npos) {
            time += 120 * 60;
        } else if (x.date.find("Sun") != std::string::npos) {
            time += 144 * 60;
        }
        time_to_activity[time].push_back(x);
        insert(time, root, t2, cnt2);
    }
    ifs1.close();

    ifstream ifs2;
    string group_table_filename = "../../src/model/identity_model/group_set/" + group_id + "_group.txt";
    ifs2.open(group_table_filename, ios::in);
    if (!ifs2.is_open()) {
        cout << "用户班级文件不存在" << endl;
        ifs2.close();
        return;
    }
    ifs2 >> ca_number;
    for (int i = 1; i <= ca_number; i++) {
        ifs2 >> x.date >> x.sh >> x.sm >> x.fh >> x.fm >> x.place >> x.name;
        x.clock_state = "circular_clock";
        x.porc = 'c';
        name_to_activity[x.name].push_back(x);
        int time = x.sh * 60 + x.sm;
        if (date.find("Mon") != std::string::npos) {
            time += 0;
        } else if (date.find("Tue") != std::string::npos) {
            time += 24 * 60;
        } else if (date.find("Wed") != std::string::npos) {
            time += 48 * 60;
        } else if (date.find("Thu") != std::string::npos) {
            time += 72 * 60;
        } else if (date.find("Fri") != std::string::npos) {
            time += 96 * 60;
        } else if (date.find("Sar") != std::string::npos) {
            time += 120 * 60;
        } else if (date.find("Sun") != std::string::npos) {
            time += 144 * 60;
        }
        insert(time, root, t2, cnt2);
        time_to_activity[x.sh * 60 + x.sm].push_back(x);
    }
    ifs2.close();
}

void Student::query_by_course_time() {
    int hour;
    int min;
    int date;
    int time;
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入时间,输入小时后按回车:\n";
    cin >> hour;
    cout << ":";
    cin >> min;
    time = (date - 1) * 1440 + 60 * hour + min;
    int close_t;
    int r = rank(time, root, t1);
    if (r != cnt2)
        close_t = kth(r, root, t1);
    else
        close_t = kth(1, root, t1);
    cout << time_to_place[close_t].first << " " << time_to_place[close_t].second;
}

void Student::course_menu(string object_id, string object_name, string stu_id) {
    Course *cou = new Course(object_id, object_name, stu_id);
    cou->init();  //首先初始化类
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
        } else if (op == 5) {
            cou->query_homework_by_grades();
        } else if (op == 6) {
            cou->query_material_by_name();
        } else if (op == 7) {
            cou->query_material_by_weight();
        } else if (op == 0) {
            delete cou;
            cout << "退出成功" << endl;
            system("pause");
            system("cls");
            return;
        } else {
            cout << "\n无法识别的操作, 请重新输入: ";
            system("pause");
            system("cls");
        }
    }
}

void Student::query_by_activity_time() {
    int hour;
    int min;
    int date;
    int time;
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入时间,输入小时后按回车:\n";
    cin >> hour;
    cout << ":";
    cin >> min;
    time = (date - 1) * 1440 + 60 * hour + min;
    int close_t;
    int r = rank(time, root, t2);
    if (r != cnt2)
        close_t = kth(r, root, t2);
    else
        close_t = kth(1, root, t2);
    vector<single_activity> result = time_to_activity[close_t];
    for (vector<single_activity>::iterator it = result.begin(); it != result.end(); ++it) {
        cout << "活动时间：" << it->date << it->sh << ":" << it->sm << "-" << it->fh << ":" << it->fm << " ";
        cout << "活动地点:" << it->place << " "
             << "活动名称：" << it->name << " "
             << "活动类型：";
        cout << kind[it->porc] << " "
             << "闹钟属性：" << it->clock_state << endl;
    }
    /*single_activity x=time_to_activity[close_t];
    cout<<"活动时间："<<x.date<<x.sh<<":"<<x.sm<<"-"<<x.fh<<":"<<x.fm<<" ";
        cout<<"活动地点:"<<x.place<<" "<<"活动名称："<<x.name<<" "<<"活动类型：";
        cout<<kind[x.porc]<<" "<<"闹钟属性："<<x.clock_state<<endl;*/
}

void Student::query_by_activity_name() {
}
void Student::activity_menu() {}
void Student::set_activity() {}
void Student::delete_activity() {}
void Student::change_activity() {}
void Student::set_activity_alarm() {}
