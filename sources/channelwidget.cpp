#include "channelwidget.h"
#include "ui_channelwidget.h"

#include <QDebug>

#include "oscillowidget.h"
#include "cursor.h"
#include "channel.h"

ChannelWidget::ChannelWidget(Channel *channel, QWidget *parent) :
    QWidget(parent), ui(new Ui::ChannelWidget), m_channel(channel){
    ui->setupUi(this);
    connect(ui->resDial,SIGNAL(resChanged(int)),m_channel,SLOT(setRes(int)));
    connect(ui->channelGroupBox,SIGNAL(toggled(bool)),m_channel,SLOT(setVisible(bool)));
    connect(ui->colorWidget,SIGNAL(colorSelectionChanged(QColor)),this,SLOT(updateColor(QColor)));
    ui->colorWidget->setColor(m_channel->color());
}

ChannelWidget::~ChannelWidget(){
    delete ui;
}

int ChannelWidget::currentRes(){
    return ui->resDial->currentRes();
}

void ChannelWidget::updateColor(QColor color){
    ui->resDial->setColor(color);
    m_channel->updateColor(color);
}
