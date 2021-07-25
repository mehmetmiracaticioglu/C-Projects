/*mehmet mirac aticioglu 
15144020
konsolda fazladan bir gun gozukyor txt yazarken dogru sadece konsolda fazladan 1 gun yazıyor istenileni yapıyor ama.
*/



#include <stdio.h>
#include <stdlib.h>

typedef struct _date{
	int day;
	int month;
	int year;
}Date;

typedef enum {thurday,friday,saturday,sunday,monday,tuesday,wednesday}days;

typedef int bool;
enum{ false, true};


/*protorype*/
bool writeAllDays(Date date1, Date date2);
Date getNextDay(Date current);
Date returnLaterDate(Date date1, Date date2);
bool isDateLater(Date date1, Date date2);
bool writeDateToFile();
bool checkDate(Date date);
bool areDatesEqual(Date date1, Date date2);
void TxtDay(char* txt);
int calculateDay(int day,int month,int year);


/*main*/
int main(){
	printf("Enter a date.\n");
	Date date, date2;
	scanf("%d", &date.day);
	scanf("%d", &date.month);
	scanf("%d", &date.year);
	printf("Enter a date.\n");
	scanf("%d", &date2.day);
	scanf("%d", &date2.month);
	scanf("%d", &date2.year);
	writeAllDays(date, date2);
	printf("Wrote to file.\n");
	TxtDay("input_date.txt");
	return 0;
}

int calculateDay(int day,int month,int year){
	/*arrayde ayin kacar gun cektigine bakiyoz 
	aydaki gunler arasi farklari aliyoz.*/
	int i,m_day;
	int arr[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	for (i = 1; i <month ; ++i)
	{
		m_day+=arr[i-1];
	}

	/* cogu sistem baslangic tarihini 1970 aldigi icin 
	baslangic kabul ettim .*/
	for (i = 1970; i <year ; ++i)
	{
		if (i%4==0)
		{
			m_day++;
		}
	}
	/* leep year olursa gun fark gun sayisine ekleme yapiliyor*/
	if (year%4==0 && month>2)
	{
		m_day++;
	}

	/*aradaki fark bulunur ve yukardaki typedef enum kullanilir */
	return ((day-1 + m_day+ (year-1970)*365)%7);
	
} 

void TxtDay(char* txt){

	FILE *fp = fopen(txt,"r");
	FILE *fw = fopen("new_date.txt","w+");
	char a,b,str[11]; /*a ve b taksim(/) sembollerini alıyor parse ediyor.*/
						/* str[11] ise 01/04/1995 varsayalim buradaki tüm karakteleri icine aliyor*/ 

	int c,d,e;    /*c gun , d ay e yil olarak tanımlanmıstır*/

	while(fgets(str,11,fp))
	{
		sscanf(str,"%d %c %d %c %d",&c,&a,&d,&b,&e);
		switch(calculateDay(c,d,e)){

			/* donen degere bakar ve ona gore gunleri yazar*/

			case 0 : fprintf(fw, "%s", "Thursday, ");break;
			case 1 : fprintf(fw, "%s", "Friday, ");break;
			case 2 : fprintf(fw, "%s", "Saturday, ");break;
			case 3 : fprintf(fw, "%s", "Sunday, ");break;
			case 4 : fprintf(fw, "%s", "Monday, ");break;
			case 5 : fprintf(fw, "%s", "Tuesday, ");break;
			case 6 : fprintf(fw, "%s", "Wednesday, ");break;

		}
		switch(d){

			/* aylari ayni sekilde alir*/	

			case 1 : fprintf(fw, "%s", "January, ");break;
			case 2 : fprintf(fw, "%s", "February, ");break;
			case 3 : fprintf(fw, "%s", "March, ");break;
			case 4 : fprintf(fw, "%s", "April, ");break;
			case 5 : fprintf(fw, "%s", "May, ");break;
			case 6 : fprintf(fw, "%s", "June, ");break;
			case 7 : fprintf(fw, "%s", "July, ");break;
			case 8 : fprintf(fw, "%s", "August, ");break;
			case 9 : fprintf(fw, "%s", "September, ");break;
			case 10 : fprintf(fw, "%s", "October, ");break;
			case 11 : fprintf(fw, "%s", "November, ");break;
			case 12 : fprintf(fw, "%s", "December, ");break;
		}
		fprintf(fw, "%d , %d\n",c,e);

	}



}
bool writeAllDays(Date date1, Date date2){
	FILE *file;
	Date current, startDate, endDate;
	if(checkDate(date1) == false || checkDate(date2) == false)
		return false;
	endDate = returnLaterDate(date1, date2);

	if(areDatesEqual(endDate,date1))
		startDate = date2;
	else
		startDate = date1;
	printf("startDate: %d %d %d\n" , startDate.day, startDate.month, startDate.year);

	current = startDate;
	file = fopen("input_date.txt", "w+");
	printf("current: %d %d %d\n" , current.day, current.month, current.year);
	while(isDateLater(current, endDate) == false){
		fprintf(file, "%d/%d/%d\n", current.day, current.month, current.year);
		current = getNextDay(current);		
		printf("current: %d %d %d\n" , current.day, current.month, current.year);
	}
	fclose(file);
	return true;
}

Date getNextDay(Date current){
	bool leapYear = ((current.year % 4) == 0);
	bool oddMonth = (current.month % 2 == 1); //if true, number of days is 31
	current.day += 1;
	if(current.month == 2){
		if(current.day > (28 + leapYear))
		{
			current.month += current.day / (28 + leapYear);
			current.day = 1;
		}
	}
	else{
		if((oddMonth && current.month <= 7) || (!oddMonth && current.month >= 8)){
			//printf("current day: %d\n", current.day);
			current.month += current.day / 32;
			if(current.day > 31)
				current.day = 1;
		}
		else{
			current.month += current.day / 31;
			if(current.day > 30)
				current.day = 1;
		}

	}
	current.year += current.month / 13;
	if(current.month > 12)
		current.month = 1;
	return current;
}

Date returnLaterDate(Date date1, Date date2){
	if(date1.year < date2.year)
		return date2;
	else if(date1.year > date2.year)
		return date1;

	/*if execution reaches here, years are equal*/
	if(date1.month < date2.month)
		return date2;
	else if(date1.month > date2.month)
		return date1;

	if(date1.day < date2.day)
		return date2;
	else if(date1.day > date2.day)
		return date1;

	/* if execution reaches here, dates are equal */
	return date1;
}

bool isDateLater(Date date1, Date date2){
	if(date1.year < date2.year)
		return false;
	else if(date1.year > date2.year)
		return true;

	/*if execution reaches here, years are equal*/
	if(date1.month < date2.month)
		return false;
	else if(date1.month > date2.month)
		return true;

	if(date1.day < date2.day)
		return false;
	else if(date1.day > date2.day)
		return true;

	/* if execution reaches here, dates are equal */
	return false;
}

bool writeDateToFile(){
	//FILE *fp, char* userInput;
	//fp = fopen("input_date.txt", "w+");
	printf("Enter date: \n");
	return false;
}

bool checkDate(Date date){
	if(date.month == 2)
		if(date.day > 29 || date.day < 1)
			return false;

	if(date.month > 12 || date.month < 0)
		return false;
	if(date.day > 31 || date.day < 0)
		return false;
	return true;
}

bool areDatesEqual(Date date1, Date date2){
	return(date1.day == date2.day && date1.year == date2.year && date1.month == date2.month);
}