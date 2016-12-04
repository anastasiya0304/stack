#include "stack.hpp"
#include <catch.hpp>
#include <iostream>
#include <thread>
#include<mutex>
using namespace std;
 
SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("top", "[top]"){
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.pop();
  REQUIRE(s.top()==2);
}


SCENARIO("empty", "[empty]"){
  stack<int> s1;
  s1.push(1);
  REQUIRE(s1.empty()==false);
}

SCENARIO("empty2", "[empty2]"){
  stack<int> s1;
  s1.push(1);
  s1.pop();
  REQUIRE(s1.empty()==true);
}

SCENARIO("empty3", "[empty3]"){
  stack<int> s1;
  s1.push(1);
  s1.push(2);
  s1.pop();
  s1.top();
  
  REQUIRE(s1.empty()==false);
}

SCENARIO("mutex", "[mutex]"){
  stack<int> s1;
  s1.push(1);
  s1.push(2);
  
  thread potok_1(&stack<int>::push, &s1, 3);
  potok_1.join();
  REQUIRE(s1.top()==3);
  thread potok_2(&stack<int>::pop, &s1);
  potok_2.join();
  REQUIRE(s1.top()==2);
}
