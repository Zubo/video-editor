#include <PLL/DelegateTimer.hpp>

void DelegateTimer::timerEvent(QTimerEvent*)
{
	if (_delegate) {
		_delegate();
	}

    emit timerEventProcessingCompleted();
}
