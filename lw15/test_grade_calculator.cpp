#include <iostream>
#include <fstream>
#include <string>

#include "test_helpers.h"

#include "grade_calculator.h"



bool test_() {
    bool pass = true;

    RESULT(pass);
    return pass;
}

bool test_default_constructor() {
    bool pass = true;

    GradeCalculator gc;
    ASSERT_FALSE(gc.get_has_final_exam());
    ASSERT_EQ(gc.get_final_exam(), 0);
    ASSERT_FALSE(gc.get_has_syllabus_ack());
    ASSERT_EQ(gc.get_exam_grades().size(), 0);
    ASSERT_EQ(gc.get_hw_grades().size(), 0);
    ASSERT_EQ(gc.get_hw_redemption_grades().size(), 0);
    ASSERT_EQ(gc.get_lw_grades().size(), 0);
    ASSERT_EQ(gc.get_zybook_challenge_grades().size(), 0);
    ASSERT_EQ(gc.get_zybook_participation_grades().size(), 0);

    RESULT(pass);
    return pass;
}

bool test_load_grades() {
    bool pass = true;

    {
        std::string filename = "does_not_exist";
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
    }

    {
        std::string filename = "empty_file";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_category";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "invalid-category" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_final_exam_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam so-many" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_exam_number";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam two 100" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_hw_number";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw five 96.5" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_hw_redemption_number";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw-redemption six 105" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_exam_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 2 hundred" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_hw_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw 5 ninety six point 5" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_hw_redemption_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw-redemption 6 one oh five" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_lw_number";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "lw four 1" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_lw_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "lw 4 TRUE" << std::endl;   // should be all lowercase: "true"
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_zybook_number";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "zybook onep 100" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "unrecognized_zybook_type";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "zybook 1x 100" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_zybook_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "zybook 12p %001" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "invalid_syllabus_ack_grade";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "syllabus-ack 100" << std::endl;
        GradeCalculator gc;
        ASSERT_THROW(gc.load_grades(filename));
        remove(filename.c_str());
    }

    {
        std::string filename = "every_happy_path";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam 98.76" << std::endl;
        fout << "exam 2 75.2" << std::endl;
        fout << "hw 2 100" << std::endl;
        fout << "hw-redemption 7 105" << std::endl;
        fout << "lw 3 1" << std::endl;
        fout << "lw 5 true" << std::endl;
        fout << "lw 7 0" << std::endl;
        fout << "lw 11 false" << std::endl;
        fout << "zybook 3p 89.5" << std::endl;
        fout << "zybook 2c 76" << std::endl;
        fout << "syllabus-ack 1" << std::endl;
        fout << "syllabus-ack 0" << std::endl;
        fout << "syllabus-ack false" << std::endl;
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_TRUE(gc.get_has_final_exam());
        ASSERT_EQ(gc.get_final_exam(), 98.76);
        ASSERT_EQ(gc.get_exam_grades().size(), 2);
        ASSERT_EQ(gc.get_exam_grades().at(0), 0);
        ASSERT_EQ(gc.get_exam_grades().at(1), 75.2);
        ASSERT_EQ(gc.get_hw_grades().size(), 2);
        ASSERT_EQ(gc.get_hw_grades().at(0), 0);
        ASSERT_EQ(gc.get_hw_grades().at(1), 100);
        ASSERT_EQ(gc.get_hw_redemption_grades().size(), 7);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(0), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(1), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(2), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(3), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(4), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(5), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(6), 105);
        ASSERT_EQ(gc.get_lw_grades().size(), 11);
        ASSERT_FALSE(gc.get_lw_grades().at(0));
        ASSERT_FALSE(gc.get_lw_grades().at(1));
        ASSERT_TRUE(gc.get_lw_grades().at(2));
        ASSERT_FALSE(gc.get_lw_grades().at(3));
        ASSERT_TRUE(gc.get_lw_grades().at(4));
        ASSERT_FALSE(gc.get_lw_grades().at(5));
        ASSERT_FALSE(gc.get_lw_grades().at(6));
        ASSERT_FALSE(gc.get_lw_grades().at(7));
        ASSERT_FALSE(gc.get_lw_grades().at(8));
        ASSERT_FALSE(gc.get_lw_grades().at(9));
        ASSERT_FALSE(gc.get_lw_grades().at(10));
        ASSERT_EQ(gc.get_zybook_participation_grades().size(), 3);
        ASSERT_EQ(gc.get_zybook_participation_grades().at(0), 0);
        ASSERT_EQ(gc.get_zybook_participation_grades().at(1), 0);
        ASSERT_EQ(gc.get_zybook_participation_grades().at(2), 89.5);
        ASSERT_EQ(gc.get_zybook_challenge_grades().size(), 2);
        ASSERT_EQ(gc.get_zybook_challenge_grades().at(0), 0);
        ASSERT_EQ(gc.get_zybook_challenge_grades().at(1), 76);
        ASSERT_TRUE(gc.get_has_syllabus_ack());
    }

    RESULT(pass);
    return pass;
}

