#ifndef __CL2_H__
#define __CL2_H__
#include "TreeObject.h"

class Class2 : public TreeObject
{
public:
	using TreeObject::TreeObject;
	void Signal_2(string& message)
	{
		message += " (class: 2)";
	}
	void Handler_2(string message)
	{
		cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message;
	}
};

#endif