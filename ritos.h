/**************************sanusb.org*********************************
  Ritos.cpp - esp8266 RTOS library of the esp8266 core for Arduino IDE
  based on Ticker library of Ivan Grokhotkov  
 ********************************************************************/

#ifndef RITOS_H
#define RITOS_H

#include <stdint.h>
#include <stddef.h>

extern "C" {
	typedef struct _ETSTIMER_ ETSTimer;
}

class Ritos
{
public:
	Ritos();
	~Ritos();
	typedef void (*callback_t)(void);
	typedef void (*callback_with_arg_t)(void*);

	
	void task(callback_t callback)
	{
		_attach_ms(1, true, reinterpret_cast<callback_with_arg_t>(callback), 0);
	}

	
	template<typename TArg>
	void task(uint32_t milliseconds, void (*callback)(TArg), TArg arg)
	{
		static_assert(sizeof(TArg) <= sizeof(uint32_t), "");
		uint32_t arg32 = (uint32_t)arg;
		_attach_ms(milliseconds, true, reinterpret_cast<callback_with_arg_t>(callback), arg32);
	}


		void detach();

	void _attach_ms(uint32_t milliseconds, bool repeat, callback_with_arg_t callback, uint32_t arg);


	ETSTimer* _timer;
};

#endif/
