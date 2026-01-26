#include <enet/enet.h>
#include <print>

int main ()
{
	// Initialize enet
	if (enet_initialize() != 0)
	{
		std::print("{0}: {1}\n", "[ERROR]", "Failed to initialize enet.");
		return 1;
	}

	std::print("...Initialized enet.\n");

	// -------------------------------------------------------------------------
	// Create ENet Server
	// -------------------------------------------------------------------------

	ENetAddress address;
	ENetHost *server;

	// Default local host
	address.host = ENET_HOST_ANY;

	// Specific port 1234
	address.port = 1234;

	// Create server
	server = enet_host_create(
				&address, 	// Address at which clients may connect to host
				32,			// Allow <= 32 clients to connect to this host
				2,			// Allow <= 2 channels used, 0 and 1
				0,			// 0 = unlimited incoming bandwidth
				0			// 0 = unlimited outgoing bandwidth
			);

	// Check for errors in server creation
	if (server == NULL)
	{
		std::print("{0}: {1}\n",
			"[ERROR]",
			"An error occurred while trying to create an ENet server host.");
		return 1;
	}

	std::print("...Created ENet server.\nHost: {0}\nPort: {1}\n",
		address.host,
		address.port
	);


	// Deinitialize enet
	enet_deinitialize();

	return 0;
}