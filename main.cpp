#include "TreeApplication.h"

int main()
{
	TreeApplication* treeApplication = new TreeApplication(nullptr, "");
	treeApplication->classNum = 1;
	treeApplication->state = 1;
	string errorString = treeApplication->BuildTree();
	if (errorString != "")
	{
		treeApplication->Exec(true);
		cout << endl << "The head object " << errorString << " is not found";
		return 0;
	}
	return treeApplication->Exec(false);
}