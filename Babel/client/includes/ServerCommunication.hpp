#pragma once

class ServerCommunication {

	// ctor - dtor
	public:
		ServerCommunication(void);
		~ServerCommunication(void);

	// coplien form
	private:
		ServerCommunication(const ServerCommunication &) {}
		const ServerCommunication &operator=(const ServerCommunication &) { return *this; }

};