bool test_parameterized_constructor() {
    bool pass = true;

    {
        std::string filename = "every_happy_path";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam 98.76" << std::endl;
        fout << "exam 2 75.2" << std::endl;
        fout << "hw 2 100" << std::endl;
        fout << "hw-redemption 7 105" << std::endl;
        fout << "lw 3 1" << std::endl;
        fout << "lw 5 true" << std::endl;
        fout << "lw 7 0" << std::endl;
        fout << "lw 11 false" << std::endl;
        fout << "zybook 3p 89.5" << std::endl;
        fout << "zybook 2c 76" << std::endl;
        fout << "syllabus-ack 1" << std::endl;
        fout << "syllabus-ack 0" << std::endl;
        fout << "syllabus-ack false" << std::endl;
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc(filename);
        remove(filename.c_str());
        ASSERT_TRUE(gc.get_has_final_exam());
        ASSERT_EQ(gc.get_final_exam(), 98.76);
        ASSERT_EQ(gc.get_exam_grades().size(), 2);
        ASSERT_EQ(gc.get_exam_grades().at(0), 0);
        ASSERT_EQ(gc.get_exam_grades().at(1), 75.2);
        ASSERT_EQ(gc.get_hw_grades().size(), 2);
        ASSERT_EQ(gc.get_hw_grades().at(0), 0);
        ASSERT_EQ(gc.get_hw_grades().at(1), 100);
        ASSERT_EQ(gc.get_hw_redemption_grades().size(), 7);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(0), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(1), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(2), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(3), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(4), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(5), 0);
        ASSERT_EQ(gc.get_hw_redemption_grades().at(6), 105);
        ASSERT_EQ(gc.get_lw_grades().size(), 11);
        ASSERT_FALSE(gc.get_lw_grades().at(0));
        ASSERT_FALSE(gc.get_lw_grades().at(1));
        ASSERT_TRUE(gc.get_lw_grades().at(2));
        ASSERT_FALSE(gc.get_lw_grades().at(3));
        ASSERT_TRUE(gc.get_lw_grades().at(4));
        ASSERT_FALSE(gc.get_lw_grades().at(5));
        ASSERT_FALSE(gc.get_lw_grades().at(6));
        ASSERT_FALSE(gc.get_lw_grades().at(7));
        ASSERT_FALSE(gc.get_lw_grades().at(8));
        ASSERT_FALSE(gc.get_lw_grades().at(9));
        ASSERT_FALSE(gc.get_lw_grades().at(10));
        ASSERT_EQ(gc.get_zybook_participation_grades().size(), 3);
        ASSERT_EQ(gc.get_zybook_participation_grades().at(0), 0);
        ASSERT_EQ(gc.get_zybook_participation_grades().at(1), 0);
        ASSERT_EQ(gc.get_zybook_participation_grades().at(2), 89.5);
        ASSERT_EQ(gc.get_zybook_challenge_grades().size(), 2);
        ASSERT_EQ(gc.get_zybook_challenge_grades().at(0), 0);
        ASSERT_EQ(gc.get_zybook_challenge_grades().at(1), 76);
        ASSERT_TRUE(gc.get_has_syllabus_ack());
    }

    RESULT(pass);
    return pass;
}

bool test_exam_average() {
    bool pass = true;

    {
        std::string filename = "exam_average_no_final";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 1 81" << std::endl;
        fout << "exam 2 66" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.exam_average(), 49);
    }

    {
        std::string filename = "exam_average_final_better";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 1 81" << std::endl;
        fout << "exam 2 64" << std::endl;
        fout << "final-exam 73" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.exam_average(), 73);
    }

    {
        std::string filename = "exam_average_final_worse";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 1 80" << std::endl;
        fout << "exam 2 67" << std::endl;
        fout << "final-exam 60" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.exam_average(), 69);
    }

    RESULT(pass);
    return pass;
}

