#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QFileDialog>
#include <QTimer>

extern bool connected;
extern bool reset_flag;
extern bool vibration_enabled;
extern short int cmd;
extern short int ref[2];
extern float k_vib;
extern double CONSTANT_ROBOT_GAIN;
extern double Kp0, Kp1, Kp2;
extern IplImage* frame;
extern QString console_info_str;
extern short int finger[3];
extern double force_loadcell;

extern int phantom_init(int mode, const char* ip_host, double z0);
extern int phantom_close();

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QString FileOpName;
    IplImage* imagerd;
    QString console_packet_str;
    QTimer* timer;
    QTimer* webcam_timer;

private slots:
    void closeEvent(QCloseEvent*);
    void on_StartApp_clicked();
    void on_Close_clicked();
    void on_ShowImage_clicked();
    void update_ImageLabel();
    void on_Pause_QB_clicked();
    void on_SavePhantomButton_clicked();
    void on_SaveAccelerationsButton_clicked();
    void on_SeeOutput_clicked();
    void update_StatusLabel();
    void on_Vibration_checkBox_stateChanged();
    void on_increase_kvib_clicked();
    void on_decrease_kvib_clicked();
    void on_increase_kp0_clicked();
    void on_decrease_kp0_clicked();
    void on_increase_kp2_clicked();
    void on_decrease_kp2_clicked();
    void on_PWM_method_combo_currentIndexChanged();
    void on_XY_SF_valueChanged();
    void on_Help_clicked();
    void on_Motor_ref_checkBox_stateChanged();
    void on_motor_ref0_valueChanged();
    void on_motor_ref1_valueChanged();

private:
    Ui::MainWindow *ui;
    
};

#endif // MAINWINDOW_H
