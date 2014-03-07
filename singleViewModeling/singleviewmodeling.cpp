#include "singleviewmodeling.h"

singleViewModeling::singleViewModeling(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

singleViewModeling::~singleViewModeling()
{

}

void singleViewModeling::on_actionLoadImage_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Load Image", ".", "BMP files(*.bmp)");
	if(filename != NULL) {
		cv::Mat img = cv::imread(filename.toAscii().data());
		cv::cvtColor(img, img, CV_BGR2RGB);
		//QImage qimg = QImage((const unsigned char*)(img.data), img.cols, img.rows, QImage::Format_RGB32);
		ui.imageWidget->loadImage(img); 
		
		// Adaptive widget size
		ui.imageWidget->resize(img.cols, img.rows);
		ui.imageWidget->repaint();
	}
}