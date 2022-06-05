#ifndef __CL6_H__
#define __CL6_H__
#include "TreeObject.h"

class Class6 : public TreeObject
{
public:
	Class6(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 6; };
	void Signal_6(string& message) { message += " (class: " + std::to_string(classNum) + ")"; }
	void Handler_6(string message) { cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message; }
};

#endif