#ifndef __CL5_H__
#define __CL5_H__
#include "TreeObject.h"

class Class5 : public TreeObject
{
public:
	Class5(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 5; };
	void Signal_5(string& message) { message += " (class: " + std::to_string(classNum) + ")"; }
	void Handler_5(string message) { cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message; }
};

#endif