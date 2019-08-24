#include "user.h"
#include "Course.h"

class CourseSystem {
private:
    user nowUser;
    string selectedList[3];//每个人最多选择3门选修课
    int selectedNum;
    Course courses[30];
    int courseNum;
public:
    CourseSystem(user user);
    user update();
    void run();
    int getCourseList(Course *list);
    void selectCourse();
    int getSelectedList();
    bool save();
    bool isSelected(string id);
    void remove();
};
