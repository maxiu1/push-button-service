#include "eventtime.h"
#include <stdio.h>

EventTime::EventTime()
{
	seconds = 0;
	micros = 0;
	sign = +1;
}

EventTime::EventTime(long int seconds, long int micros)
{
	this->seconds = seconds;
	this->micros = micros;
	this->sign = +1;

	normalize();
}

EventTime EventTime::operator+(EventTime rhs)
{
	EventTime ret;

	EventTime l = *this;
	EventTime r = rhs;

	l = l.normalize();
	r = r.normalize();

	if(l.isPositive() && r.isNegative()){
		return l - (-r); // true subtraction
	}

	if(l.isNegative() && r.isPositive()){
		return -(-l - r); // true subtraction
	}

	if(l.isNegative() && r.isNegative()){
		return -(-l + (-r));
	}

	// l and r are now positive

	long int carry = 0;

	ret.micros = l.micros + r.micros;
	if(ret.micros >= 1e6){
		ret.micros -= 1e6;
		carry = 1;
	}

	ret.seconds = l.seconds + r.seconds + carry;

	return ret;
}

EventTime EventTime::operator-(EventTime rhs)
{
	EventTime ret;

	EventTime l = *this;
	EventTime r = rhs;

	l = l.normalize();
	r = r.normalize();

	if(l.isNegative() && r.isPositive()){
		return -(-l + r); // true addition 2
	}

	if(l.isPositive() && r.isNegative()){
		return l + (-r); // true addition 1
	}

	if( l.isNegative() && r.isNegative()){
		return (-r) - (-l);
	}

	// l and r are positive now!

	if(r > l){
		return -(r-l);
	}

	// l and r are positive now, and l is greater or equal to r

	long int carry = 0;

	ret.micros = l.micros - r.micros;
	if(ret.micros < 0){
		ret.micros += 1e6;
		carry = 1;
	}

	ret.seconds = l.seconds - r.seconds - carry;

	return ret;
}

EventTime EventTime::operator-()
{
	EventTime ret = *this;
	ret.sign *= (-1);

	return ret;
}

EventTime EventTime::abs()
{
	EventTime ret = *this;
	if(sign == -1){
		ret.seconds *= -1;
		ret.sign = +1;
	}
	return ret;
}

bool EventTime::operator<(EventTime rhs)
{
	if(seconds < rhs.seconds){
		return true;
	}else if(seconds > rhs.seconds){
		return false;
	}else if((seconds > 0 && micros < rhs.micros) ||
			 (seconds < 0 && micros > rhs.micros)){
		return true;
	}else{
		return false;
	}
}

bool EventTime::isNegative()
{
	normalize();

	if(sign == -1){
		return true;
	}

	return false;
}

bool EventTime::operator>(EventTime rhs)
{
	if(seconds > rhs.seconds){
		return true;
	}else if(seconds < rhs.seconds){
		return false;
	}else if((seconds > 0 && micros > rhs.micros) ||
			 (seconds < 0 && micros < rhs.micros)){
		return true;
	}else{
		return false;
	}
}

bool EventTime::isPositive()
{
	if(sign == +1){
		return true;
	}else{
		return false;
	}
}

bool EventTime::operator==(EventTime rhs)
{
	if(seconds == rhs.seconds &&
			micros == rhs.micros){
		return true;
	}
	return false;
}

bool EventTime::operator>=(EventTime rhs)
{
	return operator> (rhs) || operator== (rhs);
}

bool EventTime::operator<=(EventTime rhs)
{
	return operator< (rhs) || operator== (rhs);
}

void EventTime::print()
{
	normalize();

	if(sign == -1){
		printf("-");
	}
	printf("%ld.%06ld", seconds, micros);
}

void EventTime::println()
{
	print();
	printf("\n");
}

void EventTime::test()
{
	EventTime(1,0).println();
	EventTime(2,0).println();

	(EventTime(1,0) - EventTime(2,0)).println();
	(EventTime(2,0) - EventTime(1,0)).println();

	(EventTime(1,8e5) - EventTime(2,2e5)).println();
	EventTime(0, -8e5).println();
	EventTime(0,-8e5).abs().println();

	(EventTime(0,-8e5) - EventTime(2,2e5)).println();
	(EventTime(-1,-8e5) - EventTime(2,2e5)).println();
	(EventTime(-1,8e5) - EventTime(2,2e5)).println();
	(EventTime(-2,2e5) - EventTime(1,9e5)).println();
	(EventTime(-2,2e5) + EventTime(1,9e5)).println();
	(EventTime(+2,2e5) + EventTime(1,9e5)).println();
}

EventTime EventTime::normalize()
{
	if(seconds < 0 || micros < 0){
		sign = -1;
	}

	if(seconds < 0){
		seconds *= -1;
	}
	if(micros < 0){
		micros *= -1;
	}

	return *this;
}

