// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <tuple>
#include <cassert>

#include "custom_tie_tuple.h"


using namespace std;

auto getPerson()
{
      const std::string name = "Petia";
      const std::string secondName = "Ivanoff";
      const std::size_t age = 23;
      const std::string department = "Sale";
      return std::make_tuple(
          name, secondName, age, department);
}


int main()
{
      std::string name, secondName, department;
      std::size_t age;

      custom_tie(name, secondName, age, department) = getPerson();
      assert(name == "Petia");
      assert(secondName == "Ivanoff");
      assert(age == 23);
      assert(department == "Sale");

      return 0;
}
