#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void thisIsATest() {
    std::string first, second, expected;
    first = "Hello";
    second = "World";
    expected = "Hello World";
    ASSERT_EQUAL(expected, first + second);
}

void runAllTests(int argc, char const *argv[]) {
    cute::suite s;
    //TODO add your test here
    s.push_back(CUTE(thisIsATest));
    cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
    cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
    runAllTests(argc, argv);
    return 0;
}
