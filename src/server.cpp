#include <enet/enet.h>
#include <print>

int main ()
{
	if (enet_initialize() != 0)
	{
		std::print("{0}: {1}\n", "[ERROR]", "Failed to initialize enet.");
		return -1;
	}

	std::print("Success!\n");

	return 0;
}