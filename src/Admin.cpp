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
    cout << "����������Ҫ���ѧ����ѧ�ţ����䣬���������룺" << endl;
    user newUser;
    cin >> newUser.id >> newUser.email >> newUser.userName >> newUser.pass;
    users[userNum] = newUser;
    userNum += 1;
    if (save()) cout << "�޸ĳɹ�" << endl;
    else cout << "�޸�ʧ��" << endl;
    Sleep(4000);
}

void Admin::addCourse() {
    cout << "����������Ҫ��ӿγ̵Ŀγ̴��룬ѧ�֣��γ����ƣ��Ͽ�ʱ�䣬ʱ��Σ��γ�������" << endl;
    Course newCourse;
    cin >> newCourse.id >> newCourse.credit >> newCourse.name >> newCourse.time >> newCourse.period;
    courses[courseNum] = newCourse;
    courseNum += 1;
    if (save()) cout << "�޸ĳɹ�" << endl;
    else cout << "�޸�ʧ��" << endl;
    Sleep(4000);
}

void Admin::modStudent() {
    system("cls");
    cout << setiosflags(ios::left) << "��ѡ��Ҫ�޸���Ϣ��ѧ����" << endl;
    cout << setw(6) << "ѡ��" << setw(15) << "ѧ��" << setw(20) << "����"
        << setw(15) << "����" << endl;
    for (int i = 0; i < userNum; i++) {
        cout << setw(6) << i+1 << setw(15) << users[i].id << setw(20) <<  
            users[i].email << setw(15) <<  users[i].userName << endl;
    }
    cout << "0.�����ϲ�˵�" << endl;
    int opcode;
    cin >> opcode;
    for (int i = 0; i < userNum; i++) {
        if (opcode == i+1) {
            cout << "��ѡ��Ҫ�޸ĵ���Ϣ�� 1.ѧ�� 2.���� 3.���� 4.���� 0.ȡ��" << endl;
            int opcode2;
            while (cin >> opcode2) {
                if (opcode2 == 0) break;
                switch (opcode2) {
                case 1:
                    cout << "�������޸ĺ��ѧ�ţ�";
                    cin >> users[i].id;
                    break;
                case 2:
                    cout << "�������޸ĺ�����䣺";
                    cin >> users[i].email;
                    break;
                case 3:
                    cout << "�������޸ĺ��������";
                    cin >> users[i].userName;
                    break;
                case 4:
                    cout << "�������޸ĺ�����룺";
                    cin >> users[i].pass;
                    break;
                default:
                    cout << "����������������������" << endl;
                    break;
                }
                break;
            }
        }
    }
    if (save()) cout << "�޸ĳɹ�" << endl;
    else cout << "�޸�ʧ��" << endl;
    Sleep(4000);
}

void Admin::modCourse() {
    system("cls");
    cout << setiosflags(ios::left) << "��ѡ��Ҫ�޸���Ϣ�Ŀγ̣�" << endl;
    cout << setw(6) <<  "ѡ��" << setw(10) << "�γ̴���" << setw(6) << "ѧ��" 
        << setw(30) << "�γ�����" << setw(30) << "�Ͽ�ʱ��" << setw(12) 
        << "ʱ���" << setw(3) << "����" << endl;
    for (int i = 0; i < courseNum; i++) {
        cout << setw(6) <<  i+1 << setw(10) << courses[i].id << setw(6) << courses[i].credit 
            << setw(30) << courses[i].name << setw(30) << courses[i].time << setw(12) 
            << courses[i].period << setw(3) << courses[i].capacity << endl;
    }
    cout << "0.�����ϲ�˵�" << endl;
    int opcode;
    cin >> opcode;
    for (int i = 0; i < userNum; i++) {
        if (opcode == i+1) {
            cout << "��ѡ��Ҫ�޸ĵ���Ϣ�� 1.�γ̴��� 2.ѧ�� 3.�γ����� 4.�Ͽ�ʱ�� 5.ʱ��� 6.���� 0.ȡ��" << endl;
            int opcode2;
            while (cin >> opcode2) {
                if (opcode2 == 0) break;
                switch (opcode2) {
                case 1:
                    cout << "�������޸ĺ�Ŀγ̴��룺";
                    cin >> courses[i].id;
                    break;
                case 2:
                    cout << "�������޸ĺ��ѧ�֣�";
                    cin >> courses[i].credit;
                    break;
                case 3:
                    cout << "�������޸ĺ�Ŀγ����ƣ�";
                    cin >> courses[i].name;
                    break;
                case 4:
                    cout << "�������޸ĺ���Ͽ�ʱ�䣺";
                    cin >> courses[i].time;
                    break;
                case 5:
                    cout << "�������޸ĺ��ʱ��Σ�";
                    cin >> courses[i].period;
                    break;
                case 6:
                    cout << "�������޸ĺ��������";
                    cin >> courses[i].capacity;
                    break;
                default:
                    cout << "����������������������" << endl;
                    break;
                }
                break;
            }
        }
    }
    if (save()) cout << "�޸ĳɹ�" << endl;
    else cout << "�޸�ʧ��" << endl;
    Sleep(4000);
}

void Admin::showStatus() {
    string id;
    cout << "������Ҫ��ѯѧ����ѧ��" << endl;
    cin >> id;
    string fileUrl = "data/selectList/" + id + ".txt";
    char fileUrlchar[50];
    strcpy(fileUrlchar, fileUrl.c_str());
    ifstream infile;
    infile.open(fileUrl, ios::in);
    if (!infile) {
        cout << "��ѯʧ�ܣ�û������ѧ��" << endl;
    } else {
        cout << setiosflags(ios::left) << "��ѡ�޵Ŀγ����£�" << endl;
        cout << setw(6) <<  "ѡ��" << setw(10) << "�γ̴���" << setw(6) << "ѧ��" 
            << setw(30) << "�γ�����" << setw(30) << "�Ͽ�ʱ��" << setw(3) << "����" << endl;
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
        cout << "��ӭ��������Ա��" << endl;;
        cout << "��ѡ�� 1.����ѧ�� 2.���ӿγ� 3.�޸�ѧ����Ϣ 4.�޸Ŀγ���Ϣ 5.�鿴ѧ��ѡ�� 0.�˳�" << endl;
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
            cout << "����������������������" << endl;
            break;
        }
    }
    cout << "�˳�ϵͳ�ɹ�" << endl;
    system("pause");
}