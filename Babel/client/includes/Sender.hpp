#pragma once

#include <qobject.h>
#include <qthread.h>
#include "IClientSocket.hpp"
#include "EncodeManager.hpp"
#include "ISoundDevice.hpp"

class Sender : public QThread {

	Q_OBJECT

	// ctor - dtor
	public:
		Sender(void);
		~Sender(void);

	// thread
	private:
		void	run(void);

	// coplien form
	private:
		Sender(const Sender &) : QThread() {}
		const Sender &operator=(const Sender &) { return *this;  }

	// attributes
	private:
		IClientSocket	*mClient;
		ISoundDevice	*mInput;
		EncodeManager	mEncodeManager;

};
