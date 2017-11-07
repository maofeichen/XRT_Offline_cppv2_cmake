#include "xt_flag.h"
#include "xt_record.h"
#include "xt_util.h"

using namespace std;

// XTRecord::XTRecord(){}
XTRecord::XTRecord(std::string &record, unsigned int index)
{
	m_index = index;
	vector<string> v_record = XT_Util::split(record.c_str(), '\t');

	string flag = v_record[0];
	m_isMark = XT_Util::isMarkRecord(flag );

	if(isMark() ){
		m_sourceNode = XTNode(v_record, true, m_index);
		// m_sourceNode = XTNode(v_record, true);
	} else{
		vector<string>::iterator first;
		vector<string>::iterator last;

		first = v_record.begin();
		last  = v_record.begin() + 3;
		vector<string> v_source(first, last);

		first = v_record.begin() + 3;
		last  = v_record.end() - 1;
		vector<string> v_destination(first, last);

		string size;
		if(XT_Util::equal_mark(flag, flag::TCG_QEMU_LD) ){
			size = v_record[6];
			v_source.push_back(size);
		}else if(XT_Util::equal_mark(flag, flag::TCG_QEMU_ST) ){
			size = v_record[6];
			v_destination.push_back(size);
		}

		m_sourceNode 		= XTNode(v_source, true, m_index);
		m_destinationNode 	= XTNode(v_destination, false, m_index);

		// m_sourceNode = XTNode(v_source, true);
		// m_destinationNode = XTNode(v_destination, false);
	}
}

bool XTRecord::isMark() {return m_isMark; }

unsigned int XTRecord::XTRecord::getIndex() {return m_index; }

XTNode XTRecord::getSourceNode() {return m_sourceNode; }

XTNode XTRecord::getDestinationNode() {return m_destinationNode; }

std::string 
XTRecord::get_str_rec() 
{
	if(m_isMark) {
		string s_index = to_string(m_index);
		string flag = m_sourceNode.getFlag();
		string addr = m_sourceNode.getAddr();
		string val  = m_sourceNode.getVal();

		return flag + '\t' + addr + '\t' + val + '\t' + s_index;

	} else {
		string flag = m_sourceNode.getFlag();

		if(XT_Util::equal_mark(flag, flag::TCG_QEMU_LD) ) {
			uint32_t bit_sz = m_sourceNode.getBitSize();
			string s_bit_sz = to_string(bit_sz);

			string s_index = to_string(m_index);

			string saddr = m_sourceNode.getAddr();
			string sval  = m_sourceNode.getVal();

			string daddr = m_destinationNode.getAddr();
			string dval  = m_destinationNode.getVal();

			return flag + '\t' + saddr + '\t' + sval + '\t' + flag + '\t' + daddr + '\t' + dval + '\t' + s_bit_sz + '\t' + s_index;
		} else if(XT_Util::equal_mark(flag, flag::TCG_QEMU_ST) ) {
			uint32_t bit_sz = m_destinationNode.getBitSize();
			string s_bit_sz = to_string(bit_sz);

			string s_index = to_string(m_index);

			string saddr = m_sourceNode.getAddr();
			string sval  = m_sourceNode.getVal();

			string daddr = m_destinationNode.getAddr();
			string dval  = m_destinationNode.getVal();

			return flag + '\t' + saddr + '\t' + sval + '\t' + flag + '\t' + daddr + '\t' + dval + '\t' + s_bit_sz + '\t' + s_index;
		} else {
			string s_index = to_string(m_index);

			string saddr = m_sourceNode.getAddr();
			string sval  = m_sourceNode.getVal();

			string daddr = m_destinationNode.getAddr();
			string dval  = m_destinationNode.getVal();

			return flag + '\t' + saddr + '\t' + sval + '\t' + flag + '\t' + daddr + '\t' + dval + '\t' + s_index;
		}

	}
}
