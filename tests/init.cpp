#include <shared_ptr.cpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("ctor1", "[ctor1]"){
  shared_ptr<int> sp;
  REQUIRE(!sp.get());
}

SCENARIO("ctor2", "[ctor2]"){
  shared_ptr<int> sp(new int(7));
  REQUIRE(*sp==7);
  REQUIRE(sp.countref()==1);
}

