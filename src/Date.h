/*
 * Date.h
 *
 *  Created on: 18/10/2014
 *      Author: Casa
 */
#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Date {

unsigned int minute;
unsigned int hour;
unsigned int day;
unsigned int month;
unsigned int year;

public:

/**
 *
 * @return returns the current minute
 */
	Date(unsigned int year=1980, unsigned int month=1, unsigned int day=1, unsigned int hour=0, unsigned int minute=0);
	unsigned int getMinute() const;
	unsigned int getHour() const;
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	bool setMinute(unsigned int minute);
	bool setHour(unsigned int hour);
	bool setDay(unsigned int day);
	bool setMonth(unsigned int month);
	bool setYear(unsigned int year);
	bool operator< (const Date&) const;
	bool operator> (const Date&) const;
	bool operator==(const Date&) const;
	bool operator<= (const Date&) const;
	bool operator>= (const Date&) const;

};

#endif /* DATE_H_ */
