#include "imageDisplayer.h"
#include<iostream>
using namespace std;
ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent){
	zoomFactor = 0;
	//draw_seed = false;
	//started_scissor = false;
	//origSize = this->size();
	setFocusPolicy(Qt::StrongFocus);
	this->setMouseTracking(true);
}

ImageDisplayer::~ImageDisplayer(){}

void ImageDisplayer::zoomIn()
{
	if(zoomFactor < 5) {
		zoomFactor ++;
		this->resize(this->size()*1.25);
	}
	
	//cout << "Zoom in: " << zoomFactor << endl;
}

void ImageDisplayer::zoomOut()
{
	if(zoomFactor > -5) {
		zoomFactor --;
		this->resize(this->size()*0.8);
	}
	
	//cout << "Zoom out: " << zoomFactor << endl;
}

// img pixel index is from (1, 1) to (cols, rows);
// displayer pixel index is from (0, 0) to (width-1, height-1);
/*
int* ImageDisplayer::img2dis(int i, int j)
{
	int pos[2];
	pos[0] = static_cast<int>((i-1)*this->width()/(qimg.width()-2));
	pos[1] = static_cast<int>((j-1)*this->height()/(qimg.height()-2));
	return pos;
}

int* ImageDisplayer::dis2img(int x, int y)
{
	int pos[2];
	pos[0] = static_cast<int>(x*(qimg.width()-2)/this->width())+1;
	pos[1] = static_cast<int>(y*(qimg.height()-2)/this->height())+1;
	return pos;
}
*/

void ImageDisplayer::loadImage(cv::Mat img)
{
	this->img = img;
	QImage::Format format = QImage::Format_RGB888;
	qimg = QImage((const unsigned char*)img.data, img.cols, img.rows, img.cols*img.channels(), format);
}


void ImageDisplayer::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter widgetPainter;
	widgetPainter.begin(this);
	drawImage(widgetPainter);
	//drawSavedContour(widgetPainter);
	//if(draw_seed) drawSeed(widgetPainter);
	//if(isStarted() && draw_seed) drawPath(widgetPainter, path);
	widgetPainter.end();
}

void ImageDisplayer::drawImage(QPainter &painter)
{
	if(img.data != NULL) {
		//QRectF target(0.0f, 0.0f, this->width()*2*(1+zoomFactor/10.0), this->height()*2*(1+zoomFactor/10.0));
		//cout << painter.device()->width() << endl;
		//cout << painter.device()->height() << endl;
		QRectF source(0.0f, 0.0f, painter.device()->width(), painter.device()->height());
		QRectF target(source);
		//painter.drawImage(target, temImage, source);
		painter.drawImage(source, qimg);
	}
}

