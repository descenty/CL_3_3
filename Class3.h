#ifndef __CL3_H__
#define __CL3_H__
#include "TreeObject.h"

class Class3 : public TreeObject
{
public:
	Class3(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 3; };
	void Signal_3(string& message) { message += " (class: " + std::to_string(classNum) + ")"; }
	void Handler_3(string message) { cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message; }
};

#endif