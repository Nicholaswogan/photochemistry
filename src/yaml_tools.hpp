#pragma once

#include <vector>
#include "yaml-cpp/yaml.h"
#include "exception.hpp"

void check_for_keys(const YAML::Node n, const std::string place, const std::vector<std::string> &keys);
void check_for_keys(const YAML::Node n, const std::string place, const std::string key);