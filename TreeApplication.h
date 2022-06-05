#ifndef __TREEAPPLICATION_H__
#define __TREEAPPLICATION_H__

#include "TreeObject.h"
class TreeApplication : public TreeObject
{
public:
	TreeApplication(TreeObject* parent, string name) : TreeObject(parent, name) { classNum = 1; };
	string BuildTree();
	void SetObjectsStates();
	void CommandLoop();
	void ConnectionLoop();
	void SignalLoop();
	int Exec(bool error);
	void Signal_1(string& message);
	void ConnectTreeObject(TreeObject* from, TreeObject* to);
	void DisconnectTreeObject(TreeObject* from, TreeObject* to);
	void Handler_1(string message);
	TYPE_SIGNAL GetSignal(TreeObject* target);
	TYPE_HANDLER GetHandler(TreeObject* target);
};

#endif