#ifndef __CL6_H__
#define __CL6_H__
#include "TreeObject.h"

class Class6 : public TreeObject
{
public:
	using TreeObject::TreeObject;
	void Signal_6(string& message)
	{
		message += " (class: 6)";
	}
	void Handler_6(string message)
	{
		cout << endl << "Signal to " << GetAbsolutePath() << " Text:  " << message;
	}
};

#endif