/*
void ImageDisplayer::drawSeed(QPainter &painter)
{
	QBrush o = painter.brush();
	painter.setBrush(QColor(255, 0, 0, 255));
	int* tem = img2dis(img_x, img_y);
	painter.drawRect(tem[0]-3, tem[1]-3, 7, 7);
	painter.setBrush(o);
}

void ImageDisplayer::drawPath(QPainter &painter, vector<vec2i>& p)
{
	if(p.empty()) return;
	QPainterPath path;
	int* tem = img2dis(p[0].pos[0], p[0].pos[1]);
	path.moveTo(tem[0], tem[1]);
	for(int i=1; i<p.size(); i++) {
		tem = img2dis(p[i].pos[0], p[i].pos[1]);
		path.lineTo(tem[0], tem[1]);
	}
	//QBrush o = painter.brush();
	//painter.setBrush(QColor(0, 255, 0, 127));
	QPen o = painter.pen();
	QPen pen(Qt::green, 3);
	painter.setPen(pen);
	painter.drawPath(path);
	//painter.setBrush(o);
	painter.setPen(o);
}

void ImageDisplayer::drawSavedContour(QPainter &painter) 
{
	//cout << "seeds size: " << seeds.size() << endl;
	//cout << "paths size: " << paths.size() << endl;
	if(seeds.size() ==  paths.size()) {
		for(int i=0; i<seeds.size(); i++) {
			// draw seed
			QBrush o = painter.brush();
			painter.setBrush(QColor(255, 0, 0, 255));
			int x = seeds[i].pos[0];
			int y = seeds[i].pos[1];
			int* tem = img2dis(x, y);
			painter.drawRect(tem[0]-3, tem[1]-3, 7, 7);
			painter.setBrush(o);

			// draw path
			QPainterPath path;
			vector<vec2i> p = paths[i];
			int* tem2 = img2dis(p[0].pos[0], p[0].pos[1]);
			path.moveTo(tem2[0], tem2[1]);
			for(int j=1; j<p.size(); j++) {
				tem2 = img2dis(p[j].pos[0], p[j].pos[1]);
				path.lineTo(tem2[0], tem2[1]);
			}
			QPen op = painter.pen();
			QPen pen(Qt::green, 3);
			painter.setPen(pen);
			painter.drawPath(path);
			painter.setPen(op);
		}
	}
}
*/
void ImageDisplayer::keyPressEvent(QKeyEvent *event)
{
	if(!isEmpty()) {
		if(event->key() == Qt::Key_I){ 
			zoomIn();
			this->repaint();
		}
		if(event->key() == Qt::Key_O) {
			zoomOut();
			this->repaint();
		}
	}
}
/*
void ImageDisplayer::mouseMoveEvent ( QMouseEvent * event )
{
	if(!isEmpty()) {
		// if image is loaded correctly
		mouse_x = event->x();
		mouse_y = event->y();

		if(started_scissor && draw_seed) {
			// if already started iscissor
			int* t = dis2img(event->x(), event->y());
			int ti = t[0];
			int tj = t[1];
			handler->getPath(ti, tj, path);

			//cout << "Computing new path..." << path.size() << endl;
			repaint();
		}
	} else {
		mouse_x = -1;
		mouse_y = -1;
	}
}

void ImageDisplayer::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton && !isEmpty()) {
		// update progress bar
		mouse_x = event->x();
		mouse_y = event->y();
		//cout << "x: " << event->x() << ", y: " << event->y() << endl;

		// compute the corresponding pixel index of the image
		//cout << qimg.width() << ", " << qimg.height() << endl;
		//cout << this->width() << ", " << this->height() << endl;
		if(started_scissor) {
			//seed_x = event->x();
			//seed_y = event->y();
			//double orig_i = seed_x*(qimg.width()-2)/this->width();
			//double orig_j = seed_y*(qimg.height()-2)/this->height();

			// save contour
			if(draw_seed && (!path.empty())) {
				vec2i s;
				s.pos[0] = img_x;
				s.pos[1] = img_y;
				seeds.push_back(s);
				paths.push_back(path);
				//cout << "Contour saved!" << endl;
			}

			// Update mouse clicked pixel pos
			int* tem = dis2img(mouse_x, mouse_y);
			img_x = tem[0];
			img_y = tem[1];
			//cout << "From displayer: " << tem[0] << ", " << tem[1] << endl;
			
			// set new seed to the image matrix
			handler->setSeed(img_x, img_y);
			// Compute a new tree
			handler->LiveWireDP(img_x, img_y);
			// Paint for test
			draw_seed = true;
		}
		repaint();
	} else if(event->button() == Qt::RightButton && seeds.size()>1) {

		vec2i f_seed = seeds[0];

		// Get the min path from last seed to first seed
		handler->getPath(f_seed.pos[0], f_seed.pos[1], path);
		paths.push_back(path);
		seeds.push_back(f_seed);
		repaint();
		this->Stop();
	}
}

void ImageDisplayer::roll_back()
{
	if(seeds.empty() || paths.empty() || started_scissor == false) return;
	if(seeds.size()==1 || paths.size()==1) {
		draw_seed = false; 
		path.clear(); 
		seeds.clear(); 
		paths.clear();
		this->repaint();
		return;
	}
	
	// withdraw the last record
	vec2i pSeed = seeds.back();
	img_x = pSeed.pos[0];
	img_y = pSeed.pos[1];
	path = paths.back();
	seeds.pop_back();
	paths.pop_back();

	handler->setSeed(img_x, img_y);
	handler->LiveWireDP(img_x, img_y);
	this->repaint();
}
*/