#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <iostream> //标准输入输出流
#include <QString>
#include "About.h"

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>
#include "QVTKWidget.h"
#include "zThread.h"

//#include "PointCloudFusionApp/ReadFile.h"
extern int start(std::string p_filePath);

bool next_iteration = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileName("")
{
    ui->setupUi(this);
    //Set up the QVTK window
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer",false));
    source_viewer.reset(new pcl::visualization::PCLVisualizer("source_viewer",false));
    ui->centralWidget->SetRenderWindow(viewer->getRenderWindow());
    ui->subWidget->SetRenderWindow(source_viewer->getRenderWindow());
    viewer->setupInteractor(ui->centralWidget->GetInteractor(),ui->centralWidget->GetRenderWindow());
    source_viewer->setupInteractor(ui->subWidget->GetInteractor(),ui->subWidget->GetRenderWindow());
//    ui->centralWidget->update();
    ui->centralWidget->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::readPCL(std::string pcd_Path)
{
    pcl::PointCloud<PointT>::Ptr tempcloud (new pcl::PointCloud<PointT>); // 创建点云（指针）

    cloud = tempcloud;
    clouds_vector.push_back(cloud);
    wait = new WaitDialog;
    wait->setModal(true);
    wait->show();
//    QLabel *label = new QLabel();
//    QMovie *movie = new QMovie(":/images/loading0.gif");
//    label->setMovie(movie);
//    movie->start();
//    label->show();

    zThread *thread = new zThread(cloud,pcd_Path,zThread::READ);
    connect(thread,SIGNAL(finished()),this,SLOT(displayViewer()));
    thread->start();
}

void keyboardEventOccurred(const pcl::visualization::KeyboardEvent &event, void *nothing)
{
    if (event.getKeySym() == "space" && event.keyDown())
    {
        next_iteration = true;
        qDebug()<<"iterator:"<<next_iteration;
    }
}

void MainWindow::viewIterator()
{
    // Register keyboard callback :
    viewer->registerKeyboardCallback(&keyboardEventOccurred, (void*)NULL);

    // Display the visualiser
    while (!viewer->wasStopped())
    {
        viewer->spinOnce();

        // The user pressed "space" :
        if (next_iteration)
        {
            // The Iterative Closest Point algorithm
            time.tic();
            //icp.align(*cloud_icp);
            std::cout << "Applied 1 ICP iteration in " << time.toc() << " ms" << std::endl;
            /*
            if (icp.hasConverged())
            {
                printf("\033[11A");  // Go up 11 lines in terminal output.
                printf("\nICP has converged, score is %+.0e\n", icp.getFitnessScore());
                std::cout << "\nICP transformation " << ++iterations << " : cloud_icp -> cloud_in" << std::endl;
                transformation_matrix *= icp.getFinalTransformation().cast<double>();  // WARNING /!\ This is not accurate! For "educational" purpose only!
                print4x4Matrix(transformation_matrix);  // Print the transformation between original pose and current pose

                ss.str("");
                ss << iterations;
                std::string iterations_cnt = "ICP iterations = " + ss.str();
                viewer->updateText(iterations_cnt, 10, 60, 16, txt_gray_lvl, txt_gray_lvl, txt_gray_lvl, "iterations_cnt");
                viewer->updatePointCloud(cloud_icp, cloud_icp_color_h, "cloud_icp_v2");
            }
            else
            {
                PCL_ERROR("\nICP has not converged.\n");
            }
            */
        }
        next_iteration = false;
    }
}

void MainWindow::displayViewer()
{
    wait->close();
    delete wait;
    wait = NULL;
    //qDebug()<<(cloud->points[0]).rgb;
    qDebug() << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_file.pcd with the following fields: ";
    //for (size_t i = 0; i < cloud->points.size (); ++i) //显示所有的点

    //        for (size_t i = 0; i < 5; ++i) // 为了方便观察，只显示前5个点
    //        std::cout << "    " << cloud->points[i].x
    //                  << " "    << cloud->points[i].y
    //                  << " "    << cloud->points[i].z << std::endl;
    //        pcl::visualization::CloudViewer viewer("Cloud Viewer1");
    //        viewer.showCloud(cloud);

    viewer->addPointCloud(cloud,fileName);
    viewer->resetCamera();
    ui->centralWidget->update();
    source_viewer->addPointCloud(cloud,fileName);
    source_viewer->resetCamera();
    ui->subWidget->update();
}

void MainWindow::on_readFile_action_triggered()
{
    QStringList filePath = QFileDialog::getOpenFileNames(this,
        tr("Open File"),
        "f:/Bibased",
        tr("Files (*.pcd *.txt *.jpg *.png *.jpg)"),
        0);
    if(!filePath.empty()){
//        for(int i=0;i<filePath.length();i++)
//        {
//            ReadFile readfile;
//            if(readfile.open(filePath.at(i).toStdString(),ReadFile::IOS_IN)){
//                char a[30];
//                while(readfile.read(a,30))
//                {
//                   ui->textEdit->append(a);
//                   qDebug()<<a;
//                }
//                readfile.close();
//            }
//        }
        QString tempFilePath = filePath.at(0);
        readPCL(tempFilePath.toStdString());
        fileName = tempFilePath.mid(tempFilePath.lastIndexOf('/')+1,tempFilePath.lastIndexOf('.')-tempFilePath.lastIndexOf('/')-1).toStdString();
        qDebug()<<QString::fromStdString(fileName);
    }
}

void MainWindow::on_delete_action_triggered()
{
    viewer->removeAllPointClouds();
    viewer->resetCamera();
    ui->centralWidget->update();
    source_viewer->removeAllPointClouds();
    source_viewer->resetCamera();
    ui->subWidget->update();
    std::vector<pcl::PointCloud<PointT>::Ptr>::iterator iter = clouds_vector.begin();
    for(;iter != clouds_vector.end();/*iter++*/){
        iter = clouds_vector.erase(iter);
    }
}

void MainWindow::on_execute_action_triggered()
{
    if(clouds_vector.size()>=2){
        qDebug()<<QString::fromLocal8Bit("执行一次");
        ICPBlend* icpBlend = new ICPBlend();
        std::vector<pcl::PointCloud<PointT>::Ptr>::iterator iter = clouds_vector.begin();
        viewer->removeAllPointClouds();
        pcl::visualization::PointCloudColorHandlerCustom<PointT> tgt_h(*iter, 0, 255, 0);
        viewer->addPointCloud(*iter,tgt_h,"cloud0");
        int length = clouds_vector.size();
        iter++;
        for(int i=1; i < length;i++)
        {
            pcl::PointCloud<PointT>::Ptr temp = icpBlend->blend(clouds_vector[1],clouds_vector[0]);

            pcl::visualization::PointCloudColorHandlerCustom<PointT> src_h(temp, 0, 0, 255);
            viewer->addPointCloud(temp,src_h,"cloud"+i);
            iter = clouds_vector.erase(iter);
            clouds_vector.push_back(temp);
        }
        viewIterator();
        ui->centralWidget->update();
    }
}

void MainWindow::on_exportFile_action_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Open Config"),
            "f:/Bibased",
            tr("Config Files (*.pcd)"));

    if (!fileName.isNull())
    {
        //fileName是文件名
        qDebug()<<fileName;
        pcl::PointCloud<PointT>::Ptr writeCloud (new pcl::PointCloud<PointT>);
        std::vector<pcl::PointCloud<PointT>::Ptr>::iterator iterator = clouds_vector.begin();

        while(iterator != clouds_vector.end()){
            for(int i=0;i<(*iterator).get()->size();i++)
            {
                writeCloud->push_back((*iterator).get()->points[i]);
            }

            iterator++;
        }

        zThread *thread = new zThread(writeCloud,fileName.toStdString(),zThread::WRITE);
        thread->start();
    }
    else
    {
        //点的是取消
    }
}

