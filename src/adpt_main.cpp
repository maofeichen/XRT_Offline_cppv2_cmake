// Adapt the new liveness analysis result to original avalnche detection

#include "boost/program_options.hpp"
#include "adpt_detectavalan.h"

using namespace boost;
namespace po = boost::program_options;

using namespace std;

string 
get_time() {
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );

  string ct = to_string( (now->tm_year + 1900) ) + '-' +
      to_string( (now->tm_mon + 1) ) + '-' +
      to_string(  now->tm_mday) + '-' +
      to_string(  now->tm_hour) + '-' +
      to_string(  now->tm_min);

  ct = "-" + ct;
  return ct;
}

int 
main(int argc, char *argv[]) {
  po::options_description desc("Allowed options");

  desc.add_options()
      ("help,h", "produce help message")
      ("input-log,l", po::value< string >(), "input log: log path")
      ("input-buf,b", po::value< string >(), "input buf: file path") 
      ("output-drec,o", po::value< string >(), "output file: drec path")
      ("dump-result,d", po::value< bool >(), "dump result: yes/no, 1/0")
      ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);


  if(vm.count("input-log") 
  	 && vm.count("input-buf") 
     && vm.count("dump-result") 
     && vm.count("output-drec") ){

    string lp = vm["input-log"].as< string >();
    // cout << "Input Log: \t" << lp << endl;

	  string bp = vm["input-buf"].as< string >();
    // cout << "Input buf: \t" << bp << endl;

    string od = vm["output-drec"].as< string >();
    // cout << "Output Drec: \t" << od << endl;

    bool is_dump = vm["dump-result"].as< bool >();
    // cout << "Is Dump: \t" << is_dump << endl;

    string ct = get_time();


	DetectAvalanche da(lp, bp, od, is_dump, ct);
	da.detect();

  } else{
    cout << desc << endl;
    return 1;
  }

  return 0;
}