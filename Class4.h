#ifndef __CL4_H__
#define __CL4_H__
#include "TreeObject.h"

class Class4 : public TreeObject
{
public:
	Class4(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 4; };
	void Signal_4(string& message) { message += " (class: " + std::to_string(classNum) + ")"; }
	void Handler_4(string message) { cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message; }
};

#endif