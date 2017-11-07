#ifndef XT_RECORD_H
#define XT_RECORD_H

#include <string>
#include "xt_node.h"

class XTRecord
{
public:
	// XTRecord();
	XTRecord(std::string &record, unsigned int index);

	bool isMark();
	unsigned int getIndex();

	XTNode getSourceNode();
	XTNode getDestinationNode();

	std::string get_str_rec();

private:
	bool m_isMark;
	unsigned int m_index = 0;

	XTNode m_sourceNode;
	XTNode m_destinationNode;
};

#endif