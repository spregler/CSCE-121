#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "grade_calculator.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;

////////////////////////////////////////////////////////////////////////////////
// TODO(student): implement these methods

double GradeCalculator::exam_average() const {
  double sum = 0;
  double avg;

  for (unsigned int i = 0; i < exam_grades.size(); i++) {
    sum += exam_grades.at(i);
  }
  if (has_final_exam) {
    sum += final_exam;
  }

  avg = sum / (exam_grades.size() + 1);
    
  return std::ceil(avg);
} 

double GradeCalculator::zybook_average() const {
  // TODO(student)
  double sum = 0;
  double avg;

  sum = std::accumulate(zybook_participation_grades.begin(), zybook_participation_grades.end(), 0); 
  sum = std::accumulate(zybook_challenge_grades.begin(), zybook_challenge_grades.end(), sum);
  avg = sum / (zybook_challenge_grades.size() + zybook_participation_grades.size()) + 15;

  if (avg > 100) {
    avg = 100;
  }
  return avg;
}

double GradeCalculator::hw_average() const {
  double sum = 0;
  double avg;

  int sz = hw_grades.size();
  std::vector<double> temp(sz);

  for (unsigned int i = 0; i < hw_grades.size(); i++) {
    temp.at(i) = hw_grades.at(i);
  }

  for (unsigned int i = 0; i < hw_redemption_grades.size(); i++) {
    if (hw_redemption_grades.at(i) > hw_grades.at(i)) {
      temp.at(i) = ( (hw_redemption_grades.at(i) - hw_grades.at(i)) / 2) + hw_grades.at(i);
    }
  }

  for (unsigned int i = 0; i < hw_grades.size(); i++) {
    sum += temp.at(i);
  }


  avg = sum / (hw_grades.size());

  return avg;
}

double GradeCalculator::lw_average() const {
  // TODO(student)
  double cnt;
  int sz = lw_grades.size();
  cnt = std::count(lw_grades.begin(), lw_grades.end(), true);

  return cnt * 100 / sz;
}

// does not apply modifiers
double GradeCalculator::final_grade_numeric() const {
  // TODO(student)
  double exam = exam_average();
  double zybook = zybook_average();
  double hw = hw_average();
  double lw = lw_average();
  double final_grade = 0;

  if (has_final_exam == true && final_exam > exam_average()) {
    exam = final_exam;
  }
  
  final_grade = (exam * .5) + (zybook * .07) + (hw * .35) + (lw * .08);

  return final_grade;
}

// includes application of modifiers
char GradeCalculator::final_grade_letter() const {
  // TODO(student)
  char letter;
  const double final_grade = final_grade_numeric();
  // standard cases
  if (final_grade >= 90 && has_syllabus_ack) {
    letter = 'A';
  }
  else if (final_grade >= 80 && has_syllabus_ack) {
    letter = 'B';
  }
  else if (final_grade >= 70 && has_syllabus_ack) {
    letter = 'C';
  }
  else if (final_grade >= 60 && has_syllabus_ack) {
    letter = 'D';
  }
  else {
    letter = 'F';
  }
  // exam modifier
  if (exam_average() <= 60 && final_exam < 60) {
    letter = 'D';
  }

  return letter;
}
////////////////////////////////////////////////////////////////////////////////

void GradeCalculator::read_final_exam(std::ifstream& fin) {
    has_final_exam = true;
    fin >> final_exam;
    if (fin.fail()) {
        throw std::runtime_error("failed to read final exam grade");
    }
}

void GradeCalculator::read_exam_hw_redemption_zybook(std::ifstream& fin, const std::string& category) {
    unsigned number;
    fin >> number;
    if (fin.fail()) {
        throw std::runtime_error("failed to read " + category + " number");
    }

    std::vector<double>* vec;
    if (category == "exam") {
        vec = &exam_grades;
    } else if (category == "hw") {
        vec = &hw_grades;
    } else if (category == "hw-redemption") {
        vec = &hw_redemption_grades;
    } else if (category == "zybook") {
        char type;
        fin >> type;
        if (fin.fail()) {
            // HOW TO REACH THIS?
            throw std::runtime_error("failed to read " + category + " type");
        }
        switch (type) {
            case 'p': vec = &zybook_participation_grades; break;
            case 'c': vec = &zybook_challenge_grades; break;
            default: throw std::runtime_error("unrecognized zybook assignment type: " + type);
        }
    } else {
        throw std::runtime_error("unrecognized category: " + category);
    }
    
    double grade;
    fin >> grade;
    if (fin.fail()) {
      throw std::runtime_error("failed to read "+category+" grade");
    }

    while (number > vec->size()) {
      vec->push_back(0);
    }

    vec->at(number-1) = grade;
}

void GradeCalculator::read_lw(std::ifstream& fin) {
    unsigned number;
    fin >> number;
    if (fin.fail()) {
        throw std::runtime_error("failed to read lw number");
    }

    std::string str;
    fin >> str;
    if (fin.fail()) {
        // HOW TO REACH THIS?
        throw std::runtime_error("failed to read lw grade");
    }

    while (number > lw_grades.size()) {
        lw_grades.push_back(false);
    }

    if (str == "0" || str == "false") {
        lw_grades.at(number-1) = false;
    } else if (str == "1" || str == "true") {
        lw_grades.at(number-1) = true;
    } else {
        throw std::runtime_error("invalid lw grade value: " + str);
    }
}

void GradeCalculator::read_syllabus_ack(std::ifstream& fin) {
    std::string str;
    fin >> str;
    if (fin.fail()) {
        // HOW TO REACH THIS?
        throw std::runtime_error("failed to read syllabus-ack type");
    }
    if (str == "0" || str == "false") {
        has_syllabus_ack = false;
    } else if (str == "1" || str == "true") {
        has_syllabus_ack = true;
    } else {
        throw std::runtime_error("invalid syllabus-ack grade value: " + str);
    }
}

void GradeCalculator::load_grades(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("could not open file");
    }
    while (!fin.eof()) {
        std::string category;
        fin >> category;
        if (fin.fail()) {
            if (fin.eof()) {
                continue;
            } 
            // HOW TO REACH THIS?
            throw std::runtime_error("failed to read category");
        }
        if (category == "final-exam") {
            read_final_exam(fin);
        } else if (category == "exam" || category == "hw" || category == "hw-redemption" || category == "zybook") {
            read_exam_hw_redemption_zybook(fin, category);
        } else if (category == "lw") {
            read_lw(fin);
        } else if (category == "syllabus-ack") {
            read_syllabus_ack(fin);
        } else {
            throw std::runtime_error("invalid category: " + category);
        }
    }
}