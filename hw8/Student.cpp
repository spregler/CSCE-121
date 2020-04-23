#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Student.h"

using std::cout;
using std::endl;
using std::string;


Student::Student(string student_id, string name) : id(student_id), name(name) {}

void Student::addCourse(string course_id) {
	bool duplicate = false;

	for (unsigned int i = 0; i < course_ids.size(); i++) {
		if (course_ids.at(i) == course_id) {
			duplicate = true;
			break;
		}
	}

	if (duplicate == false) {
		course_ids.push_back(course_id);
	}
}

void Student::listCourses() const {
	if (course_ids.empty()) {
		cout << "No Records" << endl;
		return;
	}
	cout << "Courses for " << id << endl;
	for (string i : course_ids) {
		cout << i << endl;
	}
}
