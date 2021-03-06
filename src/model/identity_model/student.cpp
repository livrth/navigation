#include "student.h"

#include <fstream>
#include <iostream>

#include "course.h"
#include "guide.h"

using namespace std;

Student::Student(string id, string name, string group) {
    this->stu_id = id;
    this->stu_name = name;
    this->group_id = group;
}

void Student::query_by_course_name() {
    string word;
    cout << "\n请输入您要搜索的课程名(请在任意两个字符之间加空格):";
    set<string> notes;
    bool empty = true;
    do {
        cin >> word;
        for (auto it = word_to_sen[word].begin(); it != word_to_sen[word].end(); it++) {
            if (notes.find(*it) == notes.end()) {
                notes.insert(*it);
                cout << *it << endl;
                empty = false;
            }
        }
    } while (cin.get() != '\n');
    if (empty) {
        cout << "没有找到相关条目" << endl;
        return;
    }
    string object_id, object_name;
    cout << endl
         << "现在请输入完整的课程名：" << endl;
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
    log("query_by_course_name" + object_name);
    system("pause");
    system("cls");
    course_menu(object_id, object_name, this->stu_id);
}

void Student::query_by_course_table() {
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t课程表" << endl;
    cout << "    ";
    for (int i = 1; i <= 11; i++) cout << "    "
                                       << "第" << i << "节"
                                       << "    ";
    cout << endl;
    cout << "   |08:00-08:45 |08:50-09:35 |09:50-10:35 |10:40-11:25 |11:35-12:15 |13:00-13:45 ";
    cout << "|13:50-14:35 |14:45-15:30 |15:40-16:25 |16:35-17:20 |17:25-18:10 |" << endl;
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
    log("query_by_course_table" + object_name);
    system("pause");
    system("cls");
    course_menu(object_id, object_name, this->stu_id);
}

// void Student::upload_course_material() {
// }

