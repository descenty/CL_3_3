#ifndef __CL2_H__
#define __CL2_H__
#include "TreeObject.h"

class Class2 : public TreeObject
{
public:
	Class2(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 2; };
	void Signal_2(string& message) { message += " (class: " + std::to_string(classNum) + ")"; }
	void Handler_2(string message) { cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message; }
};

#endif