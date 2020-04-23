Requirements
The specification for the lab is the grading section of the syllabus and the test cases (provided in starter code).

You must score at least 85 points to earn a grade of complete on this lab work.

Submit only:

grade_calculator.h
grade_calculator.cpp
Starter Code
The starter code includes a complete grade_calculator.h and skeleton grade_calculator.cpp.  Everything except the actual grade calculation is already implemented for you (https://www.youtube.com/watch?v=79DijItQXMM).

Tests (the exact same as on Mimir) are provided in test_grade_calculator.cpp. The provided test helper file (test_helpers.h) is a bootleg version of Google Test, Google's C++ test framework (which is what Mimir uses for unit testing).

The file grades.txt provides an example grade file that is used to demonstrate the use of the GradeCalculator class once you are passing all of the unit tests.  A quick and dirty use case:

GradeCalculator gc("grades.txt");
std::cout << gc.final_grade_letter() << std::endl;
Grade File Format
Grades are specified as: <category> <number> <grade>.

<category> values are: exam, final-exam, hw, hw-redemption, lw, zybook, syllabus-ack

<number> values are positive integers and are required for every category except final-exam and syllabus-ack. zyBook grades include a 'p' or 'c' after the number to denote whether the assignment was participation or challenge.

<grade> values for exam, final-exam, hw, hw-redemption, zybook are specified as percentages (i.e. numbers from 0.0 to 100.0, but sometimes more when there is extra credit).  Converting a fraction to a decimal percentage is easy: 123/164 = (do the division) 0.75 = (multiply by 100) 75%.

<grade> values for lw, syllabus-ack are boolean-valued.

Getting Started
Read the class definition in grade_calculator.h.

Find this block:

////////////////////////////////////////////////////////////////////////////////
// TODO(student): implement these methods

double exam_average() const; 
double zybook_average() const;
double hw_average() const;
double lw_average() const;
// does not apply modifiers
double final_grade_numeric() const;
// includes application of modifiers
char final_grade_letter() const;

////////////////////////////////////////////////////////////////////////////////
Find the corresponding block in grade_calculator.cpp:

////////////////////////////////////////////////////////////////////////////////
// TODO(student): implement these methods

double GradeCalculator::exam_average() const {
    // TODO(student)
    return -1;
} 

double GradeCalculator::zybook_average() const {
    // TODO(student)
    return -1;
}

double GradeCalculator::hw_average() const {
    // TODO(student)
    return -1;
}

double GradeCalculator::lw_average() const {
    // TODO(student)
    return -1;
}

// does not apply modifiers
double GradeCalculator::final_grade_numeric() const {
    // TODO(student)
    return -1;
}

// includes application of modifiers
char GradeCalculator::final_grade_letter() const {
    // TODO(student)
    return 'X';
}

////////////////////////////////////////////////////////////////////////////////
Take note of the TODO(student) comments.

Have fun.

ACTIONS
