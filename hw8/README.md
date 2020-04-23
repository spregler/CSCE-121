Individual Homework: Attendance Swipe
Objectives
●	Work with classes
○	Constructors
○	Getters and Setters
○	Encapsulation
■	Public/Private
●	Work with vectors and strings rather than arrays and c-strings.
Grading breakdown
Points	
95	Runs correctly
5	Pre-homework quiz
	
100	MAX TOTAL POINTS

Overview
There are classes that collect attendance information by swiping student IDs. Using your formidable knowledge of C++ classes, you’ve been asked to set up a system that loads attendance data into a program and produces reports of who was present.

Requirements & Roadmap
You are given the main function that will use the following classes. You need to implement the following classes based on the header files provided for each.
Note: Just because you have a member function declaration, you don’t have to have the function definition for the program to compile unless the program needs to use that function. 
●	So as you develop you only need to define the functions you need at the moment. 
●	You don’t have to get everything done at once. 
●	You might need to comment out calls in the attendance.cpp file to functions you have not yet defined/written to be able to compile, execute and debug.

1.	Add students (from a file)
a.	Requires:
i.	Student class definition
ii.	Student constructor
iii.	School::addStudents(string filename)
●	Add Student instance to vector of students
a.	Do not duplicate a student that is already there.
iv.	School::listStudents()
●	Use to output and test
●	Should output “No Students” if there are no students
●	Example output:
166100166,Tanja Cypert
660166834,Bernice Ringer
930740679,Brent Slagle

2.	Add courses (from a file)
a.	Requires:
i.	Course class definition
ii.	Course constructor
iii.	School::addCourses(string filename)
●	Add Course instance to vector of courses
a.	Do not duplicate a course that is already there
iv.	School::listCourses()
●	Use to output and test
●	Should output “No Courses” if there are no courses
●	Example output:
551,15:00,15:50,Biochemistry, Wine, and Practices in the Environmental Sciences
587,15:55,17:10,Pirates, Mineralogy, and Purpose
521,08:00,08:50,Cryptozoology

3.	Add attendance (from a file)
a.	Requires:
i.	AttendanceRecord class definition
ii.	AttendanceRecord constructor
iii.	School::addAttendanceData(string filename)
iv.	Course::addAttendanceRecord(AttendanceRecord ar)
●	Only add if it is valid, i.e. the time is greater than or equal to the start time and less than or equal to the end time.
●	If it does not get added, then output “did not save this record.” to standard out.
4.	Output course attendance
a.	Lists all attendance records for the specified course
b.	Should output “No Records” if none are found.
 
c.	Example output:
8/26/2019 15:08:56,551,166100166
8/26/2019 15:39:06,551,930740679
8/26/2019 15:41:54,551,660166834
8/28/2019 15:02:45,551,930740679
8/28/2019 15:10:15,551,166100166
8/28/2019 15:17:46,551,660166834
8/30/2019 15:05:03,551,930740679
8/30/2019 15:35:24,551,166100166
9/2/2019 15:12:05,551,930740679
9/2/2019 15:20:19,551,660166834
9/4/2019 15:06:47,551,930740679
9/4/2019 15:24:52,551,166100166
9/4/2019 15:48:34,551,660166834
9/6/2019 15:28:29,551,166100166

5.	Output course attendance for a specific student
a.	List all attendance records for the specified course and student
b.	Should output “No Records” if none are found.
c.	Example output:
8/27/2019 16:36:44,587,930740679
8/29/2019 16:20:05,587,930740679
9/3/2019 16:05:59,587,930740679
9/5/2019 16:39:17,587,930740679

The classes that you are required to implement are:
You will have to implement any class member functions that are not already provided for you.
1.	Class School
a.	See header file
2.	Class Student
a.	See header file
3.	Class Course
a.	See header file
4.	Class AttendanceRecord
a.	See header file
 
The main program and starter code
Source Code
Get Code
●	attendance.cpp
●	School.h & School.cpp
●	Course.h & Course.cpp
●	Student.h & Student.cpp
●	AttendanceRecord.h & AttendanceRecord.cpp
●	Date.h & Date.cpp

Data Files
Get Data
●	student-small.csv
●	course-small.csv
●	attendance-small.csv
●	student-medium.csv
●	course-medium.csv
●	attendance-medium.csv
●	student-large.csv
●	course-large.csv
●	attendance-large.csv

Useful functions & classes
You may use any of the functionality provided by C++ strings in your solution. Most students may find the following operations useful:
●	getline 
○	An example of how to use this is provided in
School::addStudents(string filename)
●	vector
○	push_back
○	size
●	istringstream
○	An example of how to use this is provided in
School::addStudents(string filename)
●	setw()
○	An example of how to use this is provided in
string Date::getDate()
●	setfill()
○	An example of how to use this is provided in
string Date::getDate()
