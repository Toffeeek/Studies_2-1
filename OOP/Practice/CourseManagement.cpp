#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Teacher;

//======================== Teacher Class ========================//
class Teacher
{
private:
    string name;
    string designation;
    double minimumContactHour;
    double currentLoad;

public:
    Teacher(string n, string d, double m)
        : name(n), designation(d), minimumContactHour(m), currentLoad(0) {}

    string getName() const
    {
        return name;
    }

    string getDesignation() const
    {
        return designation;
    }

    double getMinimumContactHour() const
    {
        return minimumContactHour;
    }

    double getCurrentLoad() const
    {
        return currentLoad;
    }

    void addLoad(double hour)
    {
        currentLoad += hour;
    }

    void reduceLoad(double hour)
    {
        currentLoad -= hour;
        if (currentLoad < 0)
            currentLoad = 0;
    }

    void displayTeacher() const
    {
        cout << "Name: " << name
             << ", Designation: " << designation
             << ", Minimum Contact Hour: " << minimumContactHour
             << ", Current Load: " << currentLoad << endl;
    }
};

//======================== Course Base Class ========================//
class Course
{
protected:
    string courseTitle;
    string courseCode;
    double effectiveContactHour;
    int totalSections;

public:
    Course(string title, string code, double ech, int sec)
        : courseTitle(title), courseCode(code),
          effectiveContactHour(ech), totalSections(sec) {}

    virtual ~Course() {}

    string getCourseTitle() const
    {
        return courseTitle;
    }

    string getCourseCode() const
    {
        return courseCode;
    }

    double getEffectiveContactHour() const
    {
        return effectiveContactHour;
    }

    int getTotalSections() const
    {
        return totalSections;
    }

    virtual int getTeachersPerSection() const = 0;
    virtual string getCourseType() const = 0;
};

//======================== Derived Course Classes ========================//
class TheoryCourse : public Course
{
public:
    TheoryCourse(string title, string code, double ech, int sec)
        : Course(title, code, ech, sec) {}

    int getTeachersPerSection() const override
    {
        return 1;
    }

    string getCourseType() const override
    {
        return "Theory";
    }
};

class LabCourse : public Course
{
public:
    LabCourse(string title, string code, double ech, int sec)
        : Course(title, code, ech, sec) {}

    int getTeachersPerSection() const override
    {
        return 2;
    }

    string getCourseType() const override
    {
        return "Lab";
    }
};

class ThesisProjectCourse : public Course
{
public:
    ThesisProjectCourse(string title, string code, double ech, int sec)
        : Course(title, code, ech, sec) {}

    int getTeachersPerSection() const override
    {
        return 1;
    }

    string getCourseType() const override
    {
        return "Thesis/Project";
    }
};

//======================== Assignment Info Class ========================//
// This class represents one assignment relation:
// which teacher is assigned to which course and section
class AssignmentRecord
{
public:
    Teacher *teacher;
    Course *course;
    int section;

    AssignmentRecord(Teacher *t, Course *c, int s)
        : teacher(t), course(c), section(s) {}
};

//======================== Separate Assignment Manager Class ========================//
// This is the class explicitly required by the question.
class CourseAssignmentManager
{
private:
    vector<Teacher *> teachers;
    vector<Course *> courses;
    vector<AssignmentRecord> assignments;

public:
    void addTeacher(Teacher *t)
    {
        teachers.push_back(t);
    }

    void addCourse(Course *c)
    {
        courses.push_back(c);
    }

    // Count how many teachers are already assigned to a given section of a course
    int countAssignedTeachers(Course *c, int section) const
    {
        int count = 0;
        for (const auto &a : assignments)
        {
            if (a.course == c && a.section == section)
                count++;
        }
        return count;
    }

    // Check whether a teacher is already assigned to a specific course section
    bool isAlreadyAssigned(Teacher *t, Course *c, int section) const
    {
        for (const auto &a : assignments)
        {
            if (a.teacher == t && a.course == c && a.section == section)
                return true;
        }
        return false;
    }

    // 1. Assign a course object to a teacher object
    bool assignCourseToTeacher(Teacher *t, Course *c, int section)
    {
        if (section < 1 || section > c->getTotalSections())
        {
            cout << "Invalid section number.\n";
            return false;
        }

        if (isAlreadyAssigned(t, c, section))
        {
            cout << "Teacher already assigned to this course section.\n";
            return false;
        }

        if (countAssignedTeachers(c, section) >= c->getTeachersPerSection())
        {
            cout << "This section is already fully assigned.\n";
            return false;
        }

        assignments.push_back(AssignmentRecord(t, c, section));
        t->addLoad(c->getEffectiveContactHour());

        cout << t->getName() << " assigned to "
             << c->getCourseCode() << " Section " << section << endl;
        return true;
    }

