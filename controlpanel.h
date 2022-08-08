#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>

class ControlPanel : public QObject
{
    Q_OBJECT

public:
    ControlPanel(QObject *parent = nullptr);
};

#endif // CONTROLPANEL_H
