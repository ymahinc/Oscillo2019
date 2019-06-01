#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    void setAntiAliasing(bool antiAliasing);
    bool antiAliasing();
    void setInterpolation(int interpolation);
    int interpolation();
    void setAxesVisibles(bool visible);
    bool axesVisibles();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
