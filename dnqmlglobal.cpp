#include "dnqmlglobal.h"
#include "gpbcore.h"
#include "QDebug"

DNQmlGlobal::DNQmlGlobal(QObject *parent, GPBCore* core)
    : QObject{parent},
      _core(core),
      _programName(QString("DeNovo Viewer"))
{

    _networkManager = core->networkManager();
    _boatManager = core->boatManager();

}
