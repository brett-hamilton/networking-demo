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

	// -------------------------------------------------------------------------
	// Server Loop
	// -------------------------------------------------------------------------

	ENetEvent event;
	ENetPeer *client;

	// Wait up to 10 milliseconds for an event
	while (enet_host_service(server, &event, 10) > 0)
	{
		// Handle events
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			std::print("A new client connected from {0}:{1}.\n",
				event.peer -> address.host,
				event.peer -> address.port);

			// Store client info here
			client = event.peer;

			break;

		case ENET_EVENT_TYPE_RECEIVE:
			std::print("A packet of length {0} containing {1} was received "
					"from {2} on channel {3}.\n",
                event.packet -> dataLength,
                event.packet -> data,
                event.peer -> data,
                event.channelID);
 
        	// Clean up the packet after using it
        	enet_packet_destroy (event.packet);
        
        	break;

        case ENET_EVENT_TYPE_DISCONNECT:
        	std::print("{0} disconnected.\n", event.peer -> data);
 
        	// Reset the peer's client information
        	event.peer -> data = NULL;

		}
	}

	// Deinitialize enet
	enet_deinitialize();

	return 0;
}