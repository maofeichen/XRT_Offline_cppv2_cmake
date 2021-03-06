#ifndef ADPT_DETECTAVALAN_H_
#define ADPT_DETECTAVALAN_H_ 

#include <list>
#include <string>
#include <vector>

#include "adpt_alivefunc.h"
#include "xt_data.h"

class DetectAvalanche
{
public:
	DetectAvalanche(std::string &lp, 
					std::string& bp, 
					std::string &od, 
					bool &is_dump, 
					std::string &ct);
	~DetectAvalanche() {};
	void detect();
private:
	std::string lp_;
	std::string bp_;
	std::string od_;
	bool is_dump_;
	std::string ct_;

	void to_vec_alvfunc(std::list<Alivefunc>& lst_alvfunc,
						std::vector<t_AliveFunctionCall>& vec_alvfunc);
	uint64_t get_index(std::string& rec);

	void print_valvfunc(std::vector<t_AliveFunctionCall>& vec_alvfunc);
	void helper_vec_alivefunc(std::vector<t_AliveFunctionCall>& vec_alvfunc);
	void adpt_find_cntnsbuf(std::vector<t_AliveFunctionCall>& vec_alvfunc,
							std::vector<t_AliveContinueBuffer>& v_cntnsbuf,
                            uint32_t addr,
                            uint32_t sz);
  	void adpt_find_cntnsbuf_by_sz(std::vector<t_AliveFunctionCall>& vec_alvfunc,
  								  std::vector<t_AliveContinueBuffer>& v_cntnsbuf,
                                  uint32_t sz);
};

#endif
