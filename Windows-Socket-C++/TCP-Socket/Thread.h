/*********************************************************************
	Date: 06/13/2014
	Author: Khanh Nguyen

	File: Thread.h
	Name: Kronos Thread Class
	Purpose: Provide a wrapper for C++11 thread class so that it would
	be easy to use thread (Java-like thread), implemented IRunnable
**********************************************************************/

#ifndef _KRONOS_THREAD_H_
#define _KRONOS_THREAD_H_

#include "IRunnable.h"
namespace Kronos
{
	class Thread : public IRunnable
	{
	public:
		Thread();
		virtual ~Thread();

	protected:

	private:
		unsigned m_ThreadID;
		void* _func;
	};
}

#endif