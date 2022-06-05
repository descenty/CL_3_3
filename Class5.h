#ifndef __CL5_H__
#define __CL5_H__
#include "TreeObject.h"

class Class5 : public TreeObject
{
public:
	using TreeObject::TreeObject;
	void Signal_5(string& message)
	{
		message += " (class: 5)";
	}
	void Handler_5(string message)
	{
		cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message;
	}
};

#endif