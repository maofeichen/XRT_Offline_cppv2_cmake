#include <iostream>
#include "adpt_detectavalan.h"
#include "xt_file.h"

using namespace std;

DetectAvalanche::DetectAvalanche(string &lp, 
								 string& bp, 
								 string &od, 
								 bool &is_dump, 
								 string &ct)
{
	lp_ = lp;
	bp_ = bp;
	od_ = od;
	is_dump_ = is_dump;
	ct_ = ct;
}

void 
DetectAvalanche::detect()
{
    cout << "Input Log: \t" << lp_ << endl;
    cout << "Input Buf: \t" << bp_ << endl;
    cout << "Output Drec: \t" << od_ << endl;
    cout << "Is Dump: \t" << is_dump_ << endl;
   	cout << "Current Time: \t" << ct_ << endl;

   	vector<string> log;

   	XT_File fl(lp_);
   	fl.read(log);
}