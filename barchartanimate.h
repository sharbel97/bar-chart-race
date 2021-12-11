// barchartanimate.h
// The BarChartAnimate class basically collects a BarChart object
// in an array along with other variables that define the content
// of each chart like title, xlabel, sources. This class then
// has functions that would handle reading data from file, collecting
// the charts, and then animatign those charts by looping through the
// BarCharts type array to create an animation of charts with constant
// amount of data being fed to it.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map> 
#include <vector>
#include <unistd.h>
#include "myrandom.h"
#include "barchart.h"

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts;  // pointer to a C-style array
    int size;
    int capacity;

    string title;
    string xlabel;
    string source;

    map<string, string> colorMap;
    int unsigned colorIndex = 0;

    //
    // collectFrames function is a helper function to addFrames
    // its job to simply handle the file reading completely
    // and append to our barcharts array.
    void collectFrames(ifstream &file) {
        int num = 0;
        string name, name1, value, category, frame;
        getline(file, name1);   // gets the white space
        getline(file, name1);   // gets the top number
        if (!file.fail()) {
            num = stoi(name1);
        
        BarChart bc(num);
        while (num > 0) {       // keep getting lines until num = 0
            getline(file, frame, ',');
            getline(file, name, ',');
            getline(file, name1, ',');
            getline(file, value, ',');
            getline(file, category);
            // adding category -> color to colorMap
            if (colorMap.count(category) == 0) {
                if (colorIndex == COLORS.size()) {
                    colorIndex = 0;
                }
                colorMap[category] = COLORS[colorIndex];
                colorIndex++;
            }
            bc.addBar(name, stoi(value), category);
            bc.setFrame(frame);
            num--;
        }
        barcharts[size] = bc;
        size++;
        }
    }

 public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
        barcharts = nullptr;
        capacity = 4;
        size = 0;
        barcharts = new BarChart[capacity];
        this->title = title;
        this->xlabel = xlabel;
        this->source = source;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        if (barcharts != nullptr) {
            delete[] barcharts;
            barcharts = nullptr;
        }
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
    	// growing array if size reaches capacity
        if (size == capacity) {
            int newCapacity = capacity * 2;
            BarChart* newbarcharts = new BarChart[newCapacity];
            //copy array elements to the bigger array
            for (int i = 0; i < size; ++i) {
                newbarcharts[i] = barcharts[i];
            }
            delete[] barcharts;
            barcharts = newbarcharts;
            capacity = newCapacity;
        }
        collectFrames(file);
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
        if (endIter > size || endIter < 0) {
            endIter = size;
        } else {
            size = endIter;
        }

        for (int i = 0; i < endIter; ++i) {
            usleep(3*microsecond);
            output << CLEARCONSOLE;
            output << BLACK << title << endl;
            output << BLACK << source << endl;
            barcharts[i].graph(output, colorMap, top);
            output << BLACK << xlabel << endl;
            output << BLACK <<"Frame: " << barcharts[i].getFrame() << endl;
        }
	}

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize() {
        return size;
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart& operator[](int i){
        if (i < 0 || i >= size)
        {
          throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }
};
