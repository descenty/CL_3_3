#ifndef __CL3_H__
#define __CL3_H__
#include "TreeObject.h"

class Class3 : public TreeObject
{
public:
	using TreeObject::TreeObject;
	void Signal_3(string& message)
	{
		message += " (class: 3)";
	}
	void Handler_3(string message)
	{
		cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message;
	}
};

#endif