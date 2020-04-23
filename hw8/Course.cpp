#include <iostream>
#include <fstream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::cout;
using std::endl;
using std::string;


Course::Course(string id, string title, Date startTime, Date endTime) : 
  id(id), title(title), startTime(startTime), endTime(endTime) {}

void Course::addAttendanceRecord(AttendanceRecord ar) {
  if (ar.getDate() >= startTime && ar.getDate() <= endTime) {
    attendanceRecords.push_back(ar);
  } else {
    cout << "did not save this record." << endl;
  }
}

void Course::outputAttendance() const {
  if (attendanceRecords.empty()) {
    cout << "No Records" << endl;
    return;
  }
  for (AttendanceRecord ar : attendanceRecords) {
    cout << ar.getDate().getDateTime() << "," << ar.getCourseID() << "," << ar.getStudentID() << endl;
  }
}

void Course::outputAttendance(string student_id) const {
  if (attendanceRecords.empty()) {
    cout << "No Records" << endl;
    return;
  }
  bool recordsForStudent = false;
  for (AttendanceRecord ar : attendanceRecords) {
    if (ar.getStudentID() == student_id) {
      cout << ar.getDate().getDateTime() << "," << ar.getCourseID() << "," << ar.getStudentID() << endl;
      recordsForStudent = true;
    }
  }
  if (!recordsForStudent) {
    cout << "No Records" << endl;
  }
} 