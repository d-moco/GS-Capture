#ifndef SwitchButtonInsideINSIDE_H
#define SwitchButtonInsideINSIDE_H

#include <QWidget>

class Slider;

class SwitchButtonInside : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchButtonInside(QWidget *parent = nullptr);
    ~SwitchButtonInside();
    /**
     * @brief SetSize 设置按钮的尺寸
     * @param nWidth 按钮的新宽度
     * @param nHeight 按钮的新高度
     */
    void SetSize(int nWidth, int nHeight);

    /**
     * @brief SetActiveColor 设置按钮激活时候的颜色
     * @param color 激活颜色
     */
    void SetActiveColor(const QColor& color);

    /**
     * @brief SetInactiveColor 设置按钮未激活时候的颜色
     * @param color 未激活颜色
     */
    void SetInactiveColor(const QColor& color);

    /**
     * @brief SetSliderColor 设置滑块颜色
     * @param color 滑块的颜色
     */
    void SetSliderColor(const QColor& color);

    /**
     * @brief SetStatus 设置按钮状态
     * @param bActive true: 激活，false: 未激活
     */
    void SetStatus(bool bActive);

    /**
     * @brief GetStatus 获取按钮当前状态
     * @return  true: 激活，false: 未激活
     */
    bool GetStatus() const;

    /**
     * @brief SetStatus 设置按钮显示文字
     * @param text: 文字内容
     */
    void SetText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void ToActive();
    void ToInactive();

private:
    bool m_bActive; // 是否激活
    int m_nArcRadius; // 圆弧的半径
    int m_nRectWidth; // 矩形的宽度
    const short m_nMargin = 2;
    const int m_nDuration = 100; // 动画时间，单位毫秒
    bool m_bClicked; // 能否被点击。如果动画还没结束，无法进行点击/状态切换
    QColor m_colorActive; // 激活时的颜色
    QColor m_colorInactive;
    Slider* m_pSlider;
    QString m_text; // 显示文字

signals:
    /**
     * @brief Clicked 按钮被点击后发出的信号
     * @param status 当前按钮状态。true为active，false为inactive
     */
    void Clicked(bool status);
};


class Slider : public QWidget
{
    Q_OBJECT
public:
    explicit Slider(QWidget* parent = nullptr);
    ~Slider();

    /**
     * @brief SetSliderColor 设置滑块颜色
     * @param color
     */
    void SetSliderColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent* e) override;

private:
    QColor m_sliderColor;
};

#endif // SwitchButtonInsideINSIDE_H
