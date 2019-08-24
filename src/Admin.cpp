#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <Windows.h>

#include "Admin.h"

using namespace std;

int Admin::getUserList(user *list) {
    ifstream infile;
    infile.open("data/users.txt", ios::in);
    if (!infile) {
        cout << "open file fail" << endl;
        return 0;
    }
    int n = 0;
    while (!infile.eof()) {
        user newUser;
        infile >> newUser.id >> newUser.email >> newUser.userName >> newUser.pass;
        if (infile) {
            list[n] = newUser;
            n++;
        } else {
            break;
        }
    }
    infile.close();
    return n;
}

int Admin::getCourseList(Course *list) {
    ifstream infile;
    infile.open("data/courses.txt", ios::in);
    if (!infile) {
        cout << "open file fail" << endl;
        return 0;
    }
    int n = 0;
    while (!infile.eof()) {
        Course newCourse;
        infile >> newCourse.id >> newCourse.credit >> newCourse.name >> 
            newCourse.time >> newCourse.period >> newCourse.capacity;
        if (infile) {
            list[n] = newCourse;
            n++;
        } else {
            break;
        }
    }
    infile.close();
    return n;
}

bool Admin::save() {
    ofstream outFile;
    outFile.open("data/users.txt", ios::out);
    if (!outFile) {
        cout << "open file fail" << endl;
        return false;
    }
    for (int i = 0; i < userNum; i++) {
        outFile << users[i].id << " " << users[i].email << " " 
            << users[i].userName << " " << users[i].pass << endl;
    }
    outFile.close();
    outFile.open("data/courses.txt", ios::out);
    if (!outFile) {
        cout << "open file fail" << endl;
        return false;
    }
    for (int i = 0; i < courseNum; i++) {
        outFile << courses[i].id << " " << courses[i].credit << " "
            << courses[i].name << " " << courses[i].time << " " << 
            courses[i].period << " " << courses[i].capacity << endl;
    }
    return true;
}

void Admin::addStudent() {
    cout << "请依次输入要添加学生的学号，邮箱，姓名，密码：" << endl;
    user newUser;
    cin >> newUser.id >> newUser.email >> newUser.userName >> newUser.pass;
    users[userNum] = newUser;
    userNum += 1;
    if (save()) cout << "修改成功" << endl;
    else cout << "修改失败" << endl;
    Sleep(4000);
}

void Admin::addCourse() {
    cout << "请依次输入要添加课程的课程代码，学分，课程名称，上课时间，时间段，课程容量：" << endl;
    Course newCourse;
    cin >> newCourse.id >> newCourse.credit >> newCourse.name >> newCourse.time >> newCourse.period;
    courses[courseNum] = newCourse;
    courseNum += 1;
    if (save()) cout << "修改成功" << endl;
    else cout << "修改失败" << endl;
    Sleep(4000);
}

void Admin::modStudent() {
    system("cls");
    cout << setiosflags(ios::left) << "请选择要修改信息的学生：" << endl;
    cout << setw(6) << "选择" << setw(15) << "学号" << setw(20) << "邮箱"
        << setw(15) << "姓名" << endl;
    for (int i = 0; i < userNum; i++) {
        cout << setw(6) << i+1 << setw(15) << users[i].id << setw(20) <<  
            users[i].email << setw(15) <<  users[i].userName << endl;
    }
    cout << "0.返回上层菜单" << endl;
    int opcode;
    cin >> opcode;
    for (int i = 0; i < userNum; i++) {
        if (opcode == i+1) {
            cout << "请选择要修改的信息： 1.学号 2.邮箱 3.姓名 4.密码 0.取消" << endl;
            int opcode2;
            while (cin >> opcode2) {
                if (opcode2 == 0) break;
                switch (opcode2) {
                case 1:
                    cout << "请输入修改后的学号：";
                    cin >> users[i].id;
                    break;
                case 2:
                    cout << "请输入修改后的邮箱：";
                    cin >> users[i].email;
                    break;
                case 3:
                    cout << "请输入修改后的姓名：";
                    cin >> users[i].userName;
                    break;
                case 4:
                    cout << "请输入修改后的密码：";
                    cin >> users[i].pass;
                    break;
                default:
                    cout << "输入操作码错误，请重新输入" << endl;
                    break;
                }
                break;
            }
        }
    }
    if (save()) cout << "修改成功" << endl;
    else cout << "修改失败" << endl;
    Sleep(4000);
}

