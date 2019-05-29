#include "WidgetColorPicker.h"
#include <QColorDialog>

WidgetColorPicker::WidgetColorPicker(QWidget *parent)
    : QWidget(parent){
    setupUi(this);
    init();
}

WidgetColorPicker::~WidgetColorPicker(){

}

void WidgetColorPicker::init(){
    comboBox->setMaxCount(21);

    disconnect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_currentIndexChanged(int)));
    comboBox->addItem("...");
    comboBox->addItem(createIcon("#000000"),"",QColor("#000000"));
    comboBox->addItem(createIcon("#FFFFFF"),"",QColor("#FFFFFF"));
    comboBox->addItem(createIcon("#808080"),"",QColor("#808080"));
    comboBox->addItem(createIcon("#800000"),"",QColor("#800000"));
    comboBox->addItem(createIcon("#804040"),"",QColor("#804040"));
    comboBox->addItem(createIcon("#FF8080"),"",QColor("#FF8080"));
    comboBox->addItem(createIcon("#FF0000"),"",QColor("#FF0000"));
    comboBox->addItem(createIcon("#FFFF80"),"",QColor("#FFFF80"));
    comboBox->addItem(createIcon("#FFFF00"),"",QColor("#FFFF00"));
    comboBox->addItem(createIcon("#FF8040"),"",QColor("#FF8040"));
    comboBox->addItem(createIcon("#FF8000"),"",QColor("#FF8000"));
    comboBox->addItem(createIcon("#80FF80"),"",QColor("#80FF80"));
    comboBox->addItem(createIcon("#80FF00"),"",QColor("#80FF00"));
    comboBox->addItem(createIcon("#00FF00"),"",QColor("#00FF00"));
    comboBox->addItem(createIcon("#80FFFF"),"",QColor("#80FFFF"));
    comboBox->addItem(createIcon("#00FFFF"),"",QColor("#00FFFF"));
    comboBox->addItem(createIcon("#004080"),"",QColor("#004080"));
    comboBox->addItem(createIcon("#0000FF"),"",QColor("#0000FF"));
    comboBox->addItem(createIcon("#0080FF"),"",QColor("#0080FF"));
    comboBox->addItem(createIcon("#0080C0"),"",QColor("#0080C0"));

    m_Color = QColor("000000");
    comboBox->setCurrentIndex(1);
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBox_currentIndexChanged(int)));
}

QIcon WidgetColorPicker::createIcon(QString colorName){
    QPixmap iconPixmap(32,32);
    iconPixmap.fill(QColor(colorName));
    QIcon itemIcon(iconPixmap);
    return itemIcon;
}

void WidgetColorPicker::on_comboBox_currentIndexChanged(int index){
    if(index==0){
        m_Color = QColorDialog::getColor(m_Color,this);
        addColor(m_Color);
    }else{
        m_Color = comboBox->itemData(index).value<QColor>();
    }

    emit colorSelectionChanged(m_Color);
}

void WidgetColorPicker::setColor(QColor color){
    if(color.isValid()){
        m_Color = color;
        addColor(color);
    }
}

QColor WidgetColorPicker::getColor(){
    return m_Color;
}

void WidgetColorPicker::addColor(QColor color){
    int index = comboBox->findData(color);
    if(index > -1){
        comboBox->setCurrentIndex(index);
    }else    {
        QString colorName = color.name().toUpper();
        comboBox->insertItem(1,createIcon(colorName),"",color);
        comboBox->setCurrentIndex(1);
    }
}
