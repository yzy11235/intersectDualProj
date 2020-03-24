#include "IntersectGUI.h"
#include <string>
#include <iostream>
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <QMessageBox>
#include "QDir"
#include "QFileDialog"
#include "QTextStream"
#include "QFile"

//#pragma comment(lib,"calcInterface.lib")
#pragma comment(lib,"DllexprotProj.lib")
_declspec(dllexport)  extern "C"  int guiProcess(std::vector<std::pair<double, double>> * points, std::string msg);

IntersectGUI::IntersectGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void IntersectGUI::paintEvent(QPaintEvent*)
{
	init_canvas();
	if (figures.size() != 0) {
		for (vector<string>::iterator iter = figures.begin(); iter != figures.end(); ++iter) {
			draw_figures_from_str(*iter);
		}
		draw_points();
	}
}

void IntersectGUI::init_canvas()
{
	QPainter painter(this);
	QPen pen;
	pen.setColor(Qt::red);
	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(W_*0.6);
	painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
	painter.setPen(pen);

	painter.setViewport(20, 20, CANVAS_SIZE, CANVAS_SIZE);
	//前面两个参数 左上角坐标  后面两个参数 宽和高
	//painter.setWindow(-MAX_X, MAX_X, 2 * MAX_X, -2 * MAX_X);
	//painter.fillRect(-MAX_X, MAX_X, 2 * MAX_X, -2 * MAX_X, Qt::white);
	painter.setWindow(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X);
	painter.fillRect(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X, Qt::white);

	//绘制坐标轴
	painter.drawLine(0, WINDOW_X, 0, -WINDOW_X);
	painter.drawLine(WINDOW_X, 0, -WINDOW_X, 0);

}

void IntersectGUI::on_findFileButton_clicked()
{
	filePath =
		QDir::toNativeSeparators(QFileDialog::getOpenFileName(this, tr("Save path"), QDir::currentPath()));  //文件路径

	if (!filePath.isEmpty())
	{
		if (ui.fileBox->findText(filePath) == -1)
			ui.fileBox->addItem(filePath);//在comboBox中显示文件路径
	}

}


void IntersectGUI::on_infileButton_clicked()
{
	//figures.clear();//清空当前几何图形
	QFile* file = new QFile;   //申请一个文件指针
	file->setFileName(filePath);   //设置文件路径
	bool ok = file->open(QIODevice::ReadOnly);
	if (ok)
	{
		QTextStream in(file);
		msg = in.readAll();
		//ui.textBrowser->append("msg:\n"+msg);
		QStringList list = msg.split("\n");
		int n = list.at(0).toInt();//结合体个数
		for (int i = 1; i < n + 1; i++) {//在listWidget中展示 并存入figures中
			QListWidgetItem* elem1 = new QListWidgetItem(list.at(i), ui.listWidget);
			elem1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
			elem1->setCheckState(Qt::Unchecked);
			figures.push_back(list.at(i).toStdString());
		}

		file->close();
	}
	// ui.textBrowser->append("infile_button figurs_size:"+QString::number(figures.size())+"\n");
}



void IntersectGUI::on_addCButton_clicked()
{
	QString x0 = ui.x0Box->text();
	QString y0 = ui.y0Box->text();
	QString r = ui.rBox->text();
	QString str = "C " + x0 + " " + y0 + " " + r;
	QListWidgetItem* elem = new QListWidgetItem(str, ui.listWidget);
	elem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	elem->setCheckState(Qt::Unchecked);
	figures.push_back(str.toStdString());
	//ui.textBrowser->append("addC_button figurs_size:"+QString::number(figures.size())+"\n");
}

void IntersectGUI::on_addLineButton_clicked()
{
	QString x1 = ui.x1Box->text();
	QString y1 = ui.y1Box->text();
	QString x2 = ui.x2Box->text();
	QString y2 = ui.y2Box->text();
	QString str0 = x1 + " " + y1 + " " + x2 + " " + y2;
	int type = ui.lineTypeBox->currentIndex();
	QString str;
	if (type == 0) {
		str = "L " + str0;
	}
	else if (type == 1) {
		str = "R " + str0;
	}
	else {
		str = "S " + str0;
	}
	QListWidgetItem* elem = new QListWidgetItem(str, ui.listWidget);
	elem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
	elem->setCheckState(Qt::Unchecked);
	figures.push_back(str.toStdString());
	//ui.textBrowser->append("addL_button figurs_size:"+QString::number(figures.size())+"\n");
}



void IntersectGUI::on_clearButton_clicked()
{
	figures.clear();
	points.clear();
	ui.listWidget->clear();
	update();
	//ui.textBrowser->append("clear_button figurs_size:"+QString::number(figures.size())+"\n");
}

