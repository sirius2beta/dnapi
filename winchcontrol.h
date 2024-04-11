#ifndef WINCHCONTROL_H
#define WINCHCONTROL_H

#include <QObject>

#include "dncontrol.h"

class WinchControl : public DNControl
{
    Q_OBJECT
public:
    explicit WinchControl(QObject *parent = nullptr, int controType = -1);

signals:

};

#endif // WINCHCONTROL_H