    // 2. Detach a course object from a teacher object
    // Partial detachment is possible
    bool detachCourseFromTeacher(Teacher *t, Course *c, int section)
    {
        for (auto it = assignments.begin(); it != assignments.end(); ++it)
        {
            if (it->teacher == t && it->course == c && it->section == section)
            {
                t->reduceLoad(c->getEffectiveContactHour());
                assignments.erase(it);

                cout << t->getName() << " detached from "
                     << c->getCourseCode() << " Section " << section << endl;
                return true;
            }
        }

        cout << "Assignment not found.\n";
        return false;
    }

    // Optional: detach teacher from all sections of a course
    bool detachCourseFromTeacher(Teacher *t, Course *c)
    {
        bool found = false;

        for (auto it = assignments.begin(); it != assignments.end();)
        {
            if (it->teacher == t && it->course == c)
            {
                t->reduceLoad(c->getEffectiveContactHour());
                it = assignments.erase(it);
                found = true;
            }
            else
            {
                ++it;
            }
        }

        if (found)
            cout << t->getName() << " detached from all sections of "
                 << c->getCourseCode() << endl;
        else
            cout << "No assignment found for detachment.\n";

        return found;
    }

    // 3. Display all teachers whose load is lower than minimum contact hour
    void displayTeachersBelowMinimumLoad() const
    {
        cout << "\nTeachers below minimum contact hour:\n";
        bool found = false;

        for (Teacher *t : teachers)
        {
            if (t->getCurrentLoad() < t->getMinimumContactHour())
            {
                t->displayTeacher();
                found = true;
            }
        }

        if (!found)
            cout << "None\n";
    }

    // 4. Display all courses that are not fully assigned
    void displayUnassignedCourses() const
    {
        cout << "\nCourses not fully assigned:\n";
        bool found = false;

        for (Course *c : courses)
        {
            int remaining = 0;

            for (int sec = 1; sec <= c->getTotalSections(); sec++)
            {
                int assigned = countAssignedTeachers(c, sec);
                remaining += (c->getTeachersPerSection() - assigned);
            }

            if (remaining > 0)
            {
                cout << c->getCourseCode() << " - " << c->getCourseTitle()
                     << " (" << c->getCourseType() << ")"
                     << ", Remaining teacher assignment(s): " << remaining << endl;
                found = true;
            }
        }

        if (!found)
            cout << "All courses are fully assigned.\n";
    }

    // 5. Display the current assignment of courses to teachers
    void displayCurrentAssignments() const
    {
        cout << "\nCurrent Assignment of Courses to Teachers:\n";

        if (assignments.empty())
        {
            cout << "No assignments found.\n";
            return;
        }

        for (const auto &a : assignments)
        {
            cout << "Teacher: " << a.teacher->getName()
                 << " -> Course: " << a.course->getCourseCode()
                 << " (" << a.course->getCourseTitle() << ")"
                 << ", Section: " << a.section << endl;
        }
    }
};

//======================== Main Function ========================//
int main()
{
    Teacher t1("Dr. Rahman", "Professor", 9);
    Teacher t2("Ms. Asha", "Lecturer", 6);
    Teacher t3("Mr. Karim", "Assistant Professor", 6);
    Teacher t4("Ms. Nabila", "Lecturer", 6);

    TheoryCourse c1("Object Oriented Programming", "CSE4301", 3, 2);
    LabCourse c2("Object Oriented Programming Lab", "CSE4302", 1.5, 2);
    ThesisProjectCourse c3("Thesis/Project", "CSE4900", 3, 1);

    CourseAssignmentManager manager;

    manager.addTeacher(&t1);
    manager.addTeacher(&t2);
    manager.addTeacher(&t3);
    manager.addTeacher(&t4);

    manager.addCourse(&c1);
    manager.addCourse(&c2);
    manager.addCourse(&c3);

    manager.assignCourseToTeacher(&t1, &c1, 1);
    manager.assignCourseToTeacher(&t2, &c1, 2);

    manager.assignCourseToTeacher(&t1, &c2, 1);
    manager.assignCourseToTeacher(&t3, &c2, 1);
    manager.assignCourseToTeacher(&t2, &c2, 2);
    manager.assignCourseToTeacher(&t4, &c2, 2);

    manager.assignCourseToTeacher(&t3, &c3, 1);

    manager.displayCurrentAssignments();
    manager.displayTeachersBelowMinimumLoad();
    manager.displayUnassignedCourses();

    cout << "\nAfter partial detachment:\n";
    manager.detachCourseFromTeacher(&t1, &c2, 1);

    manager.displayCurrentAssignments();
    manager.displayTeachersBelowMinimumLoad();
    manager.displayUnassignedCourses();

    return 0;
}