void Admin::modCourse() {
    system("cls");
    cout << setiosflags(ios::left) << "请选择要修改信息的课程：" << endl;
    cout << setw(6) <<  "选择" << setw(10) << "课程代码" << setw(6) << "学分" 
        << setw(30) << "课程名称" << setw(30) << "上课时间" << setw(12) 
        << "时间段" << setw(3) << "余量" << endl;
    for (int i = 0; i < courseNum; i++) {
        cout << setw(6) <<  i+1 << setw(10) << courses[i].id << setw(6) << courses[i].credit 
            << setw(30) << courses[i].name << setw(30) << courses[i].time << setw(12) 
            << courses[i].period << setw(3) << courses[i].capacity << endl;
    }
    cout << "0.返回上层菜单" << endl;
    int opcode;
    cin >> opcode;
    for (int i = 0; i < userNum; i++) {
        if (opcode == i+1) {
            cout << "请选择要修改的信息： 1.课程代码 2.学分 3.课程名称 4.上课时间 5.时间段 6.余量 0.取消" << endl;
            int opcode2;
            while (cin >> opcode2) {
                if (opcode2 == 0) break;
                switch (opcode2) {
                case 1:
                    cout << "请输入修改后的课程代码：";
                    cin >> courses[i].id;
                    break;
                case 2:
                    cout << "请输入修改后的学分：";
                    cin >> courses[i].credit;
                    break;
                case 3:
                    cout << "请输入修改后的课程名称：";
                    cin >> courses[i].name;
                    break;
                case 4:
                    cout << "请输入修改后的上课时间：";
                    cin >> courses[i].time;
                    break;
                case 5:
                    cout << "请输入修改后的时间段：";
                    cin >> courses[i].period;
                    break;
                case 6:
                    cout << "请输入修改后的余量：";
                    cin >> courses[i].capacity;
                    break;
                default:
                    cout << "输入操作码错误，请重新输入" << endl;
                    break;
                }
                break;
            }
        }
    }
    if (save()) cout << "修改成功" << endl;
    else cout << "修改失败" << endl;
    Sleep(4000);
}

void Admin::showStatus() {
    string id;
    cout << "请输入要查询学生的学号" << endl;
    cin >> id;
    string fileUrl = "data/selectList/" + id + ".txt";
    char fileUrlchar[50];
    strcpy(fileUrlchar, fileUrl.c_str());
    ifstream infile;
    infile.open(fileUrl, ios::in);
    if (!infile) {
        cout << "查询失败，没有这名学生" << endl;
    } else {
        cout << setiosflags(ios::left) << "你选修的课程如下：" << endl;
        cout << setw(6) <<  "选择" << setw(10) << "课程代码" << setw(6) << "学分" 
            << setw(30) << "课程名称" << setw(30) << "上课时间" << setw(3) << "余量" << endl;
        int n = 0;
        string selectList[3];
        while (!infile.eof()) {
            string temp;
            infile >> temp;
            if (infile) {
                selectList[n] = temp;
                n++;
            } else {
                break;
            }
        }
        infile.close();
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < courseNum; j++) {
                if (selectList[i] == courses[j].id) {
                    cout << setw(6) << i+1 << setw(10) << courses[j].id << setw(6) <<
                        courses[j].credit << setw(30) << courses[j].name <<
                        setw(30) << courses[j].time << setw(3) << courses[j].capacity << endl;
                }
            }
        }
    }
    system("pause");
}

void Admin::run() {
    userNum = getUserList(users);
    courseNum = getCourseList(courses);
    int opcode6 = -1;
    while (1) {
        if (opcode6 == 0) break;
        system("cls");
        cout << "欢迎您，管理员！" << endl;;
        cout << "请选择： 1.增加学生 2.增加课程 3.修改学生信息 4.修改课程信息 5.查看学生选课 0.退出" << endl;
        cin >> opcode6;
        switch (opcode6) {
        case 1:
            addStudent();
            break;
        case 2:
            addCourse();
            break;
        case 3:
            modStudent();
            break;
        case 4:
            modCourse();
            break;
        case 5:
            showStatus();
            break;
        default:
            cout << "输入操作码错误，请重新输入" << endl;
            break;
        }
    }
    cout << "退出系统成功" << endl;
    system("pause");
}