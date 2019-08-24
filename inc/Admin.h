#include <string>

using namespace std;

class Admin {
private:
    struct user {
        string id;
        string email;
        string userName;
        string pass;
    };
    struct Course {
        string id;
        float credit;
        string name;
        string time;
        int period;
        int capacity;
    };
    user users[1000];
    Course courses[30];
    int userNum;
    int courseNum;
public:
    void run();
    int getUserList(user *list);
    int getCourseList(Course *list);
    bool save();
    void addStudent(); 
    void addCourse();
    void modStudent();
    void modCourse();
    void showStatus();
};