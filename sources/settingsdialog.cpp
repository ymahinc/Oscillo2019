#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog){
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog(){
    delete ui;
}

void SettingsDialog::setAntiAliasing(bool antiAliasing){
    ui->antiAlisaingCheckBox->setChecked(antiAliasing);
}

bool SettingsDialog::antiAliasing(){
    return ui->antiAlisaingCheckBox->isChecked();
}

void SettingsDialog::setInterpolation(int interpolation){
    ui->interpolationComboBox->setCurrentIndex(interpolation);
}

int SettingsDialog::interpolation(){
    return ui->interpolationComboBox->currentIndex();
}
