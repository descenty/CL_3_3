#include "TreeApplication.h"

int main()
{
	TreeApplication* treeApplication = new TreeApplication(nullptr, "");
	string errorString = treeApplication->BuildTree();
	if (errorString != "")
	{
		treeApplication->Exec(true);
		cout << endl << "The head object " << errorString << " is not found";
		return 1;
	}
	return treeApplication->Exec(false);
}