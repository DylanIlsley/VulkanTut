#include "analogclock.h"

#include <QPainter>
#include <QTime>
#include <QTimer>

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);

    setWindowTitle(tr("Analog Clock"));
    resize(200, 200);
}


// called whener the update slot is called
void AnalogClock::paintEvent(QPaintEvent *event)
{
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7,8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColour(127, 0, 127);
    QColor minuteColour(0, 127, 127, 191); //191 +-= opaqueness 75%

    int side = qMin(width(), height());
    QTime time = QTime::currentTime();

    // pass the widget instance to the painter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // Move the painter to the center of the widget
    painter.translate(width()/2, height()/2);
    // Allows us to use x and y coordinates between -100 and 100
    painter.scale(side/200.0, side/200.0);

    // Draw highlighted arc
    painter.setPen(Qt::NoPen);
    // Rotate to start at top
    //painter.rotate(-180 * 16);
    //Setting brush
    QColor BlueArc = QColor(0, 0, 120);
    BlueArc.setAlphaF(0.2);
    painter.setBrush(BlueArc);


    QRectF rectangle(-100.0, -100.0, 200.0, 200.0);
    // +90 to correct the angle to start on the y axis

    int startAngle =(m_StartTime.hour()*m_u16HourAngle + m_StartTime.minute()*m_f16MinuteAngle)*16 - 90*16;
    int spanAngle = ((m_StopTime.hour() - m_StartTime.hour())*m_u16HourAngle + (m_StopTime.minute() - m_StartTime.minute())*m_f16MinuteAngle) *16;
    // Correction to make it go clockwise rather than counter clockwise
    startAngle *= -1;
    spanAngle  *=-1;
    painter.drawPie(rectangle, startAngle, spanAngle) ;


    // Drawing the hour hand
    painter.setPen(Qt::NoPen); // Don't want any outline so we use NoPen
    painter.setBrush(hourColour);
    painter.save();
    painter.rotate(m_u16HourAngle * time.hour() + m_f16MinuteAngle * time.minute());
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    //Drawing hour edges around the clock
    painter.setPen(hourColour);

    for (int i=0; i<24; ++i){
        painter.drawLine(88, 0 ,96, 0);
        // rotate to prepare for the next edge
        painter.rotate(m_u16HourAngle);
    }

    //Draw the minute hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColour);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second()/60.0)); // Not using the normal minute angle since it is 60 minutes around clock for drawing
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    //Draw minute edges around the clock
    // NOTE: Don't draw minute edges for military clock
    /*painter.setPen(minuteColour);
    painter.save();
    for (int j=0; j<60; ++j){
        // Don't draw where the hour edge would be
        if((j%5) != 0 )
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0); // Not using the normal minute angle since it is 60 minutes around clock for drawing
    }
    painter.restore();*/


}

