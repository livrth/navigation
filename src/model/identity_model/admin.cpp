#include "admin.h"

#include <fstream>
#include <iostream>
using namespace std;

Admin::Admin() {
}

Admin::Admin(string user_name) {
    this->user_name = user_name;
}

void Admin::change_activity() {
    int ca_number;
    string group_id;
    vector<single_activity_a> activities;
    cout << "请输入你想改变的班级的id:";
    cin >> group_id;
    string group_filename = "../../src/model/identity_model/group_set/" + group_id + "_group.txt";
    ifstream ifs;
    // cout<<"what"<<endl;
    ifs.open(group_filename, ios::in);
    if (!ifs.is_open()) {
        cout << "班级文件不存在" << endl;
        ifs.close();
        return;
    }
    ifs >> ca_number;
    for (int i = 1; i <= ca_number; i++) {
        single_activity_a a;
        ifs >> a.date >> a.sh >> a.sm >> a.fh >> a.fm >> a.place >> a.name;
        activities.push_back(a);
    }
    while (true) {
        cout << endl
             << "请做出选择：" << endl;
        cout << "1.删除活动 2.增加活动  3.提交并返回" << endl;
        int opt;
        cin >> opt;
        if (opt == 1) {
            cout << "请输入删除的这个活动的日期和开始时间" << endl;
            string date;
            int h, m;
            cin >> date >> h >> m;
            for (vector<single_activity_a>::iterator it = activities.begin(); it != activities.end(); it++) {
                if (it->date == date && it->sh * 60 + it->sm == h * 60 + m) {
                    activities.erase(it);
                    ca_number--;
                    break;
                }
            }
        } else if (opt == 2) {
            cout << "请输入增加的活动的日期,时间区间,地点和名字" << endl;
            single_activity_a n;
            cin >> n.date >> n.sh >> n.sm >> n.sh >> n.sm >> n.place >> n.name;
            activities.push_back(n);
            ca_number++;
        } else if (opt == 3) {
            ofstream ofs;
            ofs.open(group_filename, ios::out);
            if (!ofs.is_open()) {
                cout << "活动文件不存在" << endl;
                ofs.close();
                return;
            }
            ofs << ca_number << endl;
            for (int i = 0; i <= ca_number - 1; i++) {
                single_activity_a a = activities[i];
                ofs << a.date << " " << a.sh << " " << a.sm << " " << a.fh << " " << a.fm << " " << a.place << " " << a.name << endl;
            }
            ofs.close();
            return;
        }
    }
}

