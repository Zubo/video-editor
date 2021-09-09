#include <PLL/DelegateTimer.hpp>

void DelegateTimer::timerEvent(QTimerEvent* event)
{
	if (_delegate) {
		_delegate();
	}

    emit timerEventProcessingCompleted();
}
