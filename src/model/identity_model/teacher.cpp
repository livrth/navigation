#include "teacher.h"

#include <direct.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../global_file.h"
#include "course.h"
using namespace std;

Teacher::Teacher() {
}

Teacher::Teacher(string id, string name) {
    this->teacher_id = id;
    this->name = name;
    string course_collection = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/course_collection.txt";
    ifstream ifs1;
    ifs1.open(course_collection, ios::in);
    if (!ifs1.is_open()) {
        cout << "用户文件不存在" << endl;
        ifs1.close();
        return;
    }
    string name0, id0;
    while (ifs1 >> name0 >> id0) name_to_id[name0] = id0;
    ifs1.close();
}

//解压缩算法
void Teacher::loadZip(const char* pathname) {
    ifstream in;
    int nch;
    in.open(pathname, ios::binary);
    nch = in.get();
    if (!nch) nch = 256;
    for (int i = 0; i < 4; ++i) {
        unsigned int tmp = in.get();
        unzip_lenstr <<= 8;
        unzip_lenstr += tmp;
    }
    int sum_code = 0;
    for (int i = 1; i <= nch; ++i) {
        unzip_chlen[i].first = in.get();
        unzip_chlen[i].second = in.get();
        sum_code += unzip_chlen[i].second;
    }
    int len_bit = sum_code / 8 + (sum_code % 8 != 0);
    char* buf = new char[len_bit];
    in.read(buf, len_bit);
    for (int i = 0; i < len_bit; ++i)
        unzip_text += charToStr(buf[i]);
    //buildCodeTable(sum_code);

    int now = 1;
    for (int i = 0; i < sum_code; ++i) {
        char now_char = unzip_chlen[now].first;
        unzip_code[now_char] += unzip_text[i];
        if ((int)unzip_code[now_char].length() == unzip_chlen[now].second) {
            unzip_decode[unzip_code[now_char]] = now_char;
            now++;
        }
    }



    delete[] buf;
    unzip_text.clear();
    len_bit = unzip_lenstr / 8 + (unzip_lenstr % 8 != 0);
    buf = new char[len_bit];
    in.read(buf, len_bit);
    for (int i = 0; i < len_bit; ++i) unzip_text += charToStr(buf[i]);
    delete[] buf;
    in.close();
}

void Teacher::unzip(const char* pathname) {
    ofstream out;
    out.open(pathname, ios::binary);
    string now;
    for (int i = 0; i < (int)unzip_lenstr; ++i) {
        now += unzip_text[i];
        if (unzip_decode.count(now)) {
            out.put(unzip_decode[now]);
            now.clear();
        }
    }
}

// void Teacher::buildCodeTable(int n) {
//     int now = 1;
//     for (int i = 0; i < n; ++i) {
//         char now_char = unzip_chlen[now].first;
//         unzip_code[now_char] += unzip_text[i];
//         if ((int)unzip_code[now_char].length() == unzip_chlen[now].second) {
//             unzip_decode[unzip_code[now_char]] = now_char;
//             now++;
//         }
//     }
// }

string Teacher::charToStr(char x) {
    string res;
    for (int i = 0; i < 8; ++i) {
        if (x & 1)
            res += '1';
        else
            res += '0';
        x >>= 1;
    }
    reverse(res.begin(), res.end());
    return res;
}

void Teacher::decompress(string course, string time, vector<string> ids) {
    char path0[200];
    if (!getcwd(path0, 200)) {
        cout << "Get path fail!" << endl;
        return;
    }
    string path = path0;
    int eff = path.find("\\build\\build");
    path.erase(path.begin() + eff, path.end());
    string folderPath, target;
    //  string target, base = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/" + course_id + "_course/" + time + "_times/";
    folderPath = path + "\\src\\model\\identity_model\\homework_set\\" + teacher_id + "_teacher\\" + name_to_id[course] + "_course\\" + time + "_times";
    for (auto id : ids) {
        target = folderPath + "\\" + id + "_stu" + "\\hw_zip.txt";
        loadZip(target.c_str());
        int pos = target.find_last_of('.');
        string str1 = target.substr(0, pos);
        str1 += "_unzip.txt";
        unzip(str1.c_str());
        unzip_code.clear();
        unzip_decode.clear();
        unzip_text.clear();
    }

    
}
//解压缩

