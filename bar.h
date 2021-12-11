// bar.h
// This Bar class will contain member variables for the individual
// bars that will appear on the chart. Each bar will have a name,
// category and value variables. Along with different getter and
// setter methods for each of the private member variables.
// We also needed to overload the comparison operators in order to
// compare bars values without needing to use the dot-operator because
// it wouldn't work since the variables are private.

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    // TO DO:  Define private member variables for this class
    // NOTE: You should not be allocating memory on the heap for this class.
    string name, category;
    int value;

 public:

    // default constructor:
    Bar() {
        name = "";
        category = "";
        value = 0;
    }

    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        this->name = name;
        this->value = value;
        this->category = category;
    }

    // destructor:
    virtual ~Bar() {
    }

    // getName:
	string getName() {
        return name;
	}

    // getValue:
	int getValue() {
        return value;
	}

    // getCategory:
	string getCategory() {
        return category;
	}

	// operators
    // This allows you to compare two Bar objects.
    // Comparison should be based on the Bar's value.
	bool operator<(const Bar &other) const {
        return value < other.value;
	}

	bool operator<=(const Bar &other) const {
        return value <= other.value;
	}

	bool operator>(const Bar &other) const {
        return value > other.value;
	}

	bool operator>=(const Bar &other) const {
        return value >= other.value;
	}
};