void Admin::change_course() {
    whole_course t;
    cout << "请输入你想改变的课程的id:";
    cin >> t.course_id;
    string course_filename = "../../src/model/course_model/course_set/" + t.course_id + "_course.txt";
    ifstream ifs;
    // cout<<"what"<<endl;
    ifs.open(course_filename, ios::in);
    if (!ifs.is_open()) {
        cout << "课程文件不存在" << endl;
        ifs.close();
        return;
    }
    ifs >> t.course_name >> t.number;
    for (int i = 1; i <= t.number; i++) {
        single_course_a a;
        ifs >> a.date >> a.seq >> a.place >> a.course_name >> a.campus >> a.course_id >> a.building_id;
        t.course_table.push_back(a);
    }
    ifs >> t.teacher_name >> t.teacher_id >> t.course_qun >> t.total_weeks;
    ifs >> t.final.week >> t.final.date >> t.final.sh >> t.final.sm >> t.final.fh >> t.final.fm >> t.final.campus >> t.final.place;
    ifs >> t.ref_book_number;
    for (int i = 1; i <= t.ref_book_number; i++) {
        string book_name;
        ifs >> book_name;
        t.ref_books.push_back(book_name);
        cout << book_name << endl;
    }
    // cout<<"fine"<<endl;
    ifs >> t.material_number;
    for (int i = 1; i <= t.material_number; i++) {
        material_a a;
        ifs >> a.weight >> a.name >> a.id;
        t.materials.push_back(a);
        cout << a.name << endl;
    }
    ifs >> t.homework_number;
    for (int i = 1; i <= t.homework_number; i++) {
        string homework_instruc;
        ifs >> homework_instruc;
        t.hws.push_back(homework_instruc);
    }
    // cout<<"ok"<<endl;
    ifs >> t.student_number;
    for (int i = 1; i <= t.student_number; i++) {
        string stu_id;
        ifs >> stu_id;
        t.stu_ids.push_back(stu_id);
    }
    ifs.close();
    while (true) {
        cout << endl
             << "请做出选择：" << endl;
        cout << "1.修改考试时间 2.修改考试地点 3.删除一堂课 4.增加一堂课 5.提交并返回" << endl;
        int opt;
        cin >> opt;
        if (opt == 1) {
            cout << "请输入考试的新时间：";
            cin >> t.final.date >> t.final.sh >> t.final.sm >> t.final.fh >> t.final.fm;
        } else if (opt == 2) {
            cout << "请输入考试的新地点:";
            cin >> t.final.campus >> t.final.place;
        } else if (opt == 3) {
            cout << "请输入删除的这堂课的日期和课序";
            string date;
            int seq;
            cin >> date >> seq;
            for (vector<single_course_a>::iterator it = t.course_table.begin(); it != t.course_table.end(); it++) {
                if (it->date == date && it->seq == seq) {
                    t.course_table.erase(it);
                    t.number--;
                    break;
                }
            }
            for (int i = 0; i <= t.student_number - 1; i++) {
                delete_course_table_term(t.stu_ids[i], date, seq);
            }
        } else if (opt == 4) {
            cout << "请输入增加的这堂课的日期,课序，教室，校区,建筑编号";
            single_course_a n;
            cin >> n.date >> n.seq >> n.place >> n.campus >> n.building_id;
            n.course_id = t.course_id;
            n.course_name = t.course_name;
            t.course_table.push_back(n);
            t.number++;
            for (int i = 0; i <= t.student_number - 1; i++) {
                add_course_table_term(t.stu_ids[i], n);
            }
        } else if (opt == 5) {
            ofstream ofs;
            ofs.open(course_filename, ios::out);
            if (!ofs.is_open()) {
                cout << "课程文件不存在" << endl;
                ofs.close();
                return;
            }
            ofs << t.course_name << endl
                << t.number << endl;
            for (int i = 0; i <= t.number - 1; i++) {
                single_course_a a = t.course_table[i];
                ofs << a.date << " " << a.seq << " " << a.place << " " << t.course_name << " " << a.campus << " " << t.course_id << " " << a.building_id << endl;
            }
            ofs << t.teacher_name << " " << t.teacher_id << endl
                << t.course_qun << endl
                << t.total_weeks << endl;
            ofs << t.final.week << " " << t.final.date << " " << t.final.sh << " " << t.final.sm << " " << t.final.fh << " " << t.final.fm << " " << t.final.campus << " " << t.final.place << " " << endl;
            ofs << t.ref_book_number << endl;
            for (int i = 0; i <= t.ref_book_number - 1; i++) {
                string book_name = t.ref_books[i];
                ofs << book_name << " " << endl;
            }
            ofs << t.material_number << endl;
            for (int i = 0; i <= t.material_number - 1; i++) {
                material_a a = t.materials[i];
                ofs << a.weight << " " << a.name << " " << a.id << " " << endl;
            }
            ofs << t.homework_number << endl;
            for (int i = 0; i <= t.homework_number - 1; i++) {
                string homework_instruc = t.hws[i];
                ofs << homework_instruc << " " << endl;
            }
            ofs << t.student_number << endl;
            for (int i = 0; i <= t.student_number - 1; i++) {
                string stu_id = t.stu_ids[i];
                ofs << stu_id << endl;
            }
            ofs.close();
            return;
        }
    }
}

