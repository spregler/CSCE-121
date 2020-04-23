#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include "School.h"
#include "AttendanceRecord.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;
using std::stoi;


void School::addStudents(string filename) {
  ifstream fin(filename);
  if (!fin.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!fin.eof()) {
    string line;
    getline(fin, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
      students.push_back(Student(uin, name));
    }
  }
}

void School::addCourses(string filename) {
  ifstream fin(filename);
  if (!fin.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!fin.eof()) {
    string line;
    getline(fin, line);
    istringstream ss(line);

    string id;
    getline(ss, id, ',');
    string startHour;
    getline(ss, startHour, ':');
    string startMin;
    getline(ss, startMin, ',');
    string endHour;
    getline(ss, endHour, ':');
    string endMin;
    getline(ss, endMin, ',');
    string title;
    getline(ss, title);



    if (!ss.fail()) {
      Date startTime(stoi(startHour), stoi(startMin));
      Date endTime(stoi(endHour), stoi(endMin));
      courses.push_back(Course(id, title, startTime, endTime));
    } 
  }
}

void School::listStudents() const{
  if (students.size() == 0) {
    cout << "No Students" << endl;
    return;
  }
  for (Student s : students) {
    cout << s.get_id() << "," << s.get_name() << endl;
  }
}

void School::listCourses() const{
  if (courses.size() == 0) {
    cout << "No Courses" << endl;
    return;
  }
  for (Course c : courses) {
    cout << c.getID() << "," << c.getStartTime().getTime(false) << "," 
      << c.getEndTime().getTime(false) << "," <<c.getTitle() << endl;
  }
}

void School::addAttendanceData(string filename) {
  ifstream fin(filename);
  if (!fin.is_open()) {
    cout << "Unable to open file: " << filename << endl;
    return;
  }
  while (!fin.eof()) {
    string line;
    getline(fin, line);
    istringstream ss(line);

    string year;
    getline(ss, year, '-');
    string month;
    getline(ss, month, '-');
    string day;
    getline(ss, day, ' ');
    string hour;
    getline(ss, hour, ':');
    string min;
    getline(ss, min, ':');
    string sec;
    getline(ss, sec, ',');
    string course_id;
    getline(ss, course_id, ',');
    string student_id;
    getline(ss, student_id);

    if (!ss.fail()) {
      for (Course& c : courses) {  // pass by reference
        if (c.getID() == course_id) {
          c.addAttendanceRecord(AttendanceRecord(course_id, student_id, Date(stoi(year), stoi(month), stoi(day), stoi(hour), stoi(min), stoi(sec))));
          break;
        }
      }
    }
  }
}

void School::outputCourseAttendance(string course_id) const {
  bool found = false;
  for (Course c : courses) {
    if (c.getID() == course_id) {
      c.outputAttendance();
      found = true;
      break;
    }
  }

  if (!found) {
    cout << "Could not find course matching course id" << endl;
  }
}

void School::outputStudentAttendance(string student_id, string course_id) const {
  bool found = false;
  for (Course c : courses) {
    if (c.getID() == course_id) {
      c.outputAttendance(student_id);
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "Could not find course matching course id" << endl;
  }
}