#ifndef TICKET_H
#define TICKET_H
#include"flight.h"
class ticket
{
public:
    flight boughtmess;
    QString ticketnumber;
    QString Class;
    int status;
public:
    ticket();
};

#endif // TICKET_H
