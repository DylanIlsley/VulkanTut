#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QFloat16>
// TODO: Support both military clock and normal
class AnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent = nullptr);

public slots:
    void LightCycleChanged(QTime StartTime, QTime StopTime) {
        m_StartTime = StartTime;
        m_StopTime = StopTime;
        qDebug() << "Light cycle changed to StartTime = " + m_StartTime.toString() + ", StopTime = " + m_StopTime.toString();

    }

protected:
    // Called whenever an update occurs, used to update clocks time
    void paintEvent(QPaintEvent *event) override;


signals:

   // TODO: Add function to draw highlighted part
   // TODO: Only draw the clock edges at construction
   // TODO: Only the hands should be updated at real-time

private:
    const quint16 m_u16HourAngle = 360/24.0; ///< The number of degrees that a single hour represents, using a military clock
    const qfloat16 m_f16MinuteAngle = m_u16HourAngle/60.0; ///< The number of degrees that a single minute represents

    QTime m_CurrentTime;
    QTime m_StartTime; // Defaults to 00:00
    QTime m_StopTime; // Defaults to 00:00
};

#endif // ANALOGCLOCK_H
