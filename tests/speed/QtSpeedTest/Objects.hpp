#include <QtCore/QObject>

class Sender : public QObject
{
	Q_OBJECT
public:
	Sender(QObject * parent = 0) : QObject(parent) {}

	void fire(float x) { testSignal(x); }
signals:
	void testSignal(float x);
	bool boolSign();
};

class Reciever : public QObject
{
	Q_OBJECT
public:
	Reciever(QObject * parent = 0) : QObject(parent) {}
public slots:
	void processFloat(float) {}
};