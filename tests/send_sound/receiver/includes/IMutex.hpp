#pragma once

class IMutex {

	// virtual destructor
	public:
		virtual ~IMutex(void) {}

	// virtual pure methods
	public:
		virtual void	lock(void) = 0;
		virtual bool	tryLock(int milliseconds = -1) = 0;
		virtual void	unlock(void) = 0;

};
