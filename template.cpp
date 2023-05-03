#include <string.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace nlohmann::literals;

void manifest();
void transform(std::string from, std::string to);
void transformTemplate(std::string to);

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    std::cerr << "No arguments found" << std::endl;
    return 1;
  }

  std::string action = argv[1];

  if (!action.compare("manifest"))
    manifest();
  else if (!action.compare("transform"))
    transform(argv[2], argv[3]);
  else
    std::cerr << "Invalid action: " << action << std::endl;

  return 0;
}

void manifest()
{
  json output = R"(
    {
      "name": "template",
      "version": "0.1",
      "description": "This is a template package.",
      "transforms": [
        {
          "from": "template",
          "to": ["html"],
          "arguments": []
        }
      ]
    }
  )"_json;

  std::cout << output.dump() << std::endl;
}

void transform(std::string from, std::string to)
{
  if (!from.compare("template"))
    transformTemplate(to);
  else
    std::cerr << "Package does not support: " << from << std::endl;
}

void transformTemplate(std::string to)
{

  std::string in = "", buffer;
  while (std::getline(std::cin, buffer))
    in.append(buffer);

  json input = json::parse(in);
  std::string content = input["data"];

  json output = json::array();
  if (!to.compare("html"))
  {
    std::ostringstream oss;
    oss << content;

    output.push_back(json::parse(R"( {"name": "raw", "data": "<a>"} )"));
    output.push_back(json::parse(R"( {"name": "raw", "data": ""} )"));
    output.push_back(json::parse(R"( {"name": "raw", "data": "</a>"} )"));

    output[1]["data"] = oss.str();
    std::cout << output.dump() << std::endl;
  }
  else
  {
    std::cerr << "Cannot convert template to: " << to << std::endl;
  }
}