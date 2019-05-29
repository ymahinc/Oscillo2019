#ifndef __WIDGETCOLORPICKER_H_
#define __WIDGETCOLORPICKER_H_

#include <QWidget>
#include <QColor>
#include "ui_WidgetColorPicker.h"

class WidgetColorPicker : public QWidget, public Ui::WidgetColorPicker
{
    Q_OBJECT
    
    public: //Methods
        WidgetColorPicker(QWidget *parent = 0);
        ~WidgetColorPicker();

        void setColor(QColor color);
        QColor getColor();

    private: //Methods
        void init();
        QIcon createIcon(QString colorName);
        void addColor(QColor color);

    private: //Data Members
        QColor m_Color;

    private slots: //Slots
        void on_comboBox_currentIndexChanged(int index);

    signals: //Signal
        void colorSelectionChanged(QColor);
};

#endif /*__WIDGETCOLORPICKER_H_*/
