#pragma once

#include "qmainwindow.h"
#include "ui_BabelMainWindow.h"

class BabelMainWindow : public QMainWindow {

	// ctor - dtor
	public:
		BabelMainWindow(void);
		~BabelMainWindow(void);

	// coplien form
	private:
		BabelMainWindow(const BabelMainWindow &) {}
		const BabelMainWindow &operator=(const BabelMainWindow &) { return *this; }

	// attributes
	private:
		Ui::BabelMainWindow	ui;

};
