#include "stack.hpp"
#include <catch.hpp>
SCENARIO("stack: init", "[init]") {
	stack<int> a;
	REQUIRE(sizeof(a) != 0);
	REQUIRE(a.count() == 0);
}
SCENARIO("stack: operator==", "[op==]") {
	stack<int> a, b;
	a.push(5);
	a.push(3);
	a.push(5);
	b.push(5);
	b.push(3);
	b.push(5);
	REQUIRE(a == b);
}
SCENARIO("stack: operator=", "[op=]") {
	stack<int> a;
	a.push(1);
	stack<int> b;
	b = a;
	REQUIRE(b == a);
}
SCENARIO("stack: count", "[op=]") {
	stack<int> a;
	a.push(7);
	a.push(6);
	a.push(8);
	a.push(9);
	REQUIRE(a.count() == 4);
}
SCENARIO("stack: pop", "[op=]") {
	stack<int> a;
	a.push(7);
	a.push(6);
	a.push(8);
	a.push(9);
	a.pop();
	REQUIRE(a.count() == 3);
}
SCENARIO("Stack: copy", "[copy]")
{
	stack<int> a;
	a.push(7);
	a.push(6);
	a.push(8);
	a.push(9);
	stack<int> b = a;
	REQUIRE(b == a);
}
