#include <QApplication>
#include <QFile>
#include <iostream>
#include <QMainWindow>
#include "milxQtImage.h"
#include <vtkRenderWindowInteractor.h>
#include "vtkImageViewer3.h"
#include "milxFile.h"
#include <QSplashScreen>
#include "milxImage.h"
#include "milxGlobal.h"
#include <sstream>
#include "ui_spiffy.h"
#include<windows.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 
/*
template<class TImage>
vtkSmartPointer<vtkImageData> openImage(std::string fileName, itk::SmartPointer<TImage> &imageData)
{
	
	///Open image

	if (!milx::File::OpenImage<TImage>(fileName, imageData))
	{
		milx::PrintError("Could not open file.");

	}
	vtkSmartPointer<vtkImageData> imageVTK = milx::Image<TImage>::ConvertITKImageToVTKImage(imageData);
	vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	vtkSmartPointer<vtkImageData> imageVTKReoriented = milx::Image<TImage>::ApplyOrientationToVTKImage(imageVTK, imageData, matrix, true);
	milx::PrintDebug("Open file successfully.");
	return imageVTKReoriented;
}
*/

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	QPixmap icon(":resources/spiffy_icon.png");
	app.setWindowIcon(QIcon(icon));

	QFile qss(":/resources/style.qss");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();

	QPixmap pixmap(":resources/spiffy_splash.png");
	QSplashScreen splash(pixmap);
	//        splash.setMask(pixmap.mask());
	splash.show();
	app.processEvents();
	
	QMainWindow *mainWindow = new QMainWindow;
	if (argc < 2)
	{
		//	cerr << "View an image with correct orientation." << endl;
		milxQtImage *image = new milxQtImage(mainWindow);
		mainWindow->setWindowTitle("SPIFFY");
		mainWindow->show();
		QSignalMapper *mapper = new QSignalMapper;
		mapper->setMapping(&app, mainWindow);
		QObject::connect(&app, SIGNAL(aboutToQuit()), mapper, SLOT(map()));
		QObject::connect(mapper, SIGNAL(mapped(QWidget*)), image, SLOT(writeSettings(QWidget*)));
		splash.finish(mainWindow);
		milx::PrintDebug("setup done.");
	}
	return app.exec();
}
	//if (argc == 2)
	//{
	//	std::string fileName = argv[1];

		//open image
	//	typedef itk::Image<float, 3> VisualizingImageType;
	//	VisualizingImageType::Pointer imageType = VisualizingImageType::New();
	//	vtkSmartPointer<vtkImageData> imageVTK = openImage<VisualizingImageType>(fileName, imageType);

		//load image 
	//	milxQtImage *image = new milxQtImage(mainWindow);
	//	image->setData(imageVTK, 0);
	//	image->generate(0);
//		milx::PrintDebug("Generate image done.");
//		mainWindow->setWindowTitle("SPIFFY");
//		mainWindow->show();
//		QSignalMapper *mapper = new QSignalMapper;
//		mapper->setMapping(&app, mainWindow);
//		QObject::connect(&app, SIGNAL(aboutToQuit()), mapper, SLOT(map()));
//		QObject::connect(mapper, SIGNAL(mapped(QWidget*)), image, SLOT(writeSettings(QWidget*)));
//		splash.finish(mainWindow);

//	}



