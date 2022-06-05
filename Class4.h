#ifndef __CL4_H__
#define __CL4_H__
#include "TreeObject.h"

class Class4 : public TreeObject
{
public:
	using TreeObject::TreeObject;
	void Signal_4(string& message)
	{
		message += " (class: 4)";
	}
	void Handler_4(string message)
	{
		cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message;
	}
};

#endif