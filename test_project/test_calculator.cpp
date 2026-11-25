#include "../mp2-lab3-stack/Calculator.h"
#include "gtest.h"

TEST(Calculator, can_set_infix) {
	Calculator calc;
	std::string str = "(2 + 6) / 4";
	ASSERT_NO_THROW(calc.setInfix(str));
}