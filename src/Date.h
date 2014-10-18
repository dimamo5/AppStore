/*
 * Date.h
 *
 *  Created on: 18/10/2014
 *      Author: Casa
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;


#ifndef DATE_H_
#define DATE_H_

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
	unsigned int getMinute() const;
	unsigned int getHour() const;
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	bool setMinute();
	bool setHour();
	bool setDay();
	bool setMonth();
	bool setYear();
	bool operator> (const Date&) const;
	bool operator< (const Date&) const;
	bool operator==(const Date&) const;
	bool operator>= (const Date&) const;
	bool operator<= (const Date&) const;


};

#endif /* DATE_H_ */
