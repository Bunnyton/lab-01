// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void from_json(const nlohmann::json& j, Student& s);

#endif  // INCLUDE_STUDENT_HPP_
