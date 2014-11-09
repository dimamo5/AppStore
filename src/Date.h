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

/**
 * @class Date
 * @brief Classe que representa datas
 */
class Date {

	unsigned int minute;
	unsigned int hour;
	unsigned int day;
	unsigned int month;
	unsigned int year;

public:
	/**
	 * Default constructor para a data
	 */
	Date();
	/**
	 * Construtor da data que recebe como argumento uma time struct da library ctime
	 * e inicializa a data a partir dessa struct
	 * @param time_struct struct da data, como se recebe ao criar objetos time, da library ctime
	 */
	Date(struct tm* time_struct);
	/**
	 * Construtor da data que inicializa usando todos os parametros
	 * @param year Ano para inicializar o membro dado year
	 * @param month Mes para inicializar o membro dado month
	 * @param day Dia para inicializar o membro dado day
	 * @param hour Hora para inicializar o membro dado hour
	 * @param minute Minuto para inicializar o membro dado minute
	 */
	Date(unsigned int year, unsigned int month, unsigned int day,
			unsigned int hour, unsigned int minute);
	/**
	 * Getter de minutos da data
	 * @return Retorna o minuto da data
	 */
	unsigned int getMinute() const;
	/**
	 * Getter de horas da data
	 * @return Retorna as horas da data
	 */
	unsigned int getHour() const;
	/**
	 * Getter de dia da data
	 * @return Retorna o dia da data
	 */
	unsigned int getDay() const;
	/**
	 * Getter do mes da data
	 * @return Retorna o mes da data
	 */
	unsigned int getMonth() const;
	/**
	 * Getter do ano da data
	 * @return Retorna o ano da data
	 */
	unsigned int getYear() const;
	/**
	 * Setter do minuto da data
	 * @param minute Minuto a por na data
	 * @return Retorna true se mudou e false se nao
	 */
	bool setMinute(unsigned int minute);
	/**
	 * Setter da hora da data
	 * @param hour Hora a por na data
	 * @return Retorna true se mudou e false se nao
	 */
	bool setHour(unsigned int hour);
	/**
	 * Setter do dia da data
	 * @param day Dia a por na data
	 * @return Retorna true se mudou e false se nao
	 */
	bool setDay(unsigned int day);
	/**
	 * Setter do mes da data
	 * @param month Mes a por na data
	 * @return Retorna true se mudou e false se nao
	 */
	bool setMonth(unsigned int month);
	/**
	 * Setter do ano da data
	 * @param year Ano a por na data
	 * @return Retorna true se mudou e false se nao
	 */
	bool setYear(unsigned int year);
	/**
	 * Cria uma string a partir da data
	 * @return Retorna a string com a data no formato "Dia de Mes de Ano   hh:mm"
	 */
	string imprimeData() const;
	/**
	 * Overload operador < para classe Date
	 * @param data Data com a qual se compara a 1a
	 * @return True se menor que o argumento - False se maior que o argumento
	 */
	bool operator<(const Date& data) const;
	/**
	 *	Overload operador > para classe Date
	 * @param data Data com a qual se compara a 1a
	 * @return True se maior que o argumento - False se menor que o argumento
	 */
	bool operator>(const Date& data) const;
	/**
	 *  Overload operador == para classe Date
	 * @param data Data com a qual se compara a 1a
	 * @return True se igual ao argumento - False se diferente do argumento
	 */
	bool operator==(const Date& data) const;
	/**
	 * Overload operador <= para classe Date
	 * @param data Data com a qual se compara a 1a
	 * @return True se menor ou igual ao argumento - False se maior que o argumento
	 */
	bool operator<=(const Date& data) const;
	/**
	 * Overload operador >= para classe Date
	 * @param data Data com a qual se compara a 1a
	 * @return True se maior ou igual ao argumento - False se menor que o argumento
	 */
	bool operator>=(const Date& data) const;

};

#endif /* DATE_H_ */
