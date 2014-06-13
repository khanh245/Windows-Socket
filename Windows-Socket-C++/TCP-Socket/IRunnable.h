/*********************************************************************
	Date: 06/13/2014
	Author: Khanh Nguyen

	File: IRunnable.h
	Name: Kronos Runnable Class
	Purpose: Provide an interface for Kronos Thread (Runnable in Java)
**********************************************************************/

#ifndef _IKRONOS_RUNNABLE_H_
#define _IKRONOS_RUNNABLE_H_

namespace Kronos
{
	class IRunnable
	{
	public:
		virtual ~IRunnable();

		virtual int Start();
	};
}

#endif