void Teacher::set_homework() {
    string course_name, course_id, time;
    cout << "请输入该课程的名称: " << endl;
    cin >> course_name;
    course_id = name_to_id[course_name];
    cout << "请输入您要布置的作业次数: " << endl;
    cin >> time;
    whole_course_t t;
    t.course_id = name_to_id[course_name];
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
        single_course_t a;
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
        // cout << book_name << endl;
    }
    // cout<<"fine"<<endl;
    ifs >> t.material_number;
    string word;
    for (int i = 1; i <= t.material_number; i++) {
        material_t a;
        ifs >> a.weight >> a.name >> a.id >> a.len;
        for (int i = 0; i <= a.len - 1; i++) {
            ifs >> word;
            a.words.push_back(word);
        }
        t.materials.push_back(a);
        // cout << a.name << endl;
    }
    ifs >> t.homework_number;
    for (int i = 1; i <= t.homework_number; i++) {
        hw_t a;
        ifs >> a.name >> a.len;
        for (int j = 0; j <= a.len - 1; j++) {
            ifs >> word;
            a.words.push_back(word);
        }
        t.hws.push_back(a);
    }
    // cout<<"ok"<<endl;
    ifs >> t.student_number;
    for (int i = 1; i <= t.student_number; i++) {
        string stu_id;
        ifs >> stu_id;
        t.stu_ids.push_back(stu_id);
    }
    ifs.close();
    // Course cou = Course(course_id, course_name, teacher_id);
    // cou.init2();
    char path0[200];
    if (!getcwd(path0, 200)) {
        cout << "Get path fail!" << endl;
        return;
    }
    string path = path0;
    int eff = path.find("\\build\\build");
    path.erase(path.begin() + eff, path.end());
    string folderPath, target;
    //  string target, base = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/" + course_id + "_course/" + time + "_times/";
    folderPath = path + "\\src\\model\\identity_model\\homework_set\\" + teacher_id + "_teacher\\" + course_id + "_course\\" + time + "_times";
    // cout << folderPath << endl;
    if (0 != access(folderPath.c_str(), 0)) {
        mkdir(folderPath.c_str());
    }
    string end[4];
    ofstream location_out;
    for (int i = 0; i <= t.student_number - 1; i++) {
        target = folderPath + "\\" + t.stu_ids[i] + "_stu";
        // cout << target << endl;
        if (0 != access(target.c_str(), 0)) {
            mkdir(target.c_str());
        }

        end[0] = target + "\\hw.txt";
        location_out.open(end[0], std::ios::out | std::ios::app);
        location_out.close();

        end[1] = target + "\\info.txt";
        location_out.open(end[1], std::ios::out | std::ios::app);
        location_out << 0 << " "
                     << "未交" << endl;
        location_out.close();

        end[2] = target + "\\zip.txt";
        location_out.open(end[2], std::ios::out | std::ios::app);
        location_out.close();

        end[3] = target + "\\unzip.txt";
        location_out.open(end[3], std::ios::out | std::ios::app);
        location_out.close();
    }
    cout << "请输入您要布置的作业的描述(字符请用空格分离）" << endl;

    string word0;
    set<string> words;

    hw_t a;
    a.len = 0;
    do {
        cin >> word0;
        words.insert(word0);
        a.len++;
        a.name += word0;
    } while (cin.get() != '\n');
    for (auto it = words.begin(); it != words.end(); it++) a.words.push_back(*it);
    t.homework_number++;
    t.hws.push_back(a);

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
        single_course_t a = t.course_table[i];
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
        material_t a = t.materials[i];
        ofs << a.weight << " " << a.name << " " << a.id << " " << a.len;
        for (int i = 0; i <= a.len - 1; i++) {
            ofs << " " << a.words[i];
        }
        ofs << endl;
    }
    ofs << t.homework_number << endl;
    for (int i = 0; i <= t.homework_number - 1; i++) {
        hw_t a = t.hws[i];
        ofs << a.name << " " << a.len;
        for (int i = 0; i <= a.len - 1; i++) {
            ofs << " " << a.words[i];
        }
        ofs << endl;
    }
    ofs << t.student_number << endl;
    for (int i = 0; i <= t.student_number - 1; i++) {
        string stu_id = t.stu_ids[i];
        ofs << stu_id << endl;
    }
    ofs.close();
    log("set_homework");
}

