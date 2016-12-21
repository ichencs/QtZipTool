#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QMainWindow>
#include "ui_QtZipTool.h"

class QtZipTool : public QMainWindow
{
    Q_OBJECT

public:
    QtZipTool(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtZipToolClass ui;
};