void IntersectGUI::on_deleteButton_clicked()
{
	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		QListWidgetItem* aItem = ui.listWidget->item(i);//获取一个项
		if (aItem->checkState() == Qt::Checked) {
			ui.listWidget->takeItem(i);
			delete aItem;
			figures.erase(figures.begin() + i);
			i--;
		}
	}
	//ui.textBrowser->append("delete_button figurs_size:"+QString::number(figures.size())+"\n");
	/*
	for(size_t j=0;j<figures.size();j++){
		ui.textBrowser->append(QString::fromStdString(figures.at(j)));
	}
	*/

}

void IntersectGUI::on_drawFigureButton_clicked()
{
	//ui.textBrowser->append("drawALL_button figurs_size:"+QString::number(figures.size())+"\n");
	update();
}


void IntersectGUI::draw_ray(int x1, int y1, int x2, int y2, QColor const c) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
	painter.setViewport(20, 20, CANVAS_SIZE, CANVAS_SIZE);
	painter.setWindow(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X);
	QPen pen;
	pen.setColor(c);
	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(W_);
	painter.setPen(pen);


	if (x2 == x1) {
		if (y2 > y1) {
			painter.drawLine(TRANS(x1),TRANS(y1),TRANS(x1), WINDOW_X);
		}
		else {
			painter.drawLine(TRANS(x1),TRANS(y1),TRANS(x1), -WINDOW_X);
		}
	}
	else if (y1 == y2) {
		if (x2 > x1) {
			painter.drawLine(TRANS(x1), TRANS(y1), WINDOW_X, TRANS(y1));
		}
		else {
			painter.drawLine(TRANS(x1),TRANS(y1), -WINDOW_X,TRANS(y1));
		}
	}
	else {
		double k = ((double)y2 - y1) / ((double)x2 - x1);
		double b = y1 - k * x1;
		double tx2, ty2;
		if (x2 > x1) {
			double y_ = MAX_X * k + b;
			if (y_ > MAX_X) {
				ty2 = MAX_X;
				tx2 = (ty2 - b) / k;
			}
			else if (y_ < -MAX_X) {
				ty2 = -MAX_X;
				tx2 = (ty2 - b) / k;
			}
			else {
				tx2 = MAX_X;
				ty2 = y_;
			}
		}
		else {
			double y_ = -MAX_X * k + b;
			if (y_ > MAX_X) {
				ty2 = MAX_X;
				tx2 = (ty2 - b) / k;
			}
			else if (y_ < -MAX_X) {
				ty2 = -MAX_X;
				tx2 = (ty2 - b) / k;
			}
			else {
				tx2 = -MAX_X;
				ty2 = y_;
			}
		}
		painter.drawLine(TRANS(x1),TRANS(y1),TRANS(tx2), TRANS(ty2));
	}
}

void IntersectGUI::draw_line(int x1, int y1, int x2, int y2, QColor const c)
{   /*
	draw_ray(x1,y1,x2,y2,c);
	draw_ray(x2,y2,x1,y1,c);
	*/
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
	painter.setViewport(20, 20, CANVAS_SIZE, CANVAS_SIZE);
	painter.setWindow(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X);
	QPen pen;
	pen.setColor(c);
	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(W_);
	painter.setPen(pen);

	int A = y1 - y2;
	int B = x2 - x1;
	double C = (double)x1 * y2 - (double)x2 * y1;
	if (A == 0) {
		QPoint p1(-WINDOW_X,TRANS(y1));
		QPoint p2(WINDOW_X, TRANS(y1));
		painter.drawLine(p1, p2);
		return;
	}
	else if (B == 0) {
		QPoint p1(TRANS(x1), -WINDOW_X);
		QPoint p2(TRANS(x2), WINDOW_X);
		painter.drawLine(p1, p2);
		return;
	}
	else {
		QPoint p1;
		QPoint p2;
		double data1, data2, data3, data4;
		data1 = (-C - (double)A * MAX_X) / B;//当x取MAX_X时，y的值
		data2 = (-C + (double)A * MAX_X) / B;//当x取-MAX_X时，y的值
		data3 = (-C - (double)B * MAX_X) / A;//当y取MAX_X时，x的值
		data4 = (-C + (double)B * MAX_X) / A;//当y取-MAX_X时，x的值
		if (data1 >= -MAX_X && data1 <= MAX_X
			&& data2 >= -MAX_X && data2 <= MAX_X) {
			painter.drawLine(WINDOW_X, TRANS(data1), -WINDOW_X,TRANS(data2));
			return;
		}
		else if (data1 >= -MAX_X && data1 <= MAX_X
			&& data3 >= -MAX_X && data3 <= MAX_X) {
			painter.drawLine(WINDOW_X, TRANS(data1), TRANS(data3), WINDOW_X);
			return;
		}
		else if (data1 >= -MAX_X && data1 <= MAX_X
			&& data4 >= -MAX_X && data4 <= MAX_X) {
			painter.drawLine(WINDOW_X, TRANS(data1), TRANS(data4), -WINDOW_X);
			return;
		}
		else if (data2 >= -MAX_X && data2 <= MAX_X
			&& data3 >= -MAX_X && data3 <= MAX_X) {
			painter.drawLine(-WINDOW_X, TRANS(data2), TRANS(data3), WINDOW_X);
			return;
		}
		else if (data2 >= -MAX_X && data2 <= MAX_X
			&& data4 >= -MAX_X && data4 <= MAX_X) {
			painter.drawLine(-WINDOW_X, TRANS(data2), TRANS(data4), -WINDOW_X);
			return;
		}
		else if (data3 >= -MAX_X && data3 <= MAX_X
			&& data4 >= -MAX_X && data4 <= MAX_X) {
			painter.drawLine(TRANS(data3), WINDOW_X, TRANS(data4), -WINDOW_X);
			return;
		}
	}

}

