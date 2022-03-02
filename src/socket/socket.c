
#if defined(_WIN64) || defined(_WIN32) 
	#include "windows/lookup.i"
	#include "windows/socket.i"
#else
	#error No socket implementation for this platform 
#endif