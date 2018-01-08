#ifndef EVENTTIME_H
#define EVENTTIME_H

#include <stdint.h>

class EventTime
{
public:
	EventTime();
	EventTime(long int seconds, long int micros);
	void set(long int seconds, long int micros);


	EventTime operator+ (EventTime rhs);
	EventTime operator- (EventTime rhs);
	EventTime operator- (); // unary minus
	EventTime abs();

	bool operator< (EventTime rhs);
	bool isNegative();
	bool operator> (EventTime rhs);
	bool isPositive();
	bool operator== (EventTime rhs);
	bool operator>= (EventTime rhs);
	bool operator<= (EventTime rhs);

	void print();
	void println();

	static void test();

	long int seconds; // per definition, allways positive!
	long int micros; // per definition, allways positive!
	long int sign; // +1 or -1, needed for -0.xxxx

private:
	EventTime normalize();
};

#endif // EVENTTIME_H
