#include "course.h"

#include <fstream>
Course::Course(string course_id, string course_name, string id) {
    this->course_id = course_id;
    this->course_name = course_name;
    this->user_id = id;
}
void Course::init() {
    string course_filename = "../../src/model/course_model/course_set/" + course_id + "_course.txt";
    ifstream ifs;
    ifs.open(course_filename, ios::in);

    if (!ifs.is_open()) {
        cout << "课程文件不存在" << endl;
        ifs.close();
        return;
    }

    ifs >> course_name >> times_per_week;
    for (int i = 1; i <= times_per_week; i++) {
        single_course a;
        string name, course_id, building_id;
        ifs >> a.date >> a.seq >> a.place >> name >> a.campus >> course_id >> building_id;
        a.sh = course_start_time_table[a.seq] / 60;
        a.sm = course_start_time_table[a.seq] % 60;
        a.fh = course_finish_time_table[a.seq] / 60;
        a.fm = course_finish_time_table[a.seq] % 60;
        course_table.push_back(a);
    }
    ifs >> teacher_name >> teacher_id >> course_qun >> total_weeks;
    ifs >> final.week >> final.date >> final.st_hour >> final.st_min >> final.fi_hour >> final.fi_min >> final.campus >> final.place;
    ifs >> ref_book_number;
    for (int i = 1; i <= ref_book_number; i++) {
        string book_name;
        ifs >> book_name;
        ref_books.push_back(book_name);
    }
    ifs >> material_number;
    string word;
    for (int i = 0; i <= material_number - 1; i++) {
        material a;
        ifs >> a.weight >> a.name >> a.id >> a.len;
        for (int j = 0; j <= a.len - 1; j++) {
            ifs >> word;
            a.words.insert(word);
        }
        materials.push_back(a);
        name_to_id[a.name] = a.id;
        order_materials.push_back(i);
    }
    ifs >> homework_number;

    for (int i = 1; i <= homework_number; i++) {
        ifs >> hws[i].name >> hws[i].len;
        for (int j = 0; j <= hws[i].len - 1; j++) {
            ifs >> word;
            hws[i].words.insert(word);
        }
    }
    ifs.close();
    string target, base = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/" + course_id + "_course/";
    for (int i = 1; i <= homework_number; i++) {
        target = base + to_string(i) + "_times/" + user_id + "_stu/" + "info.txt";
        ifs.open(target, ios::in);
        if (!ifs.is_open()) {
            cout << "作业文件不存在" << endl;
            ifs.close();
            return;
        }
        ifs >> hws[i].grades >> hws[i].state;
        order_hws.push_back(i);
        ifs.close();
    }
}

void Course::submit_homework() {
    // code1();
}
void Course::submit_material() {
}
void Course::download_material() {
}
void Course::query_homework_by_name() {
    string word;
    cout << "\n请输入您要搜索的作业名(请在任意两个字符之间加空格): ";
    vector<string> notes;
    do {
        cin >> word;
        notes.push_back(word);
    } while (cin.get() != '\n');
    cout << "\n作业查询结果: " << endl;
    bool empty = true;
    for (int i = 1; i <= homework_number; i++) {
        for (auto j = notes.begin(); j != notes.end(); j++) {
            bool flag = false;
            for (auto k = hws[i].words.begin(); k != hws[i].words.end(); k++) {
                if (*j == *k) {
                    flag = true;
                    empty = false;
                    cout << "作业名:" << hws[i].name << "  成绩:" << hws[i].grades << "  状态:" << hws[i].state << endl;
                    break;
                }
            }
            if (flag) break;
        }
    }
    if (empty) cout << "没有找到相关条目" << endl;
}
void Course::query_material_by_name() {
    string word;
    cout << "\n请输入您要搜索的资料名(请在任意两个字符之间加空格): ";
    vector<string> notes;
    do {
        cin >> word;
        notes.push_back(word);
    } while (cin.get() != '\n');
    cout << "\n资料查询结果: " << endl;
    bool empty = true;
    for (auto i = materials.begin(); i != materials.end(); i++) {
        for (auto j = notes.begin(); j != notes.end(); j++) {
            bool flag = false;
            for (auto k = i->words.begin(); k != i->words.end(); k++) {
                if (*j == *k) {
                    flag = true;
                    empty = false;
                    cout << "资料名:" << i->name << "  权重:" << i->weight << endl;
                    break;
                }
            }
            if (flag) break;
        }
    }
    if (empty) cout << "没有找到相关条目" << endl;
}
void Course::query_homework_by_grades() {
    qsort_h(1, homework_number);
    for (int i = 1; i <= homework_number; i++) {
        cout << "第" << order_hws[i] << "次作业"
             << "  " << hws[order_hws[i]].name << "  "
             << "成绩：" << hws[order_hws[i]].grades;
        cout << " 状态：" << hws[order_hws[i]].state << endl;
    }
    /*cout << "请输入Yes来提交作业或者输入No来退出:";
    string opt;
    cin >> opt;
    if (opt == "No")
        return;
    else
        submit_homework();*/
}
void Course::query_material_by_weight() {
    qsort_m(0, material_number - 1);
    for (int i = 0; i <= material_number - 1; i++) {
        cout << materials[order_materials[i]].name << "  权重：" << materials[order_materials[i]].weight << endl;
    }
    /*cout << "请输入Yes来下载某份资料或者输入No来退出:";
    string opt;
    cin >> opt;
    if (opt == "No")
        return;
    else
        download_material();*/
}

