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

    // Drawing the hour hand
    painter.setPen(Qt::NoPen); // Don't want any outline so we use NoPen
    painter.setBrush(hourColour);

    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute()/60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    //Drawing hour edges around the clock
    painter.setPen(hourColour);

    for (int i=0; i<12; ++i){
        painter.drawLine(88, 0 ,96, 0);
        // rotate to prepare for the next edge
        painter.rotate(30.0);
    }

    //Draw the minute hand
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColour);

    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second()/60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    //Draw minute edges around the clock
    painter.setPen(minuteColour);
    painter.save();
    for (int j=0; j<60; ++j){
        // Don't draw where the hour edge would be
        if((j%5) != 0 )
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0); // get ready for next edge
    }
    painter.restore();

    // Draw highlighted arc
    painter.setPen(Qt::NoPen);
    // Rotate to start at top
    painter.rotate(-60);
    //Setting brush
    QColor BlueArc = QColor(0, 0, 120);
    BlueArc.setAlphaF(0.2);
    painter.setBrush(BlueArc);


    QRectF rectangle(-100.0, -100.0, 200.0, 200.0);
    int startAngle = -60 *16;
    int spanAngle = -30 * 16;
    painter.drawPie(rectangle, startAngle, spanAngle) ;
}

