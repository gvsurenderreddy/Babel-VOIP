#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimpleWindow.h"

class SimpleWindow : public QMainWindow {

	Q_OBJECT

	public:
		SimpleWindow(QWidget *parent = 0);
		~SimpleWindow() {}

	private:
		Ui::SimpleWindowClass ui;

};