void IntersectGUI::draw_seg(int x1, int y1, int x2, int y2, QColor const c)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
	painter.setViewport(20, 20, CANVAS_SIZE, CANVAS_SIZE);
	painter.setWindow(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X);
	QPen pen;
	pen.setColor(c);
	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(W_);
	painter.setPen(pen);

	painter.drawLine(TRANS(x1), TRANS(y1),TRANS(x2), TRANS(y2));
}

void IntersectGUI::draw_circle(int x0, int y0, int r, QColor const c)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
	painter.setViewport(20, 20, CANVAS_SIZE, CANVAS_SIZE);
	painter.setWindow(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X);

	QPen pen;
	pen.setColor(c);
	pen.setStyle(Qt::SolidLine);
	pen.setWidthF(W_);
	painter.setPen(pen);

	painter.drawEllipse(TRANS(x0 - r), TRANS(y0 - r),TRANS(2 * r),TRANS(2 * r));
}

void IntersectGUI::draw_points()
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);//反锯齿
	painter.setViewport(20, 20, CANVAS_SIZE, CANVAS_SIZE);
	painter.setWindow(-WINDOW_X, WINDOW_X, 2 * WINDOW_X, -2 * WINDOW_X);

	QPen pen;
	pen.setColor(Qt::red);
	double w = (double)W_*3;
	pen.setWidthF(w);
	painter.setPen(pen);
	
	for (auto vit = points.begin(); vit != points.end(); ++vit) {
		painter.drawPoint(TRANS(vit->first), TRANS(vit->second));
		//painter.drawEllipse(TRANS(vit->first)-TRANS(w), TRANS(vit->second)-TRANS(w), TRANS(w * 2), TRANS(w * 2));
		//ui.textBrowser->append("<" + QString::number(vit->first) + "," + QString::number(vit->second) + ">\n");
	}


}

void IntersectGUI::draw_figures_from_str(string str)
{
	QStringList list = (QString::fromStdString(str)).split(" ");
	QString type = list.at(0);
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0, r = 0;
	if (list.size() == 5) {
		x1 = list.at(1).toInt();
		y1 = list.at(2).toInt();
		x2 = list.at(3).toInt();
		y2 = list.at(4).toInt();
	}
	else {
		x1 = list.at(1).toInt();
		y1 = list.at(2).toInt();
		r = list.at(3).toInt();
	}

	if (type == QString::fromLocal8Bit("L")) {
		draw_line(x1, y1, x2, y2);
	}
	else if (type == QString::fromLocal8Bit("S")) {
		draw_seg(x1, y1, x2, y2);
	}
	else if (type == QString::fromLocal8Bit("R")) {
		draw_ray(x1, y1, x2, y2);
	}
	else {
		draw_circle(x1, y1, r);
	}
}






int IntersectGUI::on_calcPButton_clicked()
{
	points.clear();
	std::string input;
	size_t n = figures.size();
	//ui.textBrowser->append("figures.size():" + QString::number(figures.size()));//???

	input += std::to_string(n) + "\n";
	for (size_t i = 0; i < n; i++) {
		input += figures.at(i) + "\n";
	}
	//ui.textBrowser->append(QString::fromStdString(input));
	int cnt = 0;
	//cnt = guiProcess(&points,figures);
	try {
		cnt = guiProcess(&points, input);
	}
	catch (std::exception e) {
		QString dlgTitle = QString::fromLocal8Bit("计算出现错误");
		QMessageBox::critical(this, dlgTitle, e.what());
		return 0;

	} {
	}
	ui.lineEdit->setText(QString::number(cnt));
	return cnt;

}