#ifndef __TREEAPPLICATION_H__
#define __TREEAPPLICATION_H__

#include "TreeObject.h"
class TreeApplication : public TreeObject
{
private:
	void SetObjectsStates();
	void CommandLoop();
	void ConnectionLoop();
	void ConnectTreeObjects(TreeObject* from, TreeObject* to);
	void DisconnectTreeObjects(TreeObject* from, TreeObject* to);
	void SignalLoop();
	TYPE_SIGNAL GetSignal(TreeObject* target);
	TYPE_HANDLER GetHandler(TreeObject* target);
public:
	TreeApplication(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 1; };
	string BuildTree();
	int Exec(bool error);
	void Signal_1(string& message);
	void Handler_1(string message);
};

#endif