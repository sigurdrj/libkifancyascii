#include <iostream>
#include "libkifancyascii.hpp"

using namespace libkifancyascii;

int main(){
	Table t;

	t.contents = {{"Example text", "More text"}, {"And some more text", "here"}};

	t.print();
}
