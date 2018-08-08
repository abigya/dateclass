#include "date.h"
#include <QTextStream>
QTextStream cout(stdout);
QTextStream cin(stdin);

int main(int argc, char *argv[]){
  Date* d = new Date(2018,3,11);
  //print current date
  cout<<d->toString(true)<<endl;
  //print day of the week
  cout<<d->getWeekDay()<<endl;
  //check if d is equal to d1
  cout<<d->equals(Date(2019,3,11))<<endl;
  //check if d islessthn d1
  cout<<d->lessThan(Date(2016,3,11))<<endl;

  //add 10 days to current date
  d->addDays(10);
  cout<<d->toString(true)<<endl;
  cout<<d->getWeekDay()<<endl;

  //set d to current date
  d->setToToday();
  cout<<d->toString(true)<<endl;


  return 0;
}

