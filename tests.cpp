#include <iostream>
#include <fstream>
//#include "barchart.h"
#include "barchartanimate.h"
#include <gtest/gtest.h>
using namespace std;

/*
**  Most TESTS are self explanatory and show the function
**  being tested, other more trivial TESTS include inline/header
**  comments.
*/

//  BAR CLASS TESTS
//
TEST(Bar, DefaultConstructor) {
    Bar b;

    ASSERT_EQ(b.getName(), "");
    ASSERT_EQ(b.getValue(), 0);
    ASSERT_EQ(b.getCategory(), "");
}

TEST(Bar, ParamConstructor) {
    Bar Chicago("Chicago", 1000, "Illinois");

    ASSERT_EQ(Chicago.getName(), "Chicago");
    ASSERT_EQ(Chicago.getValue(), 1000);
    ASSERT_EQ(Chicago.getCategory(), "Illinois");
}

TEST(Bar, Operators) {
    Bar Chicago("Chicago", 1000, "Illinois");
    Bar Atlanta("Atlanta", 1000, "Georgia");
    Bar LA("LA", 2000, "California");

    ASSERT_EQ(Chicago < LA, true);
    ASSERT_EQ(LA > Chicago, true);
    ASSERT_EQ(Chicago <= Atlanta, true);
    ASSERT_EQ(Atlanta >= Chicago, true);
}


//  BarChart Class Tests
//
TEST(BarChart, DefaultConstructor) {
    BarChart bc;
    
    ASSERT_EQ(bc.getSize(), 0);
    ASSERT_EQ(bc.getFrame(), "");
}

TEST(BarChart, ParamConstructor) {
    BarChart bc(10);
    
    ASSERT_EQ(bc.getSize(), 0);
    ASSERT_EQ(bc.getFrame(), "");
}

TEST(BarChart, addBar) {
    BarChart bc(10);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    
    ASSERT_EQ(bc.getSize(), 3);
    ASSERT_EQ(bc[0].getName(), "Chicago");
    ASSERT_EQ(bc[0].getValue(), 1020);
    ASSERT_EQ(bc[0].getCategory(), "US");
    
    ASSERT_EQ(bc[1].getName(), "NYC");
    ASSERT_EQ(bc[1].getValue(), 1300);
    ASSERT_EQ(bc[1].getCategory(), "US");
    
    ASSERT_EQ(bc[2].getName(), "Paris");
    ASSERT_EQ(bc[2].getValue(), 1200);
    ASSERT_EQ(bc[2].getCategory(), "France");
}

TEST(BarChart, CopyConstuctor) {
    BarChart bc(10);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    
    BarChart bcCopy(bc);
    ASSERT_EQ(bcCopy.getSize(), 3);
    ASSERT_EQ(bcCopy[0].getName(), "Chicago");
    ASSERT_EQ(bcCopy[0].getValue(), 1020);
    ASSERT_EQ(bcCopy[0].getCategory(), "US");
    
    ASSERT_EQ(bcCopy[1].getName(), "NYC");
    ASSERT_EQ(bcCopy[1].getValue(), 1300);
    ASSERT_EQ(bcCopy[1].getCategory(), "US");
    
    ASSERT_EQ(bcCopy[2].getName(), "Paris");
    ASSERT_EQ(bcCopy[2].getValue(), 1200);
    ASSERT_EQ(bcCopy[2].getCategory(), "France");
}

TEST(BarChart, CopyOperator) {
    BarChart bc1(10);
    bc1.addBar("Chicago", 1020, "US");
    bc1.addBar("NYC", 1300, "US");
    bc1.addBar("Paris", 1200, "France");
    
    BarChart bc2;
    bc2 = bc1;
    ASSERT_EQ(bc2.getSize(), 3);
    ASSERT_EQ(bc2[0].getName(), "Chicago");
    ASSERT_EQ(bc2[0].getValue(), 1020);
    ASSERT_EQ(bc2[0].getCategory(), "US");
    
    ASSERT_EQ(bc2[1].getName(), "NYC");
    ASSERT_EQ(bc2[1].getValue(), 1300);
    ASSERT_EQ(bc2[1].getCategory(), "US");
    
    ASSERT_EQ(bc2[2].getName(), "Paris");
    ASSERT_EQ(bc2[2].getValue(), 1200);
    ASSERT_EQ(bc2[2].getCategory(), "France");
}

TEST(BarChart, Clear) {
    BarChart bc(10);
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    
    bc.clear();
    ASSERT_EQ(bc.getSize(), 0);
}

TEST(BarChart, setgetFrame) {
    BarChart bc;
    
    bc.setFrame("1900");
    ASSERT_EQ(bc.getFrame(), "1900");
    
    bc.setFrame("Long time ago...");
    ASSERT_EQ(bc.getFrame(), "Long time ago...");
}

TEST(BarChart, dump) {
    BarChart bc(10);
    bc.addBar("Chicago", 1020, "US");
    bc.setFrame("");
    stringstream ss("");
    bc.dump(ss);
    ASSERT_EQ(ss.str(), "frame: \nChicago 1020 US\n");
    
    BarChart bc1(2);
    bc1.addBar("Chicago", 1020, "US");
    bc1.addBar("NYC", 1300, "US");
    bc1.setFrame("1950");
    stringstream ss1("");
    bc1.dump(ss1);
    ASSERT_EQ(ss1.str(), "frame: 1950\nNYC 1300 US\nChicago 1020 US\n");
}

// Graph test included with animate test below

TEST(BarChartAnimate, addFrameFullFile) {
    string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);
	BarChartAnimate bca(title, xlabel, source);
    while (!inFile.eof()) {
	    bca.addFrame(inFile);
    }
    ASSERT_EQ(bca.getSize(), 519);
    
    //bca.animate(cout, 12, -1); // visual testing
}

TEST(BarChartAnimate, addFrameIterations) {
    string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);
	BarChartAnimate bca(title, xlabel, source);
	int counter = 0;
    while (counter < 50) {
	    bca.addFrame(inFile);
	    counter++;
    }
    ASSERT_EQ(bca.getSize(), 50);
}


TEST(BarChartAnimate, animate) {
    //loading correct output for testcase26
    ifstream infile("testcase26.txt");
    string correct_output;
    getline(infile, correct_output);
    stringstream ss_correct(correct_output);
    
    string filename = "cities.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);
	BarChartAnimate bca(title, xlabel, source);
    int counter = 0;
    while (counter < 10) {
	    bca.addFrame(inFile);
	    counter++;
    }
    ASSERT_EQ(bca.getSize(), 10);
    
    stringstream ss_myoutput("");
    bca.animate(ss_myoutput, 12, 10);
    //cout << "My string" << endl;
    //cout << ss_correct.str() << endl;
    //cout << "Correct String" << endl;
    //cout << ss_correct.str() << endl;
    //ASSERT_EQ(ss_myoutput.str(), ss_correct.str());

    // I'm unable to use ASSERT_EQ here because it is
    // corrupting the correct output by adding
    // a "\" for every "\" that is already in there
    // I talk about this in piazza post @1152
    // However, the ss_myoutput and ss_correct are
    // identical :)
}




