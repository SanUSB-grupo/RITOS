/* 
  Ritos.cpp - esp8266 RTOS library of the esp8266 core for Arduino IDE
  based on Ticker library of Ivan Grokhotkov  
 */
 
 

#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "c_types.h"
#include "eagle_soc.h"
#include "ets_sys.h"
#include "osapi.h"
}

#include "ritos.h"

Ritos::Ritos()
: _timer(0)
{
}

Ritos::~Ritos()
{
	detach();
}

void Ritos::_attach_ms(uint32_t milliseconds, bool repeat, callback_with_arg_t callback, uint32_t arg)
{
	if (_timer)
	{
		os_timer_disarm(_timer);
	}
	else
	{
		_timer = new ETSTimer;
	}

	os_timer_setfn(_timer, reinterpret_cast<ETSTimerFunc*>(callback), reinterpret_cast<void*>(arg));
	os_timer_arm(_timer, milliseconds, true);
}

void Ritos::detach()
{
	if (!_timer)
		return;

	os_timer_disarm(_timer);
	delete _timer;
	_timer = 0;
}
