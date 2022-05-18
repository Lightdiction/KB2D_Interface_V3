#ifndef GRPORTS_H
#define GRPORTS_H

#include "mainwindow.h"


class GrPorts : MainWindow
{
public:
    GrPorts();
    void resetPorts();
    void updatePortList();
};

#endif // GRPORTS_H
