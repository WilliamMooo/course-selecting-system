#include <iostream>
#include <fstream>
#include <winsock2.h>
#include <windows.h>
#include <cstring>
#include <string>
#include <regex>

#include "Email.h"
#include "CourseSystem.h"
#include "Admin.h"

using namespace std;

int getUserList(user *list);
void login(user users[], int n);
bool emailIsExist(user users[], string email, int n);
bool passIsMatched(user users[], string email, string pass, int n);
bool matchEmailAddr(string emailAddr);
int retrieve(string email);
void resetPsw(user users[], string email, int n);
int getWordList(string *list);
int findUser(user users[], string pass, int n);
int save(user users[], int n);

int main() {
    //��ʼ��
    user users[1000];
    int usersNum = getUserList(users);
    int opcode;
    while(1) {
        system("cls");
        cout << "��ӭʹ��ѡ��ϵͳ" << endl;
        cout << "��ѡ��1.��¼ 0.�˳�ϵͳ" << endl;
        cin >> opcode;
        if (opcode == 0) break;
        switch (opcode) {
        case 1:
            login(users, usersNum);
            break;
        default:
            cout << "����������������������" << endl;
            system("pause");
            break;
        }
    }
    cout << "�˳�ϵͳ�ɹ�" << endl;
    system("pause");
    return 0;
}

void login(user users[], int n) {
    bool isAdmin = false;
    string admin = "q961017025@163.com";
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
        if (email == admin) isAdmin = true;
        cout << "���������룺";
        cin >> pass;
        bool isMatch = passIsMatched(users, email, pass, n);
        if (isMatch) {
            int index = findUser(users, pass, n);
            cout << "��½�ɹ�" << endl;
            system("pause");
            system("cls");
            cout << "���ڽ���ϵͳ...";
            Sleep(2000);
            //����ϵͳ
            if (isAdmin) {
                Admin ad;
                ad.run();
            } else {
                CourseSystem sys(users[index]);
                sys.run();
            }
        } else {
            cout << "�������������ѡ��1.�������� 2.�һ����� 3.�˳�";
            int opcode2;
            while(cin >> opcode2) {
                if(opcode2 == 3) break;
                bool fl = false;
                switch (opcode2) {
                    case 1:
                        cout << "���������룺";
                        cin >> pass;
                        isMatch = passIsMatched(users, email, pass, n);
                        if (isMatch) {
                            int index = findUser(users, pass, n);
                            system("pause");
                            fl = true;
                            cout << "��½�ɹ�" << endl;
                            system("pause");
                            //����ϵͳ
                            if (isAdmin) {
                                Admin ad;
                                ad.run();
                            } else {
                                CourseSystem sys(users[index]);
                                sys.run();
                            }
                        } else {
                            cout << "�������������ѡ��1.�������� 2.�һ����� 3.�˳�";
                        }
                        break;
                    case 2:
                        fl = true;
                        resetPsw(users, email, n);
                        break;
                    default:
                        cout << "����������������������" << endl;
                        break;
                }
                if (fl) break;
            }
        }
    } else {
        cout << "���˺����䲻���ڣ�����ϵ����Ա" << endl;
        system("pause");
    }
}

int getWordList(string *list) {
    ifstream infile;
    infile.open("data/chinese_dictionary.txt", ios::in);
    if (!infile) {
        cerr << "���ļ�ʧ��" << endl;
        system("pause");
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
        system("pause");
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
        system("pause");
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

bool passIsMatched(user users[], string email, string pass, int n) {
    bool ret = false;
    for (int i = 0; i < n; i ++) {
        if (email == users[i].email) {
            if (pass == users[i].pass) ret = true;
        }
    }
    return ret;
}

int findUser(user users[], string pass, int n) {
    for (int i = 0; i < n; i ++) {
        if (users[i].pass == pass) {
            return i;
        }
    }
    return 0;
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
    cout << "�����������յ��Ķ�̬��֤�룺(����0�˳�)" << endl;
    int code = retrieve(email);
    int inputCode;
    while (cin >> inputCode) {
        bool flag = true;
        if (inputCode == 0) break;
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
                system("pause");
                if (!flag) break;
            }
        } else {
            cout << "��֤�����" << endl;
        }
        if (!flag) break;
    }
}