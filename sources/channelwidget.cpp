#include "channelwidget.h"
#include "ui_channelwidget.h"

#include <QDebug>

#include "oscillowidget.h"
#include "cursor.h"
#include "channel.h"

ChannelWidget::ChannelWidget(Channel *channel, QWidget *parent) :
    QWidget(parent), ui(new Ui::ChannelWidget), m_channel(channel){
    ui->setupUi(this);
    ui->mathWidget->setVisible(false);
    connect(ui->resDial,SIGNAL(resChanged(int)),m_channel,SLOT(setRes(int)));
    connect(ui->channelGroupBox,SIGNAL(toggled(bool)),m_channel,SLOT(setVisible(bool)));
    connect(ui->colorWidget,SIGNAL(colorSelectionChanged(QColor)),this,SLOT(updateColor(QColor)));
    connect(ui->channelComboBox,SIGNAL(currentIndexChanged(int)),m_channel,SLOT(onChannelCoulpingChanged(int)));
    connect(ui->invertCheckBox,SIGNAL(toggled(bool)), m_channel,SLOT(setInverted(bool)));
    connect(ui->XSlider,SIGNAL(valueChanged(int)),m_channel,SLOT(setDX(int)));
    connect(ui->YSlider,SIGNAL(valueChanged(int)),m_channel,SLOT(setDY(int)));
    ui->colorWidget->setColor(m_channel->color());
}

ChannelWidget::~ChannelWidget(){
    delete ui;
}

void ChannelWidget::setChecked(bool checked){
    ui->channelGroupBox->setChecked(checked);
}

void ChannelWidget::setMathMode(bool mathMode){
    ui->waveLabel->setVisible(!mathMode);
    ui->listWidget->setVisible(!mathMode);
    ui->channelComboBox->setVisible(!mathMode);
    ui->mathWidget->setVisible(mathMode);
}

int ChannelWidget::currentRes(){
    return ui->resDial->currentRes();
}

void ChannelWidget::updateColor(QColor color){
    ui->resDial->setColor(color);
    m_channel->updateColor(color);
}
