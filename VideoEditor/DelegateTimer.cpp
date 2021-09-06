#include "DelegateTimer.h"

void DelegateTimer::timerEvent(QTimerEvent* event)
{
	if (_delegate) {
		_delegate();
	}
}