bool test_zybook_average() {
    bool pass = true;

    {
        std::string filename = "zybook_average_none_over_85";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "zybook 1p 23" << std::endl;
        fout << "zybook 2p 85" << std::endl;
        fout << "zybook 3p 32" << std::endl;
        fout << "zybook 4p 85" << std::endl;
        fout << "zybook 5p 70" << std::endl;
        fout << "zybook 1c 52" << std::endl;
        fout << "zybook 2c 72" << std::endl;
        fout << "zybook 3c 38" << std::endl;
        fout << "zybook 4c 5" << std::endl;
        fout << "zybook 5c 54" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.zybook_average(), 66.6);
    }

    {
        std::string filename = "zybook_average_some_over_85";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "zybook 1p 71" << std::endl;
        fout << "zybook 2p 49" << std::endl;
        fout << "zybook 3p 80" << std::endl;
        fout << "zybook 4p 61" << std::endl;
        fout << "zybook 5p 91" << std::endl;
        fout << "zybook 1c 1" << std::endl;
        fout << "zybook 2c 63" << std::endl;
        fout << "zybook 3c 5" << std::endl;
        fout << "zybook 4c 98" << std::endl;
        fout << "zybook 5c 97" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.zybook_average(), 76.6);
    }

    {
        std::string filename = "zybook_average_all_over_85";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "zybook 1p 86" << std::endl;
        fout << "zybook 2p 97" << std::endl;
        fout << "zybook 3p 86" << std::endl;
        fout << "zybook 4p 87" << std::endl;
        fout << "zybook 5p 89" << std::endl;
        fout << "zybook 1c 87" << std::endl;
        fout << "zybook 2c 86" << std::endl;
        fout << "zybook 3c 99" << std::endl;
        fout << "zybook 4c 86" << std::endl;
        fout << "zybook 5c 87" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.zybook_average(), 100);
    }

    RESULT(pass);
    return pass;
}

bool test_hw_average() {
    bool pass = true;

    {
        std::string filename = "hw_average_no_redemptions";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw 1 31" << std::endl;
        fout << "hw 2 7" << std::endl;
        fout << "hw 3 17" << std::endl;
        fout << "hw 4 57" << std::endl;
        fout << "hw 5 35" << std::endl;
        fout << "hw 6 45" << std::endl;
        fout << "hw 7 54" << std::endl;
        fout << "hw 8 53" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.hw_average(), 37.375);
    }

    {
        std::string filename = "hw_average_with_redemptions";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw 1 77" << std::endl;
        fout << "hw 2 47" << std::endl;
        fout << "hw 3 43" << std::endl;
        fout << "hw 4 12" << std::endl;
        fout << "hw 5 66" << std::endl;
        fout << "hw 6 86" << std::endl;
        fout << "hw 7 27" << std::endl;
        fout << "hw 8 21" << std::endl;
        fout << "hw-redemption 3 74" << std::endl;
        fout << "hw-redemption 8 80" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.hw_average(), 53);
    }

    {
        std::string filename = "hw_average_with_redemptions2";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "hw 1 41" << std::endl;
        fout << "hw 2 91" << std::endl;
        fout << "hw 3 72" << std::endl;
        fout << "hw 4 59" << std::endl;
        fout << "hw 5 39" << std::endl;
        fout << "hw 6 58" << std::endl;
        fout << "hw 7 69" << std::endl;
        fout << "hw 8 17" << std::endl;
        fout << "hw-redemption 3 24" << std::endl;
        fout << "hw-redemption 4 32" << std::endl;
        fout << "hw-redemption 7 70" << std::endl;
        fout << "hw-redemption 8 7" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.hw_average(), 55.8125);
    }

    RESULT(pass);
    return pass;
}

bool test_lw_average() {
    bool pass = true;

    {
        std::string filename = "lw_average";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "lw 1 1" << std::endl;
        fout << "lw 2 1" << std::endl;
        fout << "lw 3 1" << std::endl;
        fout << "lw 5 1" << std::endl;
        fout << "lw 8 1" << std::endl;
        fout << "lw 13 1" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.lw_average(), 600./13);
    }

    {
        std::string filename = "lw_average2";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "lw 10 1" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.lw_average(), 10);
    }

    RESULT(pass);
    return pass;
}

