#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent = nullptr);

protected:
    // Called whenever an update occurs, used to update clocks time
    void paintEvent(QPaintEvent *event) override;

signals:


};

#endif // ANALOGCLOCK_H