//批改作业
void Teacher::mark_homework() {
    string course_id;    //课程编号
    string course_name;  //课程名称
    int hw_times;
    cout << "请输入要批改作业的课程名称: ";
    cin >> course_name;
    //教师输入课程名称，然后从 course_colleciton.txt 中查到课程id 赋值给 course_id;
    // string hw_path = ......
    course_id = name_to_id[course_name];
    cout << "请输入要批改的作业次数: ";
    cin >> hw_times;
    //作业次数
    whole_course_t t;
    t.course_id = name_to_id[course_name];
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
        single_course_t a;
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
        // cout << book_name << endl;
    }
    // cout<<"fine"<<endl;
    ifs >> t.material_number;
    string word;
    for (int i = 1; i <= t.material_number; i++) {
        material_t a;
        ifs >> a.weight >> a.name >> a.id >> a.len;
        for (int i = 0; i <= a.len - 1; i++) {
            ifs >> word;
            a.words.push_back(word);
        }
        t.materials.push_back(a);
        // cout << a.name << endl;
    }
    ifs >> t.homework_number;
    for (int i = 1; i <= t.homework_number; i++) {
        hw_t a;
        ifs >> a.name >> a.len;
        for (int j = 0; j <= a.len - 1; j++) {
            ifs >> word;
            a.words.push_back(word);
        }
        t.hws.push_back(a);
    }
    // cout<<"ok"<<endl;
    ifs >> t.student_number;
    for (int i = 1; i <= t.student_number; i++) {
        string stu_id;
        ifs >> stu_id;
        t.stu_ids.push_back(stu_id);
    }
    ifs.close();
    vector<string> ids;
    // ifstream info;
    string grades, state;
    string varify, base = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/" + course_id + "_course/";
    for (auto id : t.stu_ids) {
        varify = base + to_string(hw_times) + "_times/" + id + "_stu/" + "info.txt";
        ifs.open(varify, ios::in);
        if (!ifs.is_open()) {
            cout << "作业文件不存在" << endl;
            ifs.close();
            return;
        }
        ifs >> grades >> state;
        if (state == "已交") ids.push_back(id);
        ifs.close();
    }
    this->decompress(course_name, to_string(hw_times), ids);  //先调用解压作业
    this->check_duplicate(course_id, hw_times, ids);          //输出查重结果
    ofstream ofs;
    for (auto id : ids) {
        cout << "请给出学生" + id + "的分数:" << endl;
        cin >> grades;
        varify = base + to_string(hw_times) + "_times/" + id + "_stu/" + "info.txt";
        ofs.open(varify, ios::out);
        if (!ofs.is_open()) {
            cout << "作业文件不存在" << endl;
            ofs.close();
            return;
        }
        ofs << grades << " "
            << "已交";
        ofs.close();
    }
    log("mark_homework");
}

