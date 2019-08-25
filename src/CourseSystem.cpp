#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>

#include "CourseSystem.h"

using namespace std;

CourseSystem::CourseSystem(user user) {
    nowUser = user;
    courseNum = getCourseList(courses);
    selectedNum = getSelectedList();
}   

user CourseSystem::update() {
    return nowUser;
}

int CourseSystem::getSelectedList() {
    string fileUrl = "data/selectList/" + nowUser.id + ".txt";
    char fileUrlchar[50];
    strcpy(fileUrlchar, fileUrl.c_str());
    ifstream infile;
    infile.open(fileUrl, ios::in);
    if (!infile) {
        ofstream file(fileUrl, fstream::out);
        return 0;
    }
    int n = 0;
    while (!infile.eof()) {
        string newCourse;
        infile >> newCourse;
        if (infile) {
            selectedList[n] = newCourse;
            n++;
        } else {
            break;
        }
    }
    infile.close();
    return n;
}

int CourseSystem::getCourseList(Course *list) {
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

bool CourseSystem::save() {
    string fileUrl = "data/selectList/" + nowUser.id + ".txt";
    char fileUrlchar[50];
    strcpy(fileUrlchar, fileUrl.c_str());
    ofstream outFile;
    outFile.open(fileUrl, ios::out);
    if (!outFile) {
        cout << "open file fail" << endl;
        return false;
    }
    for (int i = 0; i < selectedNum; i++) {
        outFile << selectedList[i] << " ";
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

bool CourseSystem::isSelected(string id) {
    for (int i = 0; i < selectedNum; i++) {
        if (id == selectedList[i]) return true;
    }
    return false;
}

void CourseSystem::selectCourse() {
    system("cls");
    cout << setiosflags(ios::left) << "��ѡ��Ҫѡ�޵Ŀγ̣���ÿ�����3�ţ�" << endl;
    cout << setw(6) <<  "ѡ��" << setw(10) << "�γ̴���" << setw(6) << "ѧ��" 
        << setw(30) << "�γ�����" << setw(30) << "�Ͽ�ʱ��" << setw(3) << "����" << endl;
    for (int i = 0; i < courseNum; i++) {
        cout << setw(6) << i+1 << setw(10) << courses[i].id << setw(6) <<
            courses[i].credit << setw(30) << courses[i].name <<
            setw(30) << courses[i].time << setw(3) << courses[i].capacity << endl;
    }
    cout << "0.�����ϲ�˵�" << endl;
    int opcode4;
    while (cin >> opcode4) {
        if (opcode4 == 0) break;
        if (opcode4 < 0 || opcode4 > courseNum) {
            cout << "����������������������" << endl;
        } else {
            bool flag = false;
            int temp[3];
            for (int i = 0; i < courseNum; i++) {
                for (int j = 0; j < selectedNum; j++) {
                    if (courses[i].id == selectedList[j]) temp[j] = i;
                }
            }
            for (int i = 0; i < selectedNum; i++) {
                if (courses[opcode4-1].period == courses[temp[i]].period) flag = true;
            }
            if (courses[opcode4-1].capacity == 0) {
                cout << "�γ���������������������" << endl;
            } else if (selectedNum == 3) {
                cout << "ѡ��������������" << endl;
            } else if (isSelected(courses[opcode4-1].id)) {
                cout << "����ѡ�����ſγ�" << endl;
            }else if (flag) {
                cout << "�Ͽ�ʱ���ͻ" << endl;
            } else {
                courses[opcode4-1].capacity -= 1;
                selectedList[selectedNum] = courses[opcode4-1].id;
                selectedNum += 1;
                if(save()) cout << "ѡ�γɹ�" << endl;
                else cout << "ѡ��ʧ�ܣ�����ϵ����Ա" << endl;
            }
        }
    }
}

void CourseSystem::remove() {
    system("cls");
    if (selectedNum) {
        cout << setiosflags(ios::left) << "��ѡ�޵Ŀγ����£�" << endl;
        cout << setw(6) <<  "ѡ��" << setw(10) << "�γ̴���" << setw(6) << "ѧ��" 
            << setw(30) << "�γ�����" << setw(30) << "�Ͽ�ʱ��" << setw(3) << "����" << endl;
        int temp[3];
        for (int i = 0; i < selectedNum; i++) {
            for (int j = 0; j < courseNum; j++) {
                if (selectedList[i] == courses[j].id) {
                    temp[i] = j;
                    cout << setw(6) << i+1 << setw(10) << courses[j].id << setw(6) <<
                        courses[j].credit << setw(30) << courses[j].name <<
                        setw(30) << courses[j].time << setw(3) << courses[j].capacity << endl;
                }
            }
        }
        cout << "������������ѡ�Ŀγ�(����0�����ϲ�˵�)��";
        int opcode5;
        cin >> opcode5;
        for (int i = 0; i < selectedNum; i++) {
            if (opcode5 == i+1) {
                courses[temp[i]].capacity += 1;
                selectedNum -= 1;
                if (selectedNum) {
                    for (int j = i; j < selectedNum; j++) {
                        selectedList[j] = selectedList[j+1];
                    }
                }
                if(save()) cout << "�˿γɹ�" << endl;
                else cout << "ѡ��ʧ�ܣ�����ϵ����Ա" << endl;
            }
        }
    } else {
        cout << "��δѡ���κογ�" << endl;
        system("pause");
    }
}

void CourseSystem::run() {
    int opcode3;
    while (1) {
        system("cls");
        cout << "��ӭ����" << nowUser.userName << endl;;
        cout << "��ѡ�� 1.ѡ�� 2.�鿴/��ѡ�γ� 0.�˳�" << endl;
        cin >> opcode3;
        switch (opcode3) {
        case 1:
            selectCourse();
            break;
        case 2:
            remove();
            break;
        case 0:
            break;
        default:
            cout << "����������������������" << endl;
            break;
        }
        if (opcode3 == 0) break;
    }
    cout << "�˳�ϵͳ�ɹ�" << endl;
    system("pause");
}