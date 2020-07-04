#include "AmaApp.h"
#include "AmaApp.h" // intentional

int main()
{
	ama::AmaApp theApp("inventory.txt");
	theApp.run();
	return 0;
}
