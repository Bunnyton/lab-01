// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#include "print.hpp"

//-------------------------------BASE PRINT FUNCTIONS-------------------

void print_endl(std::ostream& os) { os << '|' << std::endl; }

void print(std::ostream& os, std::string str, int maxlength) {
  os << '|';
  if (maxlength == 0) return;

  unsigned space_front_count =
      (maxlength - str.length()) / 2 + (maxlength - str.length()) % 2 + 1;
  unsigned space_back_count = (maxlength - str.length()) / 2 + 1;

  for (unsigned i = 0; i < space_front_count; ++i) os << ' ';
  os << str;
  for (unsigned i = 0; i < space_back_count; ++i) os << ' ';
}

void print_pass(std::ostream& os, const int* maxlength) {
  for (int i = 0; i < STUD_PARAM_LENGTH; ++i) {
    os << '|';
    for (int j = 0; j < maxlength[i] + 2; ++j) os << '-';
  }
  print_endl(os);
}

void print_header(std::ostream& os, int* maxlength) {
  print(os, std::string("name"), *maxlength);
  print(os, std::string("group"), *(maxlength + 1));
  print(os, std::string("avg"), *(maxlength + 2));
  print(os, std::string("debt"), *(maxlength + 3));
  print_endl(os);
  print_pass(os, maxlength);
}

void print(const Student& student, std::ostream& os, int* maxlength) {
  const std::any name = std::any(student.name);
  const std::any* any[STUD_PARAM_LENGTH] = {&name, &student.group, &student.avg,
                                            &student.debt};
  std::string null_str = "null";
  int* maxlength_ptr = maxlength;
  for (const auto item : any) {
    if (item->type() == typeid(std::nullptr_t)) {
      print(os, null_str, *(maxlength_ptr));
    } else if (item->type() == typeid(std::string)) {
      print(os, std::any_cast<std::string>(*item), *(maxlength_ptr));
    } else if (item->type() == typeid(std::size_t)) {
      print(os, std::to_string(std::any_cast<std::size_t>(*item)),
            *(maxlength_ptr));
    } else if (item->type() == typeid(double)) {
      print(os, std::to_string(std::any_cast<double>(*item)), *(maxlength_ptr));
    } else {
      print(os,
            std::to_string(
                std::any_cast<std::vector<std::string>>(item)->size()) +
                (std::string) " items",
            *(maxlength_ptr));
    }
    maxlength_ptr++;
  }
  print_endl(os);
  print_pass(os, maxlength);
}

//--------------------------------GET TABLE SIZE--------------------------------
static void length_compare(std::string str, int& length) {
  if (static_cast<int>(str.length()) > length)
    length = static_cast<int>(str.length());
}

int* get_column_size(const std::vector<Student>& students) {
  int* maxlength = new int[STUD_PARAM_LENGTH]{0, 0, 0, 0};
  for (const auto& student : students) {
    std::any name = std::any(student.name);
    const std::any* any[STUD_PARAM_LENGTH] = {&name, &student.group,
                                              &student.avg, &student.debt};

    std::string null_str = std::string("null");

    int* maxlength_ptr = maxlength;
    for (const auto item : any) {
      if (item->type() == typeid(std::nullptr_t)) {
        length_compare(null_str, *maxlength_ptr);
      } else if (item->type() == typeid(std::string)) {
        length_compare(std::any_cast<std::string>(*item), *maxlength_ptr);
      } else if (item->type() == typeid(std::size_t)) {
        length_compare(std::to_string(std::any_cast<std::size_t>(*item)),
                       *maxlength_ptr);
      } else if (item->type() == typeid(double)) {
        length_compare(std::to_string(std::any_cast<double>(*item)),
                       *maxlength_ptr);
      } else {
        length_compare(
            std::to_string(
                std::any_cast<std::vector<std::string>>(item)->size()) +
                (std::string) " items",
            *maxlength_ptr);
      }
      maxlength_ptr++;
    }
  }
  length_compare(std::string("name"), *maxlength);
  length_compare(std::string("group"), *(maxlength + 1));
  length_compare(std::string("avg"), *(maxlength + 2));
  length_compare(std::string("debt"), *(maxlength + 3));
  return maxlength;
}
//-------------------------------PRINT FUNCTION--------------------------------
void print(const std::vector<Student>& students, std::ostream& os) {
  int* maxlength = get_column_size(students);
  print_header(os, maxlength);
  for (const auto& student : students) print(student, os, maxlength);
  delete[] maxlength;
}