void MainWindow::on_mulFusion_action_triggered()
{
    QString tempFilePath;
    std::string tempFileName;
    QStringList filePaths = QFileDialog::getOpenFileNames(this,
        tr("Open File"),
        "f:/Bibased",
        tr("Files (*.pcd *.txt *.jpg *.png *.jpg)"),
        0);
    if(!filePaths.empty()){

        wait = new WaitDialog;
        wait->setModal(true);
        wait->show();
        pcl::PointCloud<PointT>::Ptr cloud_in (new pcl::PointCloud<PointT>);
        pcl::PointCloud<PointT>::Ptr cloud_tr (new pcl::PointCloud<PointT>);
        ICPBlend* icpBlend = new ICPBlend();
        if (pcl::io::loadPCDFile<PointT> (filePaths.at(0).toStdString(), *cloud_in) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
        {
            PCL_ERROR ("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
            return ;
        }
        clouds_vector.push_back(cloud_in);
        tempFilePath = filePaths.at(0);
        tempFileName = tempFilePath.mid(tempFilePath.lastIndexOf('/')+1,tempFilePath.lastIndexOf('.') - tempFilePath.lastIndexOf('/')-1).toStdString();
        viewer->addPointCloud(cloud_in,tempFileName);
        source_viewer->addPointCloud(cloud_in);
        viewer->resetCamera();
        source_viewer->resetCamera();
        ui->centralWidget->update();
        ui->subWidget->update();
        for(int i = 1 ;i<filePaths.size();i++)
        {
            if (pcl::io::loadPCDFile<PointT> (filePaths.at(i).toStdString(), *cloud_tr) == -1) //* 读入PCD格式的文件，如果文件不存在，返回-1
            {
                PCL_ERROR ("Couldn't read file test_pcd.pcd \n"); //文件不存在时，返回错误，终止程序。
                break ;
            }
            clouds_vector.push_back(cloud_tr);
            tempFilePath = filePaths.at(i);
            tempFileName = tempFilePath.mid(tempFilePath.lastIndexOf('/')+1 , tempFilePath.lastIndexOf('.') - tempFilePath.lastIndexOf('/')-1).toStdString();
            cloud_tr = icpBlend->blend(cloud_tr,cloud_in);
            viewer->addPointCloud(cloud_tr , tempFileName);
            source_viewer->addPointCloud(cloud_tr , tempFileName);
            viewer->resetCamera();
            source_viewer->resetCamera();
            ui->centralWidget->update();
            ui->subWidget->update();
        }
        wait->close();
        delete wait;
        wait = NULL;
    }
}

void MainWindow::on_exit_action_triggered()
{
    exit(0);
}

void MainWindow::on_fullScreen_action_triggered()
{
    ui->centralWidget->setWindowFlags(Qt::Window);
    ui->centralWidget->showFullScreen();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Escape)
        {
            qDebug()<<QString::fromLocal8Bit("退出全屏");
            ui->centralWidget->setWindowFlags(Qt::SubWindow);
            ui->centralWidget->showNormal();
            return true;
        }

    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::resizeEvent(QResizeEvent *size)
{
    qDebug()<<"resize Event";
    ui->subWidget->setGeometry(window()->width()-261,window()->height()-311,261,221);
}

void MainWindow::on_about_action_triggered()
{
    About about;
    about.exec();
}

void MainWindow::on_transform_action_triggered()
{
        Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();

        // Define a rotation matrix (see https://en.wikipedia.org/wiki/Rotation_matrix)
        // Here we defined a 45° (PI/4) rotation around the Z axis and a translation on the X axis.
        float theta = M_PI/4; // The angle of rotation in radians
        transform_1 (0,0) = cos (theta);
        transform_1 (0,1) = -sin(theta);
        transform_1 (1,0) = sin (theta);
        transform_1 (1,1) = cos (theta);
        //    (row, column)

        // Define a translation of 2.5 meters on the x axis.
        transform_1 (0,3) = 2.5;

        // Print the transformation
        printf ("Method #1: using a Matrix4f\n");
        std::cout << transform_1 << std::endl;


        // Executing the transformation
        pcl::PointCloud<PointT>::Ptr transformed_cloud (new pcl::PointCloud<PointT> ());
        /*
        void pcl::transformPointCloud(const pcl::PointCloud< PointT > & cloud_in,
                                        pcl::PointCloud< PointT > &  cloud_out,
                                        const Eigen::Matrix4f &  transform  )
        */
        // Apply an affine transform defined by an Eigen Transform.
        pcl::transformPointCloud (*cloud, *transformed_cloud, transform_1);
        cloud = transformed_cloud;
        viewer->removeAllPointClouds();
        viewer->addPointCloud(cloud,"transform_t");
        clouds_vector.clear();
        clouds_vector.push_back(cloud);
        viewer->resetCamera();
        source_viewer->resetCamera();
        ui->centralWidget->update();
        ui->subWidget->update();
}

void MainWindow::on_osgExport_action_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(NULL,
            "Open Config",
            "f:/Bibased",
            "Config Files (*.pcd)");

    if (!fileName.isNull())
    {
        //fileName是文件名
        qDebug()<<fileName;
        start(fileName.toStdString());
    }

}
