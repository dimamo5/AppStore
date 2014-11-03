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
#include <sstream>
#include <vector>
#include <ctime>
#include <cmath>
#include "time.h"

using namespace std;

class Date {


unsigned int minute;
unsigned int hour;
unsigned int day;
unsigned int month;
unsigned int year;

public:

	Date();
	Date(struct tm* time_struct );
	Date(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute);
	unsigned int getMinute() const;
	unsigned int getHour() const;
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	string imprimeData() const;
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
	tm make_tm(int year, int month, int day);
	double daysBetweenDates(int year1, int month1, int day1,int year2, int month2, int day2);

	//time_t t = time(0);
	//struct tm *now = localtime(&t);
};

#endif /* DATE_H_ */
