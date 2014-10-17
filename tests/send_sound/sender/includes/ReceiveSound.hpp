#pragma once

#include <qobject.h>
#include "IClientSocket.hpp"

class ReceiveSound : public QObject {
	Q_OBJECT

	// default ctor-dtor
	public:
		ReceiveSound(void);
		~ReceiveSound(void) {}

	// private coplien form
	private:
		ReceiveSound(const ReceiveSound &) {}
		const ReceiveSound &operator=(const ReceiveSound &) { return *this; }

	// public SLOT
		public :
			void	onThreadStart(void);

	private:
		IClientSocket *client;

};
