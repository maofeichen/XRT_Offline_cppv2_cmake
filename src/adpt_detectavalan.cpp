#include <iostream>

#include "adpt_cons.h"
#include "adpt_detectavalan.h"
#include "adpt_file.h"

#include "xt_detect.h"
#include "xt_file.h"
#include "xt_log.h"
#include "xt_preprocess.h"
#include "xt_util.h"

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

   	vector<string> slog;
   	vector<Record> rlog;

	list<Alivefunc> lst_alvfunc;
	vector<t_AliveFunctionCall> vec_alvfunc;

   	XT_File fl(lp_);
   	fl.read(slog);

   	XTLog olog(slog);
   	cout << "total xt log records:\t" << olog.getRecordSize() << endl;

   	// no need slog, free
   	slog.clear();
   	cout << "free string log vector..." << endl;

   	// converts string to Record format
   	XT_PreProcess prprcss;
   	// prprcss.convertToRec(slog, rlog);
   	prprcss.convertToRec(olog, rlog);
   	cout << "total Record entries:\t" << rlog.size() << endl;

   	// init alive buffers from liveness
   	AdptFile adptfl(lp_, bp_, od_, is_dump_, ct_);
   	adptfl.alvbuf_read(lst_alvfunc);
   	to_vec_alvfunc(lst_alvfunc, vec_alvfunc);
   	// print_valvfunc(vec_alvfunc);
   	// for(auto it = lst_alvfunc.begin(); it != lst_alvfunc.end(); ++it) {
   	// 	it->print();
   	// }

   	// helper_vec_alivefunc(vec_alvfunc);

    Detect dtct(vec_alvfunc, olog, rlog);
    dtct.adpt_detect_cipher();
}

void 
DetectAvalanche::to_vec_alvfunc(list<Alivefunc>& lst_alvfunc,
								vector<t_AliveFunctionCall>& vec_alvfunc)
{
	cout << "converting alive functions from list to vector..." << endl;

	for(auto it = lst_alvfunc.begin(); it != lst_alvfunc.end(); ++it) {
		// traverse each alive function call
		t_AliveFunctionCall alvfunc;

		alvfunc.call_mark 		= it->get_call_fir();
		alvfunc.sec_call_mark 	= it->get_call_sec();
		alvfunc.ret_mark 		= it->get_ret_fir();
		alvfunc.sec_ret_mark 	= it->get_ret_sec();

		for(auto it_ab = it->get_lst_alvbuf().begin(); it_ab != it->get_lst_alvbuf().end(); ++it_ab) {
			// traverse each alive buffer
			t_AliveContinueBuffer alvbuf;

			alvbuf.beginAddress = it_ab->get_begin_addr();
			alvbuf.size 		= it_ab->get_bit_sz();

			for(auto it_rec = it_ab->get_recs().begin(); it_rec != it_ab -> get_recs().end(); ++it_rec) {
				uint64_t recidx = get_index(*it_rec);
				recidx--;	// offset by one, results in seg fault
				alvbuf.vNodeIndex.push_back(recidx);
			}

			alvfunc.vAliveContinueBuffer.push_back(alvbuf);
		}

		vec_alvfunc.push_back(alvfunc);
	}	
}

uint64_t 
DetectAvalanche::get_index(std::string& rec)
{
	vector<string> v = XT_Util::split(rec.c_str(), '\t');
	string s_idx 	 = v.back();
	uint64_t idx 	 = stoull(s_idx, nullptr, 10);
	return idx;
}

void 
DetectAvalanche::print_valvfunc(std::vector<t_AliveFunctionCall>& vec_alvfunc)
{
	for(auto it = vec_alvfunc.begin(); it != vec_alvfunc.end(); ++it) {
		cout << it->call_mark << endl;
		cout << it->sec_call_mark << endl;
		cout << cons::dash_sprtr << endl;

		for(auto it_ab = it->vAliveContinueBuffer.begin(); it_ab != it->vAliveContinueBuffer.end(); ++it_ab) {
			cout << "0x" << hex << it_ab->beginAddress << " - " << dec << it_ab->size / 8 << endl;
			for(auto it_idx = it_ab->vNodeIndex.begin(); it_idx != it_ab->vNodeIndex.end(); ++it_idx) {
				cout << dec << *it_idx << endl;
			}
			cout << cons::dash_sprtr << endl;
		}

		cout << it->ret_mark << endl;
		cout << it->sec_ret_mark << endl;
		cout << cons::star_sprtr << endl;
	}	
}

void 
DetectAvalanche::helper_vec_alivefunc(std::vector<t_AliveFunctionCall>& vec_alvfunc)
{
	uint32_t addr    = 0xbfd4464c;
 	uint32_t sz;

	vector<t_AliveContinueBuffer> v_cntnsbuf;

	sz = 64;	
 	adpt_find_cntnsbuf(vec_alvfunc, v_cntnsbuf, addr, sz*8);
 	cout << "total alive buffers with addr 0xbfd4464c size 64 bytes:\t" << v_cntnsbuf.size() << endl;
 
 	sz = 64;	
 	adpt_find_cntnsbuf_by_sz(vec_alvfunc, v_cntnsbuf, sz*8);
 	cout << "total alive buffers with size 64 bytes:\t" << v_cntnsbuf.size() << endl;

 	sz = 32;	
 	adpt_find_cntnsbuf_by_sz(vec_alvfunc, v_cntnsbuf, sz*8);
 	cout << "total alive buffers with size 32 bytes:\t" << v_cntnsbuf.size() << endl;	

  	sz = 24;	
 	adpt_find_cntnsbuf_by_sz(vec_alvfunc, v_cntnsbuf, sz*8);
 	cout << "total alive buffers with size 24 bytes:\t" << v_cntnsbuf.size() << endl;			

 	sz = 16;	
 	adpt_find_cntnsbuf_by_sz(vec_alvfunc, v_cntnsbuf, sz*8);
 	cout << "total alive buffers with size 16 bytes:\t" << v_cntnsbuf.size() << endl;	
}

void 
DetectAvalanche::adpt_find_cntnsbuf(std::vector<t_AliveFunctionCall>& vec_alvfunc,
									std::vector<t_AliveContinueBuffer>& v_cntnsbuf,
                           			uint32_t addr,
                           			uint32_t sz)
{
  for(auto it = vec_alvfunc.begin(); it != vec_alvfunc.end(); ++it) {
    for(auto it_ab = it->vAliveContinueBuffer.begin(); it_ab != it->vAliveContinueBuffer.end(); ++it_ab) {
      if(addr == it_ab->beginAddress && sz == it_ab->size) {
        v_cntnsbuf.push_back(*it_ab);
      }
    }
  } 
}


void 
DetectAvalanche::adpt_find_cntnsbuf_by_sz(std::vector<t_AliveFunctionCall>& vec_alvfunc,
										  std::vector<t_AliveContinueBuffer>& v_cntnsbuf,
                                 		  uint32_t sz)
{
  for(auto it = vec_alvfunc.begin(); it != vec_alvfunc.end(); ++it) {
    for(auto it_ab = it->vAliveContinueBuffer.begin(); it_ab != it->vAliveContinueBuffer.end(); ++it_ab) {
      if(sz == it_ab->size) {
        v_cntnsbuf.push_back(*it_ab);
      }
    }
  }  
}