//得到某次作业的查重结果
/*遍历每个学生，输出当前学生与其他所有学生的重复率
算法保证正确，极端情况全相等文本可得重复率100%，完全不同内容文本重复率为0% */
void Teacher::check_duplicate(string course_id, int times, vector<string> ids) {
    // cout << "\n查重函数 Debug Result: \n\n";
    string hw_folder = "../../src/model/identity_model/homework_set/" + this->teacher_id + "_teacher/" + course_id + "_course/" + to_string(times) + "_times/";
    //遍历每个学号
    for (auto stu_id : ids) {
        string hw_file = hw_folder + stu_id + "_stu/" + "hw.txt";  //当前学生作业
        ifstream ifs_hw;
        ifs_hw.open(hw_file, ios::in);
        if (!ifs_hw.is_open()) {
            cout << "\n打开学生 " << stu_id << " 作业文件失败!\n";
            system("pause");
            return;
        }

        string hw_content;  //作业中所有字符串拼接起来的结果
        string hw_lines;
        while (ifs_hw >> hw_lines) hw_content += hw_lines;
        //输出作业内容测试一下
        // cout << "当前学生 " << stu_id << " 作业: \n"
        //  << hw_content << "\n\n";
        // system("pause");

        // Aho–Corasick algorithm, AC自动机字符串匹配(Trie 图优化)
        //分割为长度为10的字符串，每匹配一条重复率加 (10/作业总长度) x 100%
        //查重一次作业时间复杂度O(T*C^2) T 为两个查重对象作业文本均摊长度,C 为学生人数

        /*
        other_hw_content 待匹配母串
        hw_content 待分割的子串
        */
        vector<string> split_string;
        set<string> filter1;
        int cnt = 0;
        string add_temp = "";
        for (int i = 0; hw_content[i]; i++) {
            if (cnt % 10 == 0) {
                split_string.push_back(add_temp);
                filter1.insert(add_temp);
                add_temp = "";
                cnt = 0;
            }
            add_temp += hw_content[i];
            cnt++;
        }
        if (add_temp.size() != 0) split_string.push_back(add_temp);

        // for (auto sp : split_string) cout << sp << endl;
        // system("pause");

        for (auto other_id : ids) {
            if (other_id != stu_id) {
                string other_hw_file = hw_folder + other_id + "_stu/" + "hw.txt";  //其他学生作业
                ifstream ifs_others;
                ifs_others.open(other_hw_file, ios::in);
                string other_hw_content;
                string other_hw_lines;
                while (ifs_others >> other_hw_lines) other_hw_content += other_hw_lines;

                /*other_hw_content 待匹配母串
                hw_content 待分割的子串
                split_string 分割后的子串
                split_pattern 分割后的母串*/

                vector<string> split_pattern;
                int cnt2 = 0;
                set<string> filter2;
                string add_temp2 = "";
                for (int i = 0; other_hw_content[i]; i++) {
                    if (cnt2 % 10 == 0) {
                        split_pattern.push_back(add_temp2);
                        filter2.insert(add_temp2);
                        add_temp2 = "";
                        cnt2 = 0;
                    }
                    add_temp2 += other_hw_content[i];
                    cnt2++;
                }
                if (add_temp2.size() != 0) split_pattern.push_back(add_temp2);

                // AC自动机实现
                const int N = 1000, S = 15;  //约定作业最长1000*15 字符
                // const int M = 10000;         //母串长度
                // int n;
                int tr[N * S][130];  // trie
                int cnt[N * S];      //每个节点结尾的10长度单词的数量
                // char str[M];
                string str;
                int q[N * S];  // bfs宽搜队列
                int ne[N * S];
                int idx = 0;  // trie idx
                char init = 0;

                // AC自动机插入字符串
                auto insert = [&](string str) {
                    int p = 0;  //根节点
                    for (int i = 0; str[i]; i++) {
                        int t = str[i] - init;
                        if (!tr[p][t]) tr[p][t] = ++idx;
                        p = tr[p][t];
                    }
                    cnt[p]++;
                };

                // bfs构建AC自动机
                auto build = [&]() {
                    int hh = 0, tt = -1;
                    for (int i = 0; i < 128; i++) {
                        //将根节点的子节点全部入队 就是第一层
                        if (tr[0][i]) q[++tt] = tr[0][i];
                    }
                    while (hh <= tt) {
                        int t = q[hh++];
                        for (int i = 0; i < 128; i++) {
                            int& c = tr[t][i];
                            // trie图优化：
                            //如果j的子节点c不存在 那么就让c直接指向最终的位置
                            //这里的ne[]此时是递归定义的，如果匹配下一个字母失败，就会直接跳到最终的位置
                            //不会在每一个fail指针处都判断是否存在该字母
                            if (!c)
                                tr[t][i] = tr[ne[t]][i];
                            else {
                                //如果子节点c存在 那就和朴素的写法一样 更新子节点的next
                                ne[c] = tr[ne[t]][i];
                                q[++tt] = c;
                            }
                        }
                    }
                };

                // main logic
                memset(tr, 0, sizeof tr);
                idx = 0;
                memset(cnt, 0, sizeof cnt);
                memset(ne, 0, sizeof ne);
                memset(q, 0, sizeof q);

                for (auto s : split_string) {
                    insert(s);
                }
                build();
                str = other_hw_content;  //待匹配长母串
                int res = 0;
                for (int i = 0, j = 0; str[i]; i++) {
                    int t = str[i] - init;
                    // trie图优化:
                    j = tr[j][t];  //不用再while循环了
                    int p = j;
                    while (p) {
                        res += cnt[p];
                        cnt[p] = 0;
                        p = ne[p];
                    }
                }
                // printf("%d\n", res);  //出现次数
                /*
                cout << res << endl;
                cout << split_string.size() << endl;
                cout << split_pattern.size() << endl;
                puts("---");
                cout << filter1.size() << endl;
                cout << filter2.size() << endl;
                */
                double dup_rate = 1.0 * res * 2 / (filter1.size() + filter2.size());
                cout << "\n学生 " << stu_id << " 与学生 " << other_id << " 本次作业作业重复率为 " << dup_rate * 100 << "%\n";
            }
        }
    }
    system("pause");
    system("cls");
}

void Teacher::log(string sth) {
    logger_t addition = logger_t("teacher", teacher_id, sth);
    ofstream ofs1;
    string log_file = "../../log/tea.txt";
    ofs1.open(log_file, ios::app);
    ofs1 << addition.now << " " << addition.kind << " " << addition.id << " " << addition.sth << endl;
    ofs1.close();
}