bool test_final_grade_numeric() {
    bool pass = true;

    {
        std::string filename = "final_grade_numeric";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 1 81" << std::endl;
        fout << "exam 2 64" << std::endl;
        fout << "final-exam 73" << std::endl;
        // E: 73
        fout << "zybook 1p 71" << std::endl;
        fout << "zybook 2p 49" << std::endl;
        fout << "zybook 3p 80" << std::endl;
        fout << "zybook 4p 61" << std::endl;
        fout << "zybook 5p 91" << std::endl;
        fout << "zybook 1c 1" << std::endl;
        fout << "zybook 2c 63" << std::endl;
        fout << "zybook 3c 5" << std::endl;
        fout << "zybook 4c 98" << std::endl;
        fout << "zybook 5c 97" << std::endl;
        // Z: 73.5
        fout << "hw 1 41" << std::endl;
        fout << "hw 2 91" << std::endl;
        fout << "hw 3 72" << std::endl;
        fout << "hw 4 59" << std::endl;
        fout << "hw 5 39" << std::endl;
        fout << "hw 6 58" << std::endl;
        fout << "hw 7 69" << std::endl;
        fout << "hw 8 17" << std::endl;
        fout << "hw-redemption 3 24" << std::endl;
        fout << "hw-redemption 4 32" << std::endl;
        fout << "hw-redemption 7 70" << std::endl;
        fout << "hw-redemption 8 7" << std::endl;
        // HW: 55.8125
        fout << "lw 1 1" << std::endl;
        fout << "lw 2 1" << std::endl;
        fout << "lw 3 1" << std::endl;
        fout << "lw 5 1" << std::endl;
        fout << "lw 8 1" << std::endl;
        fout << "lw 13 1" << std::endl;
        // LW: 600/13
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_LE(64.8717 - gc.final_grade_numeric(), 1e-4);
    }

    RESULT(pass);
    return pass;
}

