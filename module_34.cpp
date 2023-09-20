#include <concepts>
#include <string>
#include <iostream>

template <typename T>
concept ComplexConcept =
	requires(const T v) {
		{ v.hash() } -> std::convertible_to<long>;
	}
&&
	requires(const T v) {
		{ v.to_string() } -> std::same_as<std::string>;
	}
&&
	!std::has_virtual_destructor<T>::value
;

struct MyStruct
{
	int val{0};
	MyStruct(int v) : val(v) {}
	//virtual ~MyStruct() { std::cout << "destructor working" << std::endl; }
	long hash() const { return static_cast<long> (val); }
	std::string to_string() const { return "this is string"; }
};

void foo(ComplexConcept auto &t)
{
	std::cout << t.hash() << std::endl;
	std::cout << t.to_string() << std::endl;
}

int main() {
	MyStruct s(50);
	foo(s);
}