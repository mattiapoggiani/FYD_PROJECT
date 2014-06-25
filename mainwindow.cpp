#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/globals.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = 0;
    webcam_timer = 0;
    ui->Vibration_gain_value_label->setVisible(false);
    ui->XY_SF->setValue(int(CONSTANT_ROBOT_GAIN*10));
    ui->XY_SF_value_label->setText("1 mm FYD -> " + QString::number(CONSTANT_ROBOT_GAIN, 'g', 4) + " mm robot");
    ui->kp0_value_label->setText(QString::number(Kp0, 'g', 4));
    ui->kp2_value_label->setText(QString::number(Kp2, 'g', 4));
    ui->Vibration_gain_value_label->setVisible(true);
    on_Motor_ref_checkBox_stateChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
    on_Close_clicked();
    event->accept();
 }

void MainWindow::on_StartApp_clicked()
{
    static bool pressed = false;
    int mode = ui->Connection_mode_combo->currentIndex();       // 0 -> Ethernet / 1 -> Wireless
    if (!pressed) {
        double z0 = 0;                                 // TO ADJUST
        if (!phantom_init(mode, "", z0)){
            ui->InfoTextEdit->appendPlainText("Phantom application started - talking to F.Y.D. device");
            ui->StartApp->setText("Reset Phantom");
        }
        else {
            ui->InfoTextEdit->setPlainText("Phantom application initialization error");
        }
        ui->Vibration_gain_label->setVisible(true);
        ui->Vibration_gain_value_label->setText(QString::number(k_vib));      //prendere da QB_info() iniziale
        ui->motor0_ref_value_label->setText(QString::number(ref[0]));
        ui->motor_ref0->setValue(ref[0]);
        ui->motor1_ref_value_label->setText(QString::number(ref[1]));
        ui->motor_ref1->setValue(ref[1]);
        ui->InfoTextEdit->update();
        on_SeeOutput_clicked();
        pressed = true;
    }
    else {
        // Reset Phantom driving the robot at initial position
        reset_flag = true;
    }

}

void MainWindow::on_Close_clicked(){
    static bool pressed = false;
    if (!pressed){
        cmd = 9;
        ui->InfoTextEdit->appendPlainText("Closing application ... ");
        ui->InfoTextEdit->update();
        sleep(2);
        if (!phantom_close()){
            ui->InfoTextEdit->appendPlainText("OK!");
            sleep(1);
            ui->StartApp->setEnabled(true);
        }
        pressed = true;
    }
}

void MainWindow::on_ShowImage_clicked(){
    static bool pressed = false;
    if (!pressed){
        cmd = 7;
        ui->ShowImage->setText("Stop to show image");
        pressed = true;
    }
    else{
        cmd = 8;
        ui->ShowImage->setText("Show webcam image");
        pressed = false;
    }

    if (webcam_timer)
    {
        webcam_timer->stop();
        delete webcam_timer;
        webcam_timer=0;
    }
    else
    {
        webcam_timer = new QTimer(this);
        connect(webcam_timer, SIGNAL(timeout()), this, SLOT(update_ImageLabel()));
        webcam_timer->start(40);
    }
}

void MainWindow::update_ImageLabel(){
//    QImage imageView = QImage((const unsigned char*)(frame->imageData), frame->width,frame->height,QImage::Format_RGB888).rgbSwapped();
//    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageView));
    ui->ImageLabel->update();
}

void MainWindow::on_Pause_QB_clicked(){
    static bool pressed = false;
    if (!pressed){
        cmd = 5;
        ui->Pause_QB->setText("Restart");
        pressed = true;
        sleep(1);
        ui->InfoTextEdit->appendPlainText(console_info_str);
        ui->InfoTextEdit->update();
    }
    else{
        cmd = 6;
        ui->Pause_QB->setText("Pause and get QB info");
        pressed = false;
    }
}


void MainWindow::on_SavePhantomButton_clicked(){
    //declare FileOpName as the choosen opened file name
    FileOpName = QFileDialog::getSaveFileName(this, "Save Phantom Log to:", QDir::currentPath(),"Text Files (*.txt *.csv *.log)");

    //function to load the image whenever fName is not empty
    if( FileOpName.size() ){
        //copy file
        QFile::copy(PHANTOM_FILE_PATH, FileOpName);
    }
}

void MainWindow::on_SaveAccelerationsButton_clicked(){
    //declare FileOpName as the choosen opened file name
    FileOpName = QFileDialog::getSaveFileName(this, "Save Acceleration Log to:", QDir::currentPath(),"Text Files (*.txt *.csv *.log)");

    //function to load the image whenever fName is not empty
    if( FileOpName.size() ){
        //copy file
        QFile::copy(ACCELER_FILE_PATH, FileOpName);
    }
}

void MainWindow::on_SeeOutput_clicked(){
    if (timer)
    {
        timer->stop();
        delete timer;
        timer=0;
        ui->StatusLabel->clear();
        ui->SeeOutput->setText("See Output");
    }
    else
    {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update_StatusLabel()));
        timer->start(40);
        ui->SeeOutput->setText("Stop seeing output");
    }
}

