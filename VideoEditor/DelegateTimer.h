#ifndef DELEGATETIMER_H
#define DELEGATETIMER_H

#include <functional>
#include <utility>

#include <QObject>
#include <QTimer>

class DelegateTimer : public QObject
{
    Q_OBJECT

public:
	template <typename T>
    DelegateTimer(int const interval, T&& delegate) :
        QObject(0),
        _delegate(std::forward<T>(delegate))
    {
        startTimer(interval);
    }

protected:
	void timerEvent(QTimerEvent* event) override;

private:
    std::function<void(void)> _delegate;

};

#endif // DELEGATETIMER_H