void Admin::release_new_course() {
    whole_course t;
    cout << "请输入课程的名字,节数,id,每节课的构成,老师姓名,老师id,课程群，课时，考试信息,参考书目数目,参考书目,学生数目,学生id：" << endl;
    cin >> t.course_name >> t.number >> t.course_id;
    //输入
    for (int i = 1; i <= t.number; i++) {
        single_course_a a;
        cin >> a.date >> a.seq >> a.place >> a.course_name >> a.campus >> a.course_id >> a.building_id;
        t.course_table.push_back(a);
    }
    cin >> t.teacher_name >> t.teacher_id >> t.course_qun >> t.total_weeks;
    cin >> t.final.week >> t.final.date >> t.final.sh >> t.final.sm >> t.final.fh >> t.final.fm >> t.final.campus >> t.final.place;
    cin >> t.ref_book_number;
    for (int i = 1; i <= t.ref_book_number; i++) {
        string book_name;
        cin >> book_name;
        t.ref_books.push_back(book_name);
    }
    t.material_number = 0;
    t.homework_number = 0;
    cin >> t.student_number;
    for (int i = 1; i <= t.student_number; i++) {
        string stu_id;
        cin >> stu_id;
        t.stu_ids.push_back(stu_id);
    }
    //输出
    ofstream ofs;
    string path = "../../src/model/course_model/course_set/" + t.course_id + "_course.txt";
    ofs.open(path, ios::out);  //创建文件
    if (!ofs.is_open()) {
        cout << "课程创建失败" << endl;
        ofs.close();
        return;
    }
    ofs << t.course_name << endl
        << t.number << endl;
    for (int i = 0; i <= t.number - 1; i++) {
        single_course_a a = t.course_table[i];
        ofs << a.date << " " << a.seq << " " << a.place << " " << t.course_name << " " << a.campus << " " << t.course_id << " " << a.building_id << endl;
    }
    ofs << t.teacher_name << " " << t.teacher_id << endl
        << t.course_qun << endl
        << t.total_weeks << endl;
    ofs << t.final.week << " " << t.final.date << " " << t.final.sh << " " << t.final.sm << " " << t.final.fh << " " << t.final.fm << " " << t.final.campus << " " << t.final.place << " " << endl;
    ofs << t.ref_book_number << endl;
    for (int i = 0; i <= t.ref_book_number - 1; i++) {
        string book_name = t.ref_books[i];
        ofs << book_name << " " << endl;
    }
    ofs << t.material_number << endl;
    for (int i = 0; i <= t.material_number - 1; i++) {
        material_a a = t.materials[i];
        ofs << a.weight << " " << a.name << " " << a.id << " " << endl;
    }
    ofs << t.homework_number << endl;
    for (int i = 0; i <= t.homework_number - 1; i++) {
        string homework_instruc = t.hws[i];
        ofs << homework_instruc << " " << endl;
    }
    ofs << t.student_number << endl;
    for (int i = 0; i <= t.student_number - 1; i++) {
        string stu_id = t.stu_ids[i];
        ofs << stu_id << endl;
    }
    ofs.close();
    single_course_a n;
    for (int i = 1; i <= t.number - 1; i++) {
        n = t.course_table[i];
        for (int i = 0; i <= t.student_number - 1; i++) {
            add_course_table_term(t.stu_ids[i], n);
        }
    }
    string teacher_info_file = "../../src/identity_model/homework_set/" + t.teacher_id + "_teacher/course_collection.txt";
    ofs.open(teacher_info_file, ios::app);  //创建文件
    if (!ofs.is_open()) {
        cout << "教师文件打开失败" << endl;
        ofs.close();
        return;
    }
    ofs << t.course_id << endl;
    ofs.close();
}

void Admin::delete_course_table_term(string stu_id, string date, int seq) {
    string filename = "../../src/model/identity_model/course_table/" + stu_id + "_course_table.txt";
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs.is_open()) {
        cout << "学生" + stu_id + "课程文件不存在" << endl;
        ifs.close();
        return;
    }
    vector<single_course_a> course_table;
    single_course_a a;
    int cnt = 0;
    while (ifs >> a.date >> a.seq >> a.place >> a.course_name >> a.campus >> a.course_id >> a.building_id) {
        if (a.date != date && a.seq != seq) {
            course_table.push_back(a);
            cnt++;
        }
    }
    ifs.close();
    ofstream ofs;
    ofs.open(filename, ios::out);
    if (!ofs.is_open()) {
        cout << "学生" + stu_id + "课程文件不存在" << endl;
        ofs.close();
        return;
    }
    for (int i = 0; i <= cnt - 1; i++) {
        a = course_table[i];
        ofs << a.date << " " << a.seq << " " << a.place << " " << a.course_name << " " << a.campus << " " << a.course_id << " " << a.building_id << endl;
    }
    ofs.close();
}

void Admin::add_course_table_term(string stu_id, single_course_a n) {
    string filename = "../../src/model/identity_model/course_table/" + stu_id + "_course_table.txt";
    ifstream ifs;
    ifs.open(filename, ios::in);
    if (!ifs.is_open()) {
        cout << "学生" + stu_id + "课程文件不存在" << endl;
        ifs.close();
        return;
    }
    vector<single_course_a> course_table;
    single_course_a a;
    int cnt = 0;
    while (ifs >> a.date >> a.seq >> a.place >> a.course_name >> a.campus >> a.course_id >> a.building_id) {
        course_table.push_back(a);
        cnt++;
    }
    ifs.close();
    course_table.push_back(n);
    ofstream ofs;
    ofs.open(filename, ios::out);
    if (!ofs.is_open()) {
        cout << "学生" + stu_id + "课程文件不存在" << endl;
        ofs.close();
        return;
    }
    for (int i = 0; i <= cnt; i++) {
        a = course_table[i];
        ofs << a.date << " " << a.seq << " " << a.place << " " << a.course_name << " " << a.campus << " " << a.course_id << " " << a.building_id << endl;
    }
    ofs.close();
}