bool test_final_grade_letter() {
    bool pass = true;

    {
        std::string filename = "final_grade_letter_no_syllabus_ack";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 1 81" << std::endl;
        fout << "exam 2 64" << std::endl;
        fout << "final-exam 73" << std::endl;
        // E: 73
        fout << "zybook 1p 71" << std::endl;
        fout << "zybook 2p 49" << std::endl;
        fout << "zybook 3p 80" << std::endl;
        fout << "zybook 4p 61" << std::endl;
        fout << "zybook 5p 91" << std::endl;
        fout << "zybook 1c 1" << std::endl;
        fout << "zybook 2c 63" << std::endl;
        fout << "zybook 3c 5" << std::endl;
        fout << "zybook 4c 98" << std::endl;
        fout << "zybook 5c 97" << std::endl;
        // Z: 73.5
        fout << "hw 1 41" << std::endl;
        fout << "hw 2 91" << std::endl;
        fout << "hw 3 72" << std::endl;
        fout << "hw 4 59" << std::endl;
        fout << "hw 5 39" << std::endl;
        fout << "hw 6 58" << std::endl;
        fout << "hw 7 69" << std::endl;
        fout << "hw 8 17" << std::endl;
        fout << "hw-redemption 3 24" << std::endl;
        fout << "hw-redemption 4 32" << std::endl;
        fout << "hw-redemption 7 70" << std::endl;
        fout << "hw-redemption 8 7" << std::endl;
        // HW: 55.8125
        fout << "lw 1 1" << std::endl;
        fout << "lw 2 1" << std::endl;
        fout << "lw 3 1" << std::endl;
        fout << "lw 5 1" << std::endl;
        fout << "lw 8 1" << std::endl;
        fout << "lw 13 1" << std::endl;
        // LW: 600/13
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.final_grade_letter(), 'F');
    }

    {
        std::string filename = "final_grade_letter_with_syllabus_ack";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "exam 1 81" << std::endl;
        fout << "exam 2 64" << std::endl;
        fout << "final-exam 73" << std::endl;
        // E: 73
        fout << "zybook 1p 71" << std::endl;
        fout << "zybook 2p 49" << std::endl;
        fout << "zybook 3p 80" << std::endl;
        fout << "zybook 4p 61" << std::endl;
        fout << "zybook 5p 91" << std::endl;
        fout << "zybook 1c 1" << std::endl;
        fout << "zybook 2c 63" << std::endl;
        fout << "zybook 3c 5" << std::endl;
        fout << "zybook 4c 98" << std::endl;
        fout << "zybook 5c 97" << std::endl;
        // Z: 73.5
        fout << "hw 1 41" << std::endl;
        fout << "hw 2 91" << std::endl;
        fout << "hw 3 72" << std::endl;
        fout << "hw 4 59" << std::endl;
        fout << "hw 5 39" << std::endl;
        fout << "hw 6 58" << std::endl;
        fout << "hw 7 69" << std::endl;
        fout << "hw 8 17" << std::endl;
        fout << "hw-redemption 3 24" << std::endl;
        fout << "hw-redemption 4 32" << std::endl;
        fout << "hw-redemption 7 70" << std::endl;
        fout << "hw-redemption 8 7" << std::endl;
        // HW: 55.8125
        fout << "lw 1 1" << std::endl;
        fout << "lw 2 1" << std::endl;
        fout << "lw 3 1" << std::endl;
        fout << "lw 5 1" << std::endl;
        fout << "lw 8 1" << std::endl;
        fout << "lw 13 1" << std::endl;
        // LW: 600/13
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.final_grade_letter(), 'D');
    }

    {
        std::string filename = "final_grade_letter_A";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam 90" << std::endl;
        // E: 90
        fout << "zybook 1p 75" << std::endl;
        fout << "zybook 2p 75" << std::endl;
        // Z: 85
        fout << "hw 1 80" << std::endl;
        fout << "hw-redemption 1 100" << std::endl;
        // HW: 90
        fout << "lw 1 1" << std::endl;
        // LW: 100
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.final_grade_letter(), 'A');
    }

    {
        std::string filename = "final_grade_letter_B";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam 90" << std::endl;
        // E: 90
        fout << "zybook 1p 75" << std::endl;
        fout << "zybook 2p 75" << std::endl;
        // Z: 85
        fout << "hw 1 80" << std::endl;
        fout << "hw-redemption 1 100" << std::endl;
        // HW: 90
        fout << "lw 2 1" << std::endl;
        // LW: 50
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.final_grade_letter(), 'B');
    }

    {
        std::string filename = "final_grade_letter_C";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam 70" << std::endl;
        // E: 70
        fout << "zybook 1p 75" << std::endl;
        fout << "zybook 2p 75" << std::endl;
        // Z: 85
        fout << "hw 1 80" << std::endl;
        fout << "hw-redemption 1 100" << std::endl;
        // HW: 90
        fout << "lw 2 1" << std::endl;
        // LW: 50
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.final_grade_letter(), 'C');
    }

    {
        std::string filename = "final_grade_letter_D_because_exams";
        std::ofstream fout(filename);
        ASSERT_TRUE(fout.is_open());
        fout << "final-exam 50" << std::endl;
        // E: 50
        fout << "zybook 1p 85" << std::endl;
        fout << "zybook 2p 85" << std::endl;
        // Z: 100
        fout << "hw 1 90" << std::endl;
        fout << "hw-redemption 1 100" << std::endl;
        // HW: 95
        fout << "lw 1 1" << std::endl;
        // LW: 100
        fout << "syllabus-ack true" << std::endl;
        GradeCalculator gc;
        ASSERT_NO_THROW(gc.load_grades(filename));
        remove(filename.c_str());
        ASSERT_EQ(gc.final_grade_letter(), 'D');
    }

    RESULT(pass);
    return pass;
}

int main() {
    unsigned int pass_cnt = 0, fail_cnt = 0;

    // already passing because starter code already implemented the methods
    TEST(default_constructor);
    TEST(load_grades);
    TEST(parameterized_constructor);

    TEST(exam_average);
    TEST(zybook_average);
    TEST(hw_average);
    TEST(lw_average);
    TEST(final_grade_numeric);
    TEST(final_grade_letter);

    std::cout << "passing " << pass_cnt << "/" << (pass_cnt + fail_cnt) << " tests" << std::endl;

    if (fail_cnt == 0) {
        std::cout << std::endl;
        std::cout << "demo: grades.txt" << std::endl;
        GradeCalculator gc("grades.txt");
        std::cout << "      exam average: " << gc.exam_average() << std::endl;
        std::cout << "    zybook average: " << gc.zybook_average() << std::endl;
        std::cout << "        hw average: " << gc.hw_average() << std::endl;
        std::cout << "        lw average: " << gc.lw_average() << std::endl;
        std::cout << "       final grade: " << gc.final_grade_numeric() << " (" << gc.final_grade_letter() << ")" << std::endl;
        std::cout << "  modifier applied: ";
        if (!gc.get_has_syllabus_ack()) {
            std::cout << "F due to no syllabus acknowledgment" << std::endl;
        } else if (gc.exam_average() < 60) {
            std::cout << "max grade of D due to exam average < 60" << std::endl;
        } else {
            std::cout << "none" << std::endl;
        }
    }
}