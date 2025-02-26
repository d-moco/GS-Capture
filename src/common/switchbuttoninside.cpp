#include "switchbuttoninside.h"
#include <QPainter>
#include <QFont>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QDebug>

SwitchButtonInside::SwitchButtonInside(QWidget *parent) :
    QWidget(parent)
{
    resize(72, 28); // 默认80，28宽高
    m_pSlider = new Slider(this);
    m_pSlider->resize(height() - m_nMargin * 2, height() - m_nMargin * 2);
    m_pSlider->move(m_nMargin, m_nMargin);
    m_bActive = false; // 默认未激活
    m_nArcRadius = std::min(width(), height()); // 默认半径
    m_nRectWidth = width() - m_nArcRadius;
    //m_colorActive = qRgb(60, 189, 136);64
    m_colorActive = qRgb(0, 255, 204);
    //m_colorInactive = qRgb(167, 177, 188);
    m_colorInactive = qRgb(64, 64, 64);
}

SwitchButtonInside::~SwitchButtonInside()
{
}

void SwitchButtonInside::SetSize(int nWidth, int nHeight)
{
    resize(nWidth, nHeight);
    m_pSlider->resize(height() - m_nMargin * 2, height() - m_nMargin * 2);
    m_pSlider->move(m_nMargin, m_nMargin);
    m_nArcRadius = std::min(width(), height());
    m_nRectWidth = width() - m_nArcRadius;
}

void SwitchButtonInside::SetActiveColor(const QColor& color)
{
    m_colorActive = color;
}

void SwitchButtonInside::SetInactiveColor(const QColor& color)
{
    m_colorInactive = color;
}

void SwitchButtonInside::SetSliderColor(const QColor& color)
{
    m_pSlider->SetSliderColor(color);
}

void SwitchButtonInside::SetStatus(bool bActive)
{
    if(m_bActive == bActive) {
        return;
    }
    m_bActive = bActive;
    if(m_bActive) {
        ToActive();
    } else {
        ToInactive();
    }
}

bool SwitchButtonInside::GetStatus() const
{
    return m_bActive;
}

void SwitchButtonInside::SetText(const QString &text)
{
    m_text = text;
}

void SwitchButtonInside::paintEvent(QPaintEvent *)
{
//    qDebug() << "[SwitchButtonInside]m_nArcRadius = " << m_nArcRadius
//             << "| m_nRectWidth << " << m_nRectWidth
//             << "| size = " << width() << "," << height();

    if (m_nArcRadius > height()) {
        //qDebug() << "******* switchbutton resize ******";
        SetSize(width(), height());
    }

    QPainter p;
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(Qt::NoPen);
    if(m_bActive) p.setBrush(QBrush(m_colorActive));
    else p.setBrush(QBrush(m_colorInactive));

    QPainterPath leftPath;
    //leftPath.addEllipse(0, 0, m_nArcRadius, m_nArcRadius);
    leftPath.addRect(0, 0, m_nArcRadius, m_nArcRadius);

    QPainterPath middlePath;
    middlePath.addRect(m_nArcRadius / 2, 0, m_nRectWidth, m_nArcRadius);

    QPainterPath rightPath;
    //rightPath.addEllipse(m_nRectWidth, 0, m_nArcRadius, m_nArcRadius);
    rightPath.addRect(m_nRectWidth, 0, m_nArcRadius, m_nArcRadius);

    QPainterPath path = leftPath + middlePath + rightPath;

    p.drawPath(path);

    QPen pen;
    QFont ft;
    ft.setPointSize(9);
    p.setFont(ft);
    if (m_bActive) {
        pen.setColor(Qt::black);
         p.setPen(pen);
        p.drawText(QRect(0, 0, m_nRectWidth,
                         m_nArcRadius), Qt::AlignCenter, m_text);
    } else {
        pen.setColor(Qt::white);
        p.setPen(pen);
        p.drawText(QRect(m_nArcRadius, 0,
                         m_nRectWidth, m_nArcRadius), Qt::AlignCenter, m_text);
    }


    p.end();
}

void SwitchButtonInside::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void SwitchButtonInside::mouseReleaseEvent(QMouseEvent *event)
{
    emit Clicked(!m_bActive);
    QWidget::mouseReleaseEvent(event);
}

void SwitchButtonInside::ToActive()
{
    QPropertyAnimation* pAnimation = new QPropertyAnimation(m_pSlider, "geometry");
    pAnimation->setDuration(m_nDuration);
    pAnimation->setStartValue(m_pSlider->rect());
    pAnimation->setEndValue(QRect(width() - m_pSlider->width() - m_nMargin,
                                  m_nMargin,
                                  m_pSlider->width(),
                                  m_pSlider->height()));
    connect(pAnimation, &QPropertyAnimation::valueChanged, this, [&](const QVariant &value){
        Q_UNUSED(value)
        update();
    });
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SwitchButtonInside::ToInactive()
{
    QPropertyAnimation* pAnimation = new QPropertyAnimation(m_pSlider, "geometry");
    pAnimation->setDuration(m_nDuration);
    pAnimation->setStartValue(QRect(m_pSlider->x(),
                                    m_pSlider->y(),
                                    m_pSlider->width(),
                                    m_pSlider->height()));
    pAnimation->setEndValue(QRect(m_nMargin,
                                  m_nMargin,
                                  m_pSlider->width(),
                                  m_pSlider->height()));
    connect(pAnimation, &QPropertyAnimation::valueChanged, this, [&](const QVariant &value){
        Q_UNUSED(value)
        update();
    });
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}


///
/// Slider  滑块类  //
//

Slider::Slider(QWidget *parent) : QWidget(parent)
{
    m_sliderColor = Qt::white;
    resize(56, 56);
}

Slider::~Slider()
{

}

void Slider::SetSliderColor(const QColor &color)
{
    m_sliderColor = color;
    update();
}

void Slider::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    p.fillRect(rect(), Qt::transparent);
    p.setBrush(m_sliderColor);
    p.setPen(Qt::NoPen);
    QRect newRect(rect().x() + 4, rect().y() + 4, rect().width() - 8, rect().height() - 8);
    p.drawRect(newRect);
    QWidget::paintEvent(e);
}
