#ifndef SINGLEVIEWMODELING_H
#define SINGLEVIEWMODELING_H

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include "ui_singleviewmodeling.h"
#include "imageDisplayer.h"

class singleViewModeling : public QMainWindow
{
	Q_OBJECT

public:
	singleViewModeling(QWidget *parent = 0, Qt::WFlags flags = 0);
	~singleViewModeling();

private:
	Ui::singleViewModelingClass ui;

public slots:
	void on_actionLoadImage_triggered();
};

#endif // SINGLEVIEWMODELING_H
