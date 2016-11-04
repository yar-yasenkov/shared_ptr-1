#include <stack.cpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("ctor1", "[ctor1]"){
  shared_ptr<int> sp;
  REQUIRE(!sp.get());
}
