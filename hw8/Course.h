#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "Date.h"
#include "AttendanceRecord.h"

class Course {
  std::string id;
  std::string title;
  Date startTime;
  Date endTime;
  std::vector<AttendanceRecord> attendanceRecords;

public:
  Course(std::string id, std::string title, Date startTime, Date endTime);
  std::string getID() { return id; }
  std::string getTitle() { return title; }
  Date getStartTime(){ return startTime; }
  Date getEndTime() { return endTime; }
  void addAttendanceRecord(AttendanceRecord ar);
  void outputAttendance() const;
  void outputAttendance(std::string student_id) const;
};

#endif