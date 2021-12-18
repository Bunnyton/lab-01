// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#ifndef INCLUDE_PRINT_HPP_
#define INCLUDE_PRINT_HPP_

#define STUD_PARAM_LENGTH 4

#include <vector>
#include <string>

#include "student.hpp"

//-----------------BASE PRINT FUNCTIONS-----------------------------------------
void print(std::ostream& os, std::string* str, int maxlength);
void print(std::ostream& os, std::string str, int maxlength);
void print_pass(std::ostream& os, const int* maxlength);
void print_header(std::ostream& os, int* maxlength);
void print(const Student& student, std::ostream& os, int* maxlength);
//--------------------------------GET TABLE SIZE--------------------------------
int* get_column_size(const std::vector<Student>& students);
//-------------------------------PRINT FUNCTION---------------------------------
void print(const std::vector<Student>& students, std::ostream& os);

#endif  // INCLUDE_PRINT_HPP_
