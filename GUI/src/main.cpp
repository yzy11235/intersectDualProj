#include "IntersectGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IntersectGUI w;
	w.show();
	return a.exec();
}