void Course::qsort_h(int l, int r) {
    int i = l, j = r, flag = hws[order_hws[(l + r) / 2]].grades, tmp;
    do {
        while (hws[order_hws[i]].grades > flag) i++;
        while (hws[order_hws[j]].grades < flag) j--;
        if (i <= j) {
            tmp = order_hws[i];
            order_hws[i] = order_hws[j];
            order_hws[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) qsort_h(l, j);
    if (i < r) qsort_h(i, r);
}

void Course::qsort_m(int l, int r) {
    int i = l, j = r, flag = materials[order_materials[(l + r) / 2]].weight, tmp;
    do {
        while (materials[order_materials[i]].weight > flag) i++;
        while (materials[order_materials[j]].weight < flag) j--;
        if (i <= j) {
            tmp = order_materials[i];
            order_materials[i] = order_materials[j];
            order_materials[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) qsort_m(l, j);
    if (i < r) qsort_m(i, r);
}
/*void Course::log(string sth) {
    logger addition = logger("stu", user_id, sth);
    loggers.push_back(addition);
}
void Course::submit() {
    ofstream ofs1;
    string log_file = "../../doc/stu";
    ofs1.open(log_file, ios::app);
    for (auto it = loggers.begin(); it != loggers.end(); it++) {
        ofs1 << it->now << " " << it->kind << " " << it->id << " " << it->sth << endl;
    }
    ofs1.close();
}*/
void Course::init2() {
    string course_filename = "../../src/model/course_model/course_set/" + course_id + "_course.txt";
    ifstream ifs;
    ifs.open(course_filename, ios::in);

    if (!ifs.is_open()) {
        cout << "课程文件不存在" << endl;
        ifs.close();
        return;
    }

    ifs >> course_name >> times_per_week;
    for (int i = 1; i <= times_per_week; i++) {
        single_course a;
        string name, course_id, building_id;
        ifs >> a.date >> a.seq >> a.place >> name >> a.campus >> course_id >> building_id;
        a.sh = course_start_time_table[a.seq] / 60;
        a.sm = course_start_time_table[a.seq] % 60;
        a.fh = course_finish_time_table[a.seq] / 60;
        a.fm = course_finish_time_table[a.seq] % 60;
        course_table.push_back(a);
    }
    ifs >> teacher_name >> teacher_id >> course_qun >> total_weeks;
    ifs >> final.week >> final.date >> final.st_hour >> final.st_min >> final.fi_hour >> final.fi_min >> final.campus >> final.place;
    ifs >> ref_book_number;
    for (int i = 1; i <= ref_book_number; i++) {
        string book_name;
        ifs >> book_name;
        ref_books.push_back(book_name);
    }
    ifs >> material_number;
    string word;
    for (int i = 0; i <= material_number - 1; i++) {
        material a;
        ifs >> a.weight >> a.name >> a.id >> a.len;
        for (int j = 0; j <= a.len - 1; j++) {
            ifs >> word;
            a.words.insert(word);
        }
        materials.push_back(a);
        name_to_id[a.name] = a.id;
        order_materials.push_back(i);
    }
    ifs >> homework_number;

    for (int i = 1; i <= homework_number; i++) {
        ifs >> hws[i].name >> hws[i].len;
        for (int j = 0; j <= hws[i].len - 1; j++) {
            ifs >> word;
            hws[i].words.insert(word);
        }
    }
    ifs >> stu_number;
    string id;
    for (int i = 1; i <= stu_number; i++) {
        ifs >> id;
        stus.push_back(id);
    }
    ifs.close();
}