//和 navigation_model 交互
void Student::guide_now() {
    // cout << endl;
    // cout << "请输入您当前所在的校区(沙河/西土城): ";
    // string campus_now_in;
    // cin >> campus_now_in;

    Guide guide(this->stu_id);
    while (true) {
        guide.guideOperMenu();
        cout << "请输入您的操作: ";
        int op;
        cin >> op;
        if (op == 1) {
            guide.print_path_by_course();
            log("guide_by_course");
        } else if (op == 2) {
            guide.print_path_by_location();
            log("guide_by_location");
        } else if (op == 3) {
            guide.print_path_by_time();
            log("guide_by_time");
        } else if (op == 4) {
            guide.print_path_by_fixed_building();
            log("guide_by_multi_place");
        } else if (op == 0) {
            cout << "\n退出成功!\n"
                 << endl;
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
    string date, place, course_name, course_id, campus, word;
    int seq, building_id, sen_len;
    t1[root = ++cnt1] = Node(0, 0, 1, 2147483647);
    while (ifs >> date >> seq >> place >> course_name >> campus >> course_id >> building_id >> sen_len) {
        for (int i = 1; i <= sen_len; i++) {
            ifs >> word;
            word_to_sen[word].insert(course_name);
        }
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
    while (ifs1 >> x.date >> x.sh >> x.sm >> x.fh >> x.fm >> x.place >> x.name >> x.clock_state >> x.len) {
        x.words.clear();
        for (int i = 0; i <= x.len - 1; i++) {
            ifs1 >> word;

            x.words.push_back(word);
            word_to_par[word].insert(x.name);
            // cout << word << x.name << endl;
        }
        x.state = 'p';
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
        ifs2 >> x.date >> x.sh >> x.sm >> x.fh >> x.fm >> x.place >> x.name >> x.len;
        for (int i = 0; i <= x.len - 1; i++) {
            ifs2 >> word;
            x.words.push_back(word);
            word_to_par[word].insert(x.name);
            // cout << word << x.name << endl;
        }
        x.clock_state = "circular_clock";
        x.state = 'c';
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
        time_to_activity[time].push_back(x);
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
    cout << "\n请以格式 小时 ：分钟 输入时间,输入小时后请按回车:\n";
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
    log("query_by_course_time" + to_string(date) + "th" + to_string(hour) + ":" + to_string(min));
}

void Student::course_menu(string object_id, string object_name, string stu_id) {
    Course *cou = new Course(object_id, object_name, stu_id);
    cou->init();  //首先初始化类
    while (true) {
        cou->operMenu();
        int op;
        cin >> op;
        if (op == 1) {
            log("submit_homework");

            cou->submit_homework();

        } else if (op == 2) {
            log("submit_material");

            cou->submit_material();

        } else if (op == 3) {
            log("download_material");

            cou->download_material();

        } else if (op == 4) {
            log("query_homework_by_name");

            cou->query_homework_by_name();
            system("pause");
            system("cls");
        } else if (op == 5) {
            log("query_homework_by_grades");

            cou->query_homework_by_grades();
            system("pause");
            system("cls");
        } else if (op == 6) {
            log("query_material_by_name");

            cou->query_material_by_name();
            system("pause");
            system("cls");
        } else if (op == 7) {
            log("query_material_by_weight");

            cou->query_material_by_weight();
            system("pause");
            system("cls");
        } else if (op == 0) {
            // cou->submit();
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
        cout << kind[it->state] << " "
             << "闹钟属性：" << it->clock_state << endl;
    }
    log("query_by_activity_time_" + to_string(date) + "th" + to_string(hour) + ":" + to_string(min));
}

void Student::query_by_activity_name() {
    string word, name;
    cout << "\n请输入您要搜索的活动名（请在任意两个字符之间加空格）:";
    set<single_activity> notes;
    do {
        cin >> word;
        name += word;
        for (auto p = word_to_par[word].begin(); p != word_to_par[word].end(); p++) {
            vector<single_activity> to_find = name_to_activity[*p];
            for (auto it = to_find.begin(); it != to_find.end(); it++) {
                if (notes.find(*it) == notes.end()) {
                    notes.insert(*it);
                    cout << "活动时间：" << it->date << it->sh << ":" << it->sm << "-" << it->fh << ":" << it->fm << " ";
                    cout << "活动地点:" << it->place << " "
                         << "活动名称：" << it->name << " "
                         << "活动类型：";
                    cout << kind[it->state] << " "
                         << "闹钟属性：" << it->clock_state << endl;
                }
            }
        }
    } while (cin.get() != '\n');
    log("query_by_activity_name" + name);
}
void Student::set_activity() {
    cout << "请输入活动的日期：";
    single_activity x;
    // int sh, sm, fh, fm;  //unused variable warning
    int time;
    int date;
    string place, name, word;
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入活动开始时间,输入小时后按回车:\n";
    cin >> x.sh;
    cout << ":";
    cin >> x.sm;
    cout << "\n请以格式 小时 ：分钟 输入活动结束时间,输入小时后按回车:\n";
    cin >> x.fh;
    cout << ":";
    cin >> x.fm;
    time = (date - 1) * 1440 + 60 * x.sh + x.sm;
    cout << "请输入活动地点：";
    cin >> x.place;
    cout << "请输入活动名字（请将任意字符用空格分离）：";
    x.len = 0;
    x.name = "";
    do {
        cin >> word;
        cout << word << endl;
        x.words.push_back(word);
        x.name += x.words[x.len];
        x.len++;

    } while (cin.get() != '\n');
    x.clock_state = "circular_clock";
    x.state = 'p';
    x.date = number_to_date[date];
    insert(time, root, t2, cnt2);
    name_to_activity[x.name].push_back(x);
    time_to_activity[time].push_back(x);
    clash_test(number_to_date[date], x.sh * 60 + x.sm, x.fh * 60 + x.fm);
    cout << "活动设置完毕" << endl;
    log("set_activity_" + x.name);
}
void Student::delete_activity() {
    cout << "请输入你想删除的活动的开始时间：";
    int date, sh, sm, time;
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入活动开始时间,输入小时后按回车:\n";
    cin >> sh;
    cout << ":";
    cin >> sm;
    time = (date - 1) * 1440 + 60 * sh + sm;
    if (time_to_activity[time].empty()) {
        cout << "不存在这样的活动，请重试" << endl;
        return;
    }

    string description;

    bool flag = false;
    while (!flag) {
        cout << "请输入欲删除活动的完整描述,并注意只有还没有删除过的个人活动才可以删除(输入0可退出):";
        cin >> description;
        if (description == "0") return;
        for (vector<single_activity>::iterator it = time_to_activity[time].begin(); it != time_to_activity[time].end(); ++it) {
            if (it->name == description && it->state == 'p') {
                it->state = 'd';
                flag = true;
                break;
            }
        }
    }
    cout << "活动删除完毕" << endl;
    log("delete_activity_" + description);
}
void Student::change_activity() {
    cout << "请输入你想改变的活动的开始时间：";
    int date, sh, sm, time;
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入活动开始时间,输入小时后按回车:\n";
    cin >> sh;
    cout << ":";
    cin >> sm;
    time = (date - 1) * 1440 + 60 * sh + sm;
    if (time_to_activity[time].empty()) {
        cout << "不存在这样的活动，请重试" << endl;
        return;
    }

    string name, place;
    vector<string> words;
    int len;
    bool flag = false;
    while (!flag) {
        cout << "请输入完整的活动描述,并注意只有还没有删除过的个人活动才可以更改(输入0可退出):";
        cin >> name;
        if (name == "0") return;
        for (vector<single_activity>::iterator it = time_to_activity[time].begin(); it != time_to_activity[time].end(); ++it) {
            if (it->name == name && it->state == 'p') {
                it->state = 'd';
                len = it->len;
                for (auto c : it->words) words.push_back(c);
                flag = true;
                break;
            }
        }
    }
    single_activity y;
    cout << "请输入改变后活动的地点:";
    cin >> y.place;
    cout << "请输入改变后的活动的开始时间：";
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入活动开始时间,输入小时后按回车:\n";
    cin >> y.sh;
    cout << ":";
    cin >> y.sm;
    cout << "\n请以格式 小时 ：分钟 输入活动结束时间,输入小时后按回车:\n";
    cin >> y.fh;
    cout << ":";
    cin >> y.fm;
    y.name = name;
    y.state = 'p';
    y.clock_state = "circular_clock";
    y.date = number_to_date[date];
    y.len = len;
    for (auto c : words) y.words.push_back(c);
    time = (date - 1) * 1440 + 60 * y.sh + y.sm;
    insert(time, root, t2, cnt2);
    name_to_activity[y.name].push_back(y);
    time_to_activity[time].push_back(y);
    clash_test(y.date, y.sh * 60 + sm, y.fh * 60 + y.fm);
    cout << "活动改变完毕" << endl;
    log("change_activity" + name);
}

void Student::clash_test(string date, int st, int ft) {
    /*for(int i=1;i<=cnt2;i++){
        vector<single_activity> x=time_to_activity[t2[i].value];
        for (vector<single_activity>::iterator it = x.begin(); it != x.end(); ++it) {
            if(it->state != 'd' && it->date == date && interact(it->sh*60+it->sm,it->fh*60+it->fm,st,ft)){
              cout << "检测到冲突!"<<endl;
              return;
            }
        }
    }*/
    for (int i = 1; i <= 5; i++) {
        if (number_to_date[i] == date) {
            for (int seq = 1; seq <= 11; seq++) {
                if (my_course_table[i][seq] != "NULL" && interact(course_start_time_table[seq], course_finish_time_table[seq], st, ft)) {
                    cout << "检测到冲突!" << endl;
                    return;
                }
            }
        }
    }
    cout << "未检测到与课程的冲突" << endl;
}
bool Student::interact(int x1, int x2, int y1, int y2) {
    return (x1 + y1 - x2 - y2 <= x1 + x2 - y1 - y2) && (x1 + x2 - y1 - y2 <= x2 + y2 - x1 - y1);
}
void Student::set_activity_alarm() {
    cout << "请输入你想改变的活动的开始时间：";
    int date, sh, sm, time;
    cout << "\n 1: 星期一";
    cout << "\n 2: 星期二";
    cout << "\n 3: 星期三";
    cout << "\n 4: 星期四";
    cout << "\n 5: 星期五";
    cout << "\n 6: 星期六";
    cout << "\n 7: 星期日";
    cout << "\n请选择星期: ";
    cin >> date;
    cout << "\n请以格式 小时 ：分钟 输入活动开始时间,输入小时后按回车:\n";
    cin >> sh;
    cout << ":";
    cin >> sm;
    time = (date - 1) * 1440 + 60 * sh + sm;
    if (time_to_activity[time].empty()) {
        cout << "不存在这样的活动，请重试" << endl;
        return;
    }

    string name, place;

    bool flag = false;
    while (!flag) {
        cout << "请输入完整的活动描述,并注意只有还没有删除过的个人活动才可以更改(输入0可退出):";
        cin >> name;
        if (name == "0") return;
        for (vector<single_activity>::iterator it = time_to_activity[time].begin(); it != time_to_activity[time].end(); ++it) {
            if (it->name == name && it->state == 'p') {
                cout << "请输入改变后的闹钟类型(只有no_clock,circular_clock,once_clock三种选项):";
                // m_lock.lock();
                cin >> it->clock_state;
                // m_lock.unlock();
                flag = true;
                break;
            }
        }
    }
    cout << "闹钟设置完毕" << endl;

    log("set_activity_alarm_for_" + name);
}
void Student::submit() {
    ofstream ofs;
    string activity_table_filename = "../../src/model/identity_model/activity_table/" + stu_id + "_activity_table.txt";
    ofs.open(activity_table_filename);
    for (int i = 1; i <= cnt2; i++) {
        vector<single_activity> x = time_to_activity[t2[i].value];
        for (vector<single_activity>::iterator it = x.begin(); it != x.end(); ++it) {
            if (it->state == 'p') {
                ofs << it->date << " " << it->sh << " " << it->sm << " " << it->fh << " " << it->fm << " ";
                ofs << it->place << " " << it->name << " " << it->clock_state << " " << it->len;
                for (int i = 0; i <= it->len - 1; i++) {
                    ofs << " " << it->words[i];
                }
                ofs << endl;
            }
        }
    }
    ofs.close();
    ofstream ofs1;
    string log_file = "../../log/stu.txt";
    ofs1.open(log_file, ios::app);
    for (auto it = loggers.begin(); it != loggers.end(); it++) {
        ofs1 << it->now << " " << it->kind << " " << it->id << " " << it->sth << endl;
    }
    ofs1.close();
}
void Student::log(string sth) {
    logger addition = logger("stu", stu_id, sth);
    loggers.push_back(addition);
}
void Student::typequery() {
    cout << "请输入查询类型：";
    string t;
    cin >> t;
    cout << endl;
    if (t == "班级") {
        for (int i = 1; i <= cnt2 - 1; i++) {
            vector<single_activity> x = time_to_activity[kth(i, root, t2)];
            for (vector<single_activity>::iterator it = x.begin(); it != x.end(); ++it) {
                if (kind[it->state] == "班级") {
                    cout << "活动时间：" << it->date << it->sh << ":" << it->sm << "-" << it->fh << ":" << it->fm << "    ";
                    cout << "活动地点:" << it->place << "    "
                         << "活动名称：" << it->name << "    "
                         << "活动类型：";
                    cout << kind[it->state] << "     "
                         << "闹钟属性：" << it->clock_state << endl;
                    clash_test(it->date, it->sh * 60 + it->sm, it->fh * 60 + it->fm);
                }
            }
        }
    } else {
        for (int i = 1; i <= cnt2 - 1; i++) {
            vector<single_activity> x = time_to_activity[kth(i, root, t2)];
            for (vector<single_activity>::iterator it = x.begin(); it != x.end(); ++it) {
                if (kind[it->state] == "个人") {
                    cout << "活动时间：" << it->date << it->sh << ":" << it->sm << "-" << it->fh << ":" << it->fm << "    ";
                    cout << "活动地点:" << it->place << "    "
                         << "活动名称：" << it->name << "    "
                         << "活动类型：";
                    cout << kind[it->state] << "     "
                         << "闹钟属性：" << it->clock_state << endl;
                    clash_test(it->date, it->sh * 60 + it->sm, it->fh * 60 + it->fm);
                }
            }
        }
    }
    log("query_activity_by_type" + t);
}