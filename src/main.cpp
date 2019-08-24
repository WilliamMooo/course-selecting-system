#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <windows.h>
#include <cstring>
#include <string>
#include <regex>

#include "Email.h"
#include "CourseSystem.h"

using namespace std;

int getUserList(user *list);
void login(user users[], int n);
bool emailIsExist(user users[], string email, int n);
int passIsMatched(user users[], string pass, int n);
bool matchEmailAddr(string emailAddr);
int retrieve(string email);
void resetPsw(user users[], string email, int n);

int getWordList(string *list);
int save(user users[], int n);

int main() {
    //��ʼ��
    user users[100];
    int usersNum = getUserList(users);
    int opcode;
    while(1) {
        system("cls");
        cout << "��ӭʹ��ѡ��ϵͳ" << endl;
        cout << "��ѡ��1.��½ 0.�˳�ϵͳ" << endl;
        cin >> opcode;
        if (opcode == 0) break;
        switch (opcode) {
        case 1:
            login(users, usersNum);
            break;
        default:
            cout << "����������������������" << endl;
            Sleep(2000);
            break;
        }
    }
    cout << "�˳�ϵͳ�ɹ�" << endl;
    system("pause");
    return 0;
}

void login(user users[], int n) {
    string email;
    string userName;
    string pass;
    cout << "�������˺����䣺";
    while (cin >> email) {
        if (matchEmailAddr(email)) break;
        else cout << "���������ʽ����ȷ����������" << endl << "�������˺����䣺";
    }
    bool isExist = emailIsExist(users, email, n);
    if (isExist) {
        cout << "���������룺";
        cin >> pass;
        int isMatch = passIsMatched(users, pass, n);
        if (isMatch != -1) {
            cout << "��½�ɹ�" << endl;
            Sleep(1000);
            system("cls");
            cout << "���ڽ���ϵͳ...";
            Sleep(4000);
            //����ϵͳ
            CourseSystem sys(users[isMatch]);
            sys.run();
            users[isMatch] = sys.update();
        } else {
            cout << "�������������ѡ��1.�������� 2.�һ����� 3.�˳�)";
            int opcode2;
            while(cin >> opcode2) {
                if(opcode2 == 3) break;
                switch (opcode2) {
                    case 1:
                        cout << "���������룺";
                        cin >> pass;
                        isMatch = passIsMatched(users, pass, n);
                        if (isMatch != -1) {
                            cout << "��½�ɹ�" << endl;
                            Sleep(1000);
                            //����ϵͳ
                            CourseSystem sys(users[isMatch]);
                            users[isMatch] = sys.update();
                            sys.run();
                        } else {
                            cout << "�������������ѡ��1.�������� 2.�һ����� 3.�˳�)";
                        }
                        break;
                    case 2:
                        resetPsw(users, email, n);
                        break;
                    default:
                        cout << "����������������������" << endl;
                        break;
                }
            }
        }
    } else {
        cout << "���˺����䲻���ڣ�����ϵ����Ա" << endl;
        Sleep(4000);
    }
}

int getWordList(string *list) {
    ifstream infile;
    infile.open("data/chinese_dictionary.txt", ios::in);
    if (!infile) {
        cerr << "���ļ�ʧ��" << endl;
        Sleep(4000);
        return 0;
    }
    int n = 0;
    while (!infile.eof()) {
        string temp;
        infile >> temp;
        if (infile) {
            list[n] = temp;
            n++;
        } else {
            break;
        }
    }
    infile.close();
    return n;
}

int getUserList(user *list) {
    ifstream infile;
    infile.open("data/users.txt", ios::in);
    if (!infile) {
        cout << "open file fail" << endl;
        Sleep(4000);
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

int save(user users[], int n) {
    ofstream outFile;
    outFile.open("data/users.txt", ios::out);
    if (!outFile) {
        cout << "�����ļ�ʧ�ܣ�" << endl;
        Sleep(4000);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        outFile << users[i].id << " " << users[i].email << " " <<
            users[i].userName << " " << users[i].pass << endl;
    }
    outFile.close();
    return 0;
}

bool emailIsExist(user users[], string email, int n) {
    for (int i = 0; i < n; i++) {
        if (email == users[i].email) {
            return true;
        }
    }
    return false;
}

int passIsMatched(user users[], string pass, int n) {
    for (int i = 0; i < n; i++) {
        if (pass == users[i].pass) {
            return i;
        }
    }
    return -1;
}

int retrieve(string email) {
    char emailAddr[100];
    strcpy(emailAddr, email.c_str());
    Email em(emailAddr);
    int code = em.getDppsw();
    em.setDppsw(code);
    em.sendTo();
    return code;
}

bool matchEmailAddr(string emailAddr) {
    regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
    if (regex_match(emailAddr, pattern)) {
        return true;
    } else {
        return false;
    }
}

void resetPsw(user users[], string email, int n) {
    cout << "�����������յ��Ķ�̬��֤�룺" << endl;
    int code = retrieve(email);
    int inputCode;
    while (cin >> inputCode) {
        bool flag = true;
        if (code == inputCode) {
            //��������
            while (flag) {
                string newPass, confirm;
                cout << "�����������룺" << endl;
                cin >> newPass;
                cout << "�Ƿ�ȷ���޸ģ���Y/N��" << endl;
                cin >> confirm;
                if (confirm == "y" || confirm == "Y") {
                    flag = false;
                    for (int i = 0; i < n; i++) {
                        if (users[i].email == email) users[i].pass = newPass;
                    }
                }
                save(users, n);
                cout << "�޸ĳɹ�" << endl;
                Sleep(1000);
                if (!flag) break;
            }
        } else {
            cout << "��֤�����" << endl;
        }
        if (!flag) break;
    }
}