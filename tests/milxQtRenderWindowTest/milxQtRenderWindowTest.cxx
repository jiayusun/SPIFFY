#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include "milxQtRenderWindow.h"
#include <vtkRenderWindowInteractor.h>
#include "vtkImageViewer3.h"
#include "milxFile.h"
#include "milxImage.h"
#include "milxGlobal.h"
#include <sstream>
#include "ui_spiffy.h"


int main(int argc, char *argv[])
{

	QApplication app(argc, argv);
	QFile qss(":/resources/style.qss");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();
	QMainWindow *mainWindow = new QMainWindow;
	Ui::MainWindow ui;
	
	ui.setupUi(mainWindow);

	if (argc < 2)
	{
		cerr << "View an image with correct orientation." << endl;
		cerr << "Usage: " << argv[0] << " <image>" << endl;
		exit(EXIT_FAILURE);
	}
	std::string fileName = argv[1];

	typedef itk::Image<float, 3> VisualizingImageType;

	///Open image
	VisualizingImageType::Pointer image = VisualizingImageType::New();
	if (!milx::File::OpenImage<VisualizingImageType>(fileName, image))
	{
		milx::PrintError("Could not open file.");
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkImageData> imageVTK = milx::Image<VisualizingImageType>::ConvertITKImageToVTKImage(image);
	vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	vtkSmartPointer<vtkImageData> imageVTKReoriented = milx::Image<VisualizingImageType>::ApplyOrientationToVTKImage(imageVTK,image,matrix,true);
	
	// Visualize
	vtkSmartPointer<vtkImageViewer3> imageViewer = vtkSmartPointer<vtkImageViewer3>::New();
	imageViewer->SetInputData(imageVTKReoriented);
	imageViewer->GetRenderWindow()->SetSize(500, 500);
	imageViewer->GetRenderer()->ResetCamera();
	//
	//~ imageViewer->SetSlice(bounds[5]/2); //show middle of volume
	

	milxQtRenderWindow *renderWindow = new milxQtRenderWindow(mainWindow);
	renderWindow->setGeometry(QRect(90, 25, 590, 590));
	renderWindow->SetRenderer(imageViewer->GetRenderer());
	renderWindow->SetRenderWindow(imageViewer->GetRenderWindow());
	imageViewer->SetupInteractor(renderWindow->GetInteractor());	
	imageViewer->Render();
	imageViewer->SetSliceOrientationToXZ(); //Saggital

	mainWindow->setWindowTitle("milxQtWindowTest");
	mainWindow->show();
	return app.exec();
}