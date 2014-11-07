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
#include <iomanip>
#include "time.h"

using namespace std;

tm make_tm(int year, int month, int day);
double daysBetweenDates(int year1, int month1, int day1, int year2, int month2,
		int day2);

string nomeDoMes(unsigned int month);

class Date {

	unsigned int minute;
	unsigned int hour;
	unsigned int day;
	unsigned int month;
	unsigned int year;

public:

	Date();
	Date(struct tm* time_struct);
	Date(unsigned int year, unsigned int month, unsigned int day,
			unsigned int hour, unsigned int minute);
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

	string imprimeData() const;
	/**
	 * Overload operador < para classe Date
	 * @param data
	 * @return true se menor-false se maior
	 */
	bool operator<(const Date&) const;
	/**
	 *	Overload operador > para classe Date
	 * @param data
	 * @return true se maior-false se menor
	 */
	bool operator>(const Date&) const;
	bool operator==(const Date&) const;
	bool operator<=(const Date&) const;
	bool operator>=(const Date&) const;

};

#endif /* DATE_H_ */