void MainWindow::update_StatusLabel(){
    console_packet_str = QString("LAST FINGER POSITION: %1, %2, %3, FORCE: %4").arg(finger[0]).arg(finger[1]).arg(finger[2]).arg(force_loadcell);
    ui->StatusLabel->setText(console_packet_str);
    ui->StatusLabel->update();
}

void MainWindow::on_Vibration_checkBox_stateChanged(){
    if (ui->Vibration_checkBox->isChecked())
        vibration_enabled = true;
    else
        vibration_enabled = false;
}

void MainWindow::on_decrease_kvib_clicked(){
    cmd = 1;
    ui->InfoTextEdit->appendPlainText("Decrease vibration gain");
    ui->InfoTextEdit->update();
    float val = ui->Vibration_gain_value_label->text().toFloat() - 0.1;
    ui->Vibration_gain_value_label->setText(QString::number(val, 'g', 4));
}

void MainWindow::on_increase_kvib_clicked(){
    cmd = 2;
    ui->InfoTextEdit->appendPlainText("Increase vibration gain");
    ui->InfoTextEdit->update();
    float val = ui->Vibration_gain_value_label->text().toFloat() + 0.1;
    ui->Vibration_gain_value_label->setText(QString::number(val, 'g', 4));
}

void MainWindow::on_decrease_kp0_clicked(){
    Kp0 -= 0.05;
    ui->InfoTextEdit->appendPlainText("Decrease gain on horizontal movement");
    ui->InfoTextEdit->update();
    float val = ui->kp0_value_label->text().toFloat() - 0.05;
    ui->kp0_value_label->setText(QString::number(val, 'g', 4));
}

void MainWindow::on_increase_kp0_clicked(){
    Kp0 += 0.05;
    ui->InfoTextEdit->appendPlainText("Increase gain on horizontal movement");
    ui->InfoTextEdit->update();
    float val = ui->kp0_value_label->text().toFloat() + 0.05;
    ui->kp0_value_label->setText(QString::number(val, 'g', 4));
}

void MainWindow::on_decrease_kp2_clicked(){
    Kp2 -= 0.05;
    ui->InfoTextEdit->appendPlainText("Decrease gain on vertical movement");
    ui->InfoTextEdit->update();
    float val = ui->kp2_value_label->text().toFloat() - 0.05;
    ui->kp2_value_label->setText(QString::number(val, 'g', 4));
}

void MainWindow::on_increase_kp2_clicked(){
    Kp2 += 0.05;
    ui->InfoTextEdit->appendPlainText("Increase gain on vertical movement");
    ui->InfoTextEdit->update();
    float val = ui->kp2_value_label->text().toFloat() + 0.05;
    ui->kp2_value_label->setText(QString::number(val, 'g', 4));
}

void MainWindow::on_PWM_method_combo_currentIndexChanged(){
    if (ui->PWM_method_combo->currentIndex() == 0)
        cmd = 3;
    if (ui->PWM_method_combo->currentIndex() == 1)
        cmd = 4;
    ui->InfoTextEdit->appendPlainText("Changed vibration method to " + ui->PWM_method_combo->currentText());
    ui->InfoTextEdit->update();
}

void MainWindow::on_XY_SF_valueChanged(){
    CONSTANT_ROBOT_GAIN = ui->XY_SF->value()/10.0;
    float val = ui->XY_SF->value()/10.0;
    ui->XY_SF_value_label->setText("1 mm FYD -> " + QString::number(val, 'g', 4) + " mm robot");
}

void MainWindow::on_Help_clicked(){
    QMessageBox box;
    QString str = QString("Help - Button functionality:\n") + \
                  QString("Start Program - initialize F.Y.D. device and Phantom and opens connection between them\n") + \
                  QString("Close - close connection and the application\n") + \
                  QString("Vibration Gain - Increase/Decrease gain on PWM vibration according to PWM method (SoC or DFT321)\n") + \
                  QString("Movement Scale factor - F.Y.D./robot SFs");
    box.setText(str);
    box.exec();
}

void MainWindow::on_Motor_ref_checkBox_stateChanged(){
    if (ui->Motor_ref_checkBox->isChecked()){
        ui->motor0_ref_label->setEnabled(true);
        ui->motor_ref0->setEnabled(true);
        ui->motor0_ref_value_label->setEnabled(true);
        ui->motor1_ref_label->setEnabled(true);
        ui->motor_ref1->setEnabled(true);
        ui->motor1_ref_value_label->setEnabled(true);
    }
    else {
        ui->motor0_ref_label->setEnabled(false);
        ui->motor_ref0->setEnabled(false);
        ui->motor0_ref_value_label->setEnabled(false);
        ui->motor1_ref_label->setEnabled(false);
        ui->motor_ref1->setEnabled(false);
        ui->motor1_ref_value_label->setEnabled(false);
    }
}

void MainWindow::on_motor_ref0_valueChanged(){
    cmd = 10;
    ref[0] = (short int)ui->motor_ref0->value();
    ui->motor0_ref_value_label->setText(QString::number(ref[0]));
}

void MainWindow::on_motor_ref1_valueChanged(){
    cmd = 10;
    ref[1] = (short int)ui->motor_ref1->value();
    ui->motor1_ref_value_label->setText(QString::number(ref[1]));
}
