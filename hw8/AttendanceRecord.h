#ifndef ATTENDANCERECORD_H
#define ATTENDANCERECORD_H

#include <string>
#include "Date.h"

class AttendanceRecord {
  std::string course_id;
  std::string student_id;
  Date time;

  public:
    AttendanceRecord(std::string course_id, std::string student_id, Date time);
    std::string getCourseID() const { return course_id; }
    std::string getStudentID() const { return student_id; }
    Date getDate() const { return time; }
};

#endif