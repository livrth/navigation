#include "course.h"

#include <direct.h>

#include <fstream>
Course::Course(string course_id, string course_name, string id) {
    this->course_id = course_id;
    this->course_name = course_name;
    this->user_id = id;
}

//以下是压缩算法
void Course::compress(string str) {
    cout << "compress启动成功" << endl;
    buildText(str.c_str());
    int pos = str.find_last_of('.');
    string str1 = str.substr(0, pos);
    str = str1 + "_zip.txt";
    writeZip(str.c_str());
}

void Course::buildText(const char* pathname) {
    map<char, int> cnt;
    priority_queue<zipnode*, vector<zipnode*>, cmp> Q;
    zip_text.find(pathname);
    ifstream in;
    char buf[1024];
    in.open(pathname, ios::binary);

    while (true) {
        memset(buf, 0, sizeof(buf));
        in.read(buf, 1024);
        for (int i = 0; i < in.gcount(); ++i) {
            cnt[buf[i]]++;
        }
        if (in.gcount() < 1024)
            break;
    }

    nch = cnt.size();
    in.close();
    for (auto x : cnt) {
        zipnode* p = new zipnode(x.second);
        p->ch = x.first;
        Q.push(p);
    }
    while (Q.size() >= 2) {
        zipnode* lc = Q.top();
        Q.pop();
        zipnode* rc = Q.top();
        Q.pop();
        rt = new zipnode(lc->val + rc->val, lc, rc);
        Q.push(rt);
    }
    dfs(rt, "");
    for (auto x : zip_code) {
        if (isprint(x.first)) cout << x.first;
        cout << "/" << (int)x.first << " : " << x.second << endl;
    }
    in.open(pathname, ios::binary);

    while (true) {
        memset(buf, 0, sizeof(buf));
        in.read(buf, 1024);
        for (int i = 0; i < in.gcount(); ++i) {
            zip_text += zip_code[buf[i]];
        }
        if (in.gcount() < 1024)
            break;
    }
    in.close();
}

void Course::dfs(zipnode* p, string s) {
    if (p->l == nullptr && p->r == nullptr) {
        zip_code[p->ch] = s;
        return;
    }
    if (p->l != nullptr) dfs(p->l, s + '0');
    if (p->r != nullptr) dfs(p->r, s + '1');
}

void Course::writeZip(const char* pathname) {
    ofstream out;
    out.open(pathname, ios::binary);
    zip_lenstr = zip_text.length();
    out.put((unsigned char)nch);
    unsigned int len_tmp = zip_lenstr;
    for (int i = 3; i >= 0; --i) {
        out.put((unsigned char)(len_tmp >> (8 * i)) % (1 << 8));
    }
    vector<string> tmp_zip_codelist;
    for (auto x : zip_code) {
        out.put(x.first);
        out.put((unsigned char)x.second.length());
        int remain_size = 8;
        if (!tmp_zip_codelist.empty())
            remain_size = 8 - (tmp_zip_codelist[tmp_zip_codelist.size() - 1].length());
        string pre = x.second.substr(0, remain_size), nxt, _nxt;
        if (remain_size < (int)x.second.length()) nxt = x.second.substr(remain_size);
        if (nxt.length() > 8) {
            _nxt = nxt.substr(8);
            nxt = nxt.substr(0, 8);
        }
        if (tmp_zip_codelist.empty()) {
            tmp_zip_codelist.push_back(pre);
            if (!nxt.empty()) tmp_zip_codelist.push_back(nxt);
            continue;
        }
        tmp_zip_codelist[tmp_zip_codelist.size() - 1] += pre;
        if (!nxt.empty()) tmp_zip_codelist.push_back(nxt);
        if (!_nxt.empty()) tmp_zip_codelist.push_back(_nxt);
    }
    for (string x : tmp_zip_codelist)
        out.put(strToChar(x));
    string now;
    for (char x : zip_text) {
        now += x;
        if (now.length() == 8) {
            out.put(strToChar(now));
            now.clear();
        }
    }
    if (!now.empty())
        out.put(strToChar(now));
    out.close();
}

unsigned char Course::strToChar(string s) {
    while (s.length() < 8) s += '0';
    unsigned char res = 0;
    for (char x : s) {
        res <<= 1;
        res |= x - '0';
    }
    return res;
}

//压缩算法结束
//下面是解压缩算法

//解压缩算法
void Course::loadZip(const char* pathname) {
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
    buildCodeTable(sum_code);
    delete[] buf;
    unzip_text.clear();
    len_bit = unzip_lenstr / 8 + (unzip_lenstr % 8 != 0);
    buf = new char[len_bit];
    in.read(buf, len_bit);
    for (int i = 0; i < len_bit; ++i) unzip_text += charToStr(buf[i]);
    delete[] buf;
    in.close();
}

void Course::unzip(const char* pathname) {
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

void Course::buildCodeTable(int n) {
    int now = 1;
    for (int i = 0; i < n; ++i) {
        char now_char = unzip_chlen[now].first;
        unzip_code[now_char] += unzip_text[i];
        if ((int)unzip_code[now_char].length() == unzip_chlen[now].second) {
            unzip_decode[unzip_code[now_char]] = now_char;
            now++;
        }
    }
}

string Course::charToStr(char x) {
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

void Course::decompress() {
    string str;
    cin >> str;
    loadZip(str.c_str());
    int pos = str.find_last_of('.');
    string str1 = str.substr(0, pos);
    str1 += "_unzip.txt";
    unzip(str1.c_str());
}
//解压缩

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
        ifs >> a.date >> a.seq >> a.place >> name >> a.campus >> course_id >> a.building_id;
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
    string seq;
    for (int i = 0; i <= stu_number - 1; i++) {
        ifs >> seq;
        stus.push_back(seq);
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
    int str;
    cout << "请输入要提交的作业的次数:" << endl;
    cin >> str;
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
    folderPath = path + "\\src\\model\\identity_model\\homework_set\\" + teacher_id + "_teacher\\" + course_id + "_course\\" + to_string(str) + "_times";
    target = folderPath + "\\" + user_id + "_stu" + "\\hw.txt";
    compress(target);
    target = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/" + course_id + "_course/" + to_string(str) + "_times/" + user_id + "_stu/" + "info.txt";
    ofstream location_out;
    location_out.open(target, std::ios::out);
    location_out << 0 << " "
                 << "已交" << endl;
    location_out.close();
    hws[str].state = "已交";
    cout << "已提交" << endl;
    system("pause");
}
void Course::submit_material() {
    string str, word;
    cout << "请输入要提交的资料的文件地址：" << endl;
    cin >> str;
    material addition;
    addition.len = 0;
    cout << "请输入资料的名字(任意字符请用空格分离）:" << endl;
    do {
        cin >> word;
        if (addition.words.find(word) == addition.words.end()) addition.len++;
        addition.words.insert(word);

        addition.name += word;
    } while (cin.get() != '\n');

    //资料去重
    for (auto key : materials) {
        if (key.name == addition.name) {
            cout << "资料已经存在！不能上传该资料!" << endl;
            return;
        }
    }

    cout << "资料允许上传，请输入资料重要度：" << endl;
    cin >> addition.weight;
    addition.id = "0008";
    materials.push_back(addition);
    order_materials.push_back(material_number);
    material_number++;
    compress(str);
    ofstream ofs;
    string course_filename = "../../src/model/course_model/course_set/" + course_id + "_course.txt";
    ofs.open(course_filename, ios::out);
    if (!ofs.is_open()) {
        cout << "课程文件不存在" << endl;
        ofs.close();
        return;
    }
    ofs << course_name << endl
        << times_per_week << endl;
    for (int i = 0; i <= times_per_week - 1; i++) {
        single_course a = course_table[i];
        ofs << a.date << " " << a.seq << " " << a.place << " " << course_name << " " << a.campus << " " << course_id << " " << a.building_id << endl;
    }
    ofs << teacher_name << " " << teacher_id << endl
        << course_qun << endl
        << total_weeks << endl;
    ofs << final.week << " " << final.date << " " << final.st_hour << " " << final.st_min << " " << final.fi_hour << " " << final.fi_min << " " << final.campus << " " << final.place << " " << endl;
    ofs << ref_book_number << endl;
    for (int i = 0; i <= ref_book_number - 1; i++) {
        string book_name = ref_books[i];
        ofs << book_name << " " << endl;
    }
    ofs << material_number << endl;
    for (int i = 0; i <= material_number - 1; i++) {
        material a = materials[i];
        ofs << a.weight << " " << a.name << " " << a.id << " " << a.len;
        for (auto word : a.words) {
            ofs << " " << word;
        }
        ofs << endl;
    }
    ofs << homework_number << endl;
    for (int i = 1; i <= homework_number; i++) {
        hw a = hws[i];
        ofs << a.name << " " << a.len;
        for (auto word : a.words) {
            ofs << " " << word;
        }
        ofs << endl;
    }
    ofs << stu_number << endl;
    for (int i = 0; i <= stu_number - 1; i++) {
        ofs << stus[i] << endl;
    }
    ofs.close();
    cout << "已提交" << endl;
    system("pause");
}

void Course::download_material() {
    cout << "请输入要下载的材料的文件地址：" << endl;
    decompress();
    cout << "下载成功" << endl;
    system("pause");
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
