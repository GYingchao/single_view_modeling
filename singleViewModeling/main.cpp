#include "singleviewmodeling.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	singleViewModeling w;
	w.show();
	return a.exec();
}
