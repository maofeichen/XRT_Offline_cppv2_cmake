#ifndef ADPT_FILE_H_
#define ADPT_FILE_H_ 

#include <list>
#include <string>
#include "adpt_alivefunc.h"

class AdptFile
{
public:
	AdptFile(std::string &lp, 
			 std::string& bp, 
			 std::string &od, 
			 bool &is_dump, 
			 std::string &ct);
	~AdptFile() {};

	void alvbuf_read(std::list<Alivefunc>& lst_alvfunc);
private:
	std::string lp_;
	std::string bp_;
	std::string od_;
	bool is_dump_;
	std::string ct_;

	std::vector<std::string> buflog_;

	void init_alvfunc(std::list<Alivefunc>& lst_alvfunc);
	void init_alvbuf(std::vector<std::string>& buf, Alivefunc& alvfunc);
};

#endif