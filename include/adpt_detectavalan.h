#ifndef ADPT_DETECTAVALAN_H_
#define ADPT_DETECTAVALAN_H_ 

#include <string>

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
};

#endif
