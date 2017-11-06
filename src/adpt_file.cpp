#include <fstream>
#include <iostream>

#include "adpt_cons.h"
#include "adpt_file.h"
#include "xt_util.h"

using namespace std;

AdptFile::AdptFile(std::string &lp, 
			 	   std::string& bp, 
			 	   std::string &od, 
			 	   bool &is_dump, 
			 	   std::string &ct)
{
	lp_ = lp;
	bp_ = bp;
	od_ = od;
	is_dump_ = is_dump;
	ct_ = ct;
}

void 
AdptFile::buf_read(std::list<Alivefunc>& lst_alvfunc)
{
	cout << "reading buffers from liveness analysis result: \n\t" 
		 << bp_ << endl; 

	ifstream fin(bp_.c_str() );
	if(fin.is_open() ) {
		int fc = 0;
		string line;

		while(getline(fin, line) ) {
			if(line.compare(cons::star_sprtr) == 0) {
				// cleanmerge_flow(lst_alvfunc);
				init_alvfunc(lst_alvfunc);
				buflog_.clear();
				fc++;
			} else {
				buflog_.push_back(line);
			}
		}

		cout << "finishing read buffers " 
			 << "- total alive functions: \t" << dec << fc << endl;

	} else {
		cout << "buf_read - error open file: \t" << bp_ << endl;
		return;
	}

	fin.close();	
}


void 
AdptFile::init_alvfunc(std::list<Alivefunc>& lst_alvfunc)
{
	cout << "initing alive function call..." << endl;

	Alivefunc alvfunc;
	vector<string> v;

	int sz = buflog_.size();
	alvfunc.set_call_fir(buflog_[0]);
	alvfunc.set_call_sec(buflog_[1]);
	alvfunc.set_ret_fir(buflog_[sz-2]);
	alvfunc.set_ret_sec(buflog_[sz-1]);

	for(auto it = buflog_.begin()+3; it != buflog_.end() - 2; ++it) {
		if(it->compare(cons::dash_sprtr) == 0) {
			init_alvbuf(v, alvfunc);
			v.clear();
		} else {
			v.push_back(*it);
		}
	}

	lst_alvfunc.push_back(alvfunc);
}

void 
AdptFile::init_alvbuf(std::vector<std::string>& buf, Alivefunc& alvfunc)
{
	string buf_info = buf[0];

	vector<string> v_bi = XT_Util::split(buf_info.c_str(), '\t');
	string s_baddr 		= v_bi[0].substr(2, string::npos);
	string s_sz 		= v_bi[1];

	uint32_t baddr = stoul(s_baddr, nullptr, 16);
	uint32_t sz    = stoul(s_sz, nullptr, 10);
	vector<string> rec(buf.begin()+1, buf.end() );
	
	Alivebuf alvbuf(baddr, sz, rec);
	alvfunc.insert_buf(alvbuf);
}
