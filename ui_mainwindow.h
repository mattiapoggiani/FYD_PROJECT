/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Jun 12 17:56:59 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCredits;
    QWidget *centralWidget;
    QPushButton *StartApp;
    QLabel *StatusLabel;
    QPushButton *Close;
    QPushButton *Pause_QB;
    QPushButton *ShowImage;
    QLabel *IP_label;
    QPushButton *SavePhantomButton;
    QLabel *ImageLabel;
    QPushButton *SaveAccelerationsButton;
    QPushButton *SeeOutput;
    QPushButton *increase_kvib;
    QPushButton *decrease_kvib;
    QLabel *Vibration_gain_label;
    QLabel *Vibration_gain_value_label;
    QSlider *XY_SF;
    QLabel *PWM_method_label;
    QComboBox *PWM_method_combo;
    QPlainTextEdit *InfoTextEdit;
    QLabel *XY_SF_label;
    QLabel *XY_SF_value_label;
    QCheckBox *Vibration_checkBox;
    QComboBox *Connection_mode_combo;
    QPushButton *Help;
    QSlider *motor_ref0;
    QSlider *motor_ref1;
    QLabel *motor0_ref_label;
    QLabel *motor1_ref_label;
    QCheckBox *Motor_ref_checkBox;
    QLabel *motor0_ref_value_label;
    QLabel *motor1_ref_value_label;
    QPushButton *decrease_kp0;
    QPushButton *increase_kp0;
    QPushButton *decrease_kp2;
    QPushButton *increase_kp2;
    QLabel *kp0_value_label;
    QLabel *kp2_value_label;
    QLabel *Vibration_gain_label_2;
    QLabel *Vibration_gain_label_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(840, 589);
        actionCredits = new QAction(MainWindow);
        actionCredits->setObjectName(QString::fromUtf8("actionCredits"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        StartApp = new QPushButton(centralWidget);
        StartApp->setObjectName(QString::fromUtf8("StartApp"));
        StartApp->setGeometry(QRect(10, 50, 111, 27));
        StatusLabel = new QLabel(centralWidget);
        StatusLabel->setObjectName(QString::fromUtf8("StatusLabel"));
        StatusLabel->setGeometry(QRect(10, 510, 401, 41));
        StatusLabel->setAutoFillBackground(false);
        StatusLabel->setFrameShape(QFrame::Panel);
        StatusLabel->setAlignment(Qt::AlignCenter);
        Close = new QPushButton(centralWidget);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setGeometry(QRect(140, 50, 111, 27));
        Pause_QB = new QPushButton(centralWidget);
        Pause_QB->setObjectName(QString::fromUtf8("Pause_QB"));
        Pause_QB->setGeometry(QRect(10, 90, 241, 27));
        ShowImage = new QPushButton(centralWidget);
        ShowImage->setObjectName(QString::fromUtf8("ShowImage"));
        ShowImage->setGeometry(QRect(560, 220, 201, 27));
        IP_label = new QLabel(centralWidget);
        IP_label->setObjectName(QString::fromUtf8("IP_label"));
        IP_label->setGeometry(QRect(10, 20, 171, 17));
        IP_label->setAlignment(Qt::AlignCenter);
        SavePhantomButton = new QPushButton(centralWidget);
        SavePhantomButton->setObjectName(QString::fromUtf8("SavePhantomButton"));
        SavePhantomButton->setGeometry(QRect(560, 10, 201, 27));
        ImageLabel = new QLabel(centralWidget);
        ImageLabel->setObjectName(QString::fromUtf8("ImageLabel"));
        ImageLabel->setGeometry(QRect(580, 90, 160, 120));
        ImageLabel->setFrameShape(QFrame::Panel);
        ImageLabel->setAlignment(Qt::AlignCenter);
        SaveAccelerationsButton = new QPushButton(centralWidget);
        SaveAccelerationsButton->setObjectName(QString::fromUtf8("SaveAccelerationsButton"));
        SaveAccelerationsButton->setGeometry(QRect(560, 50, 201, 27));
        SeeOutput = new QPushButton(centralWidget);
        SeeOutput->setObjectName(QString::fromUtf8("SeeOutput"));
        SeeOutput->setGeometry(QRect(10, 480, 151, 27));
        increase_kvib = new QPushButton(centralWidget);
        increase_kvib->setObjectName(QString::fromUtf8("increase_kvib"));
        increase_kvib->setGeometry(QRect(120, 324, 31, 27));
        decrease_kvib = new QPushButton(centralWidget);
        decrease_kvib->setObjectName(QString::fromUtf8("decrease_kvib"));
        decrease_kvib->setGeometry(QRect(160, 324, 31, 27));
        Vibration_gain_label = new QLabel(centralWidget);
        Vibration_gain_label->setObjectName(QString::fromUtf8("Vibration_gain_label"));
        Vibration_gain_label->setGeometry(QRect(10, 334, 111, 20));
        Vibration_gain_value_label = new QLabel(centralWidget);
        Vibration_gain_value_label->setObjectName(QString::fromUtf8("Vibration_gain_value_label"));
        Vibration_gain_value_label->setGeometry(QRect(210, 330, 31, 21));
        XY_SF = new QSlider(centralWidget);
        XY_SF->setObjectName(QString::fromUtf8("XY_SF"));
        XY_SF->setGeometry(QRect(120, 440, 81, 29));
        XY_SF->setMaximum(100);
        XY_SF->setSingleStep(1);
        XY_SF->setPageStep(1);
        XY_SF->setSliderPosition(0);
        XY_SF->setOrientation(Qt::Horizontal);
        PWM_method_label = new QLabel(centralWidget);
        PWM_method_label->setObjectName(QString::fromUtf8("PWM_method_label"));
        PWM_method_label->setGeometry(QRect(10, 300, 171, 20));
        PWM_method_combo = new QComboBox(centralWidget);
        PWM_method_combo->setObjectName(QString::fromUtf8("PWM_method_combo"));
        PWM_method_combo->setGeometry(QRect(190, 290, 201, 27));
        InfoTextEdit = new QPlainTextEdit(centralWidget);
        InfoTextEdit->setObjectName(QString::fromUtf8("InfoTextEdit"));
        InfoTextEdit->setGeometry(QRect(460, 280, 311, 271));
        QFont font;
        font.setPointSize(9);
        font.setItalic(true);
        font.setKerning(false);
        InfoTextEdit->setFont(font);
        InfoTextEdit->setUndoRedoEnabled(false);
        InfoTextEdit->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        XY_SF_label = new QLabel(centralWidget);
        XY_SF_label->setObjectName(QString::fromUtf8("XY_SF_label"));
        XY_SF_label->setGeometry(QRect(10, 450, 121, 17));
        XY_SF_value_label = new QLabel(centralWidget);
        XY_SF_value_label->setObjectName(QString::fromUtf8("XY_SF_value_label"));
        XY_SF_value_label->setGeometry(QRect(210, 450, 191, 21));
        Vibration_checkBox = new QCheckBox(centralWidget);
        Vibration_checkBox->setObjectName(QString::fromUtf8("Vibration_checkBox"));
        Vibration_checkBox->setGeometry(QRect(10, 260, 151, 22));
        Vibration_checkBox->setChecked(true);
        Connection_mode_combo = new QComboBox(centralWidget);
        Connection_mode_combo->setObjectName(QString::fromUtf8("Connection_mode_combo"));
        Connection_mode_combo->setGeometry(QRect(180, 10, 311, 27));
        Help = new QPushButton(centralWidget);
        Help->setObjectName(QString::fromUtf8("Help"));
        Help->setGeometry(QRect(780, 520, 31, 27));
        motor_ref0 = new QSlider(centralWidget);
        motor_ref0->setObjectName(QString::fromUtf8("motor_ref0"));
        motor_ref0->setGeometry(QRect(180, 180, 160, 29));
        motor_ref0->setMinimum(-5000);
        motor_ref0->setMaximum(5000);
        motor_ref0->setSingleStep(500);
        motor_ref0->setValue(0);
        motor_ref0->setOrientation(Qt::Horizontal);
        motor_ref1 = new QSlider(centralWidget);
        motor_ref1->setObjectName(QString::fromUtf8("motor_ref1"));
        motor_ref1->setGeometry(QRect(180, 210, 160, 29));
        motor_ref1->setMinimum(-5000);
        motor_ref1->setMaximum(5000);
        motor_ref1->setSingleStep(500);
        motor_ref1->setOrientation(Qt::Horizontal);
        motor0_ref_label = new QLabel(centralWidget);
        motor0_ref_label->setObjectName(QString::fromUtf8("motor0_ref_label"));
        motor0_ref_label->setGeometry(QRect(10, 180, 141, 17));
        motor1_ref_label = new QLabel(centralWidget);
        motor1_ref_label->setObjectName(QString::fromUtf8("motor1_ref_label"));
        motor1_ref_label->setGeometry(QRect(10, 210, 141, 17));
        Motor_ref_checkBox = new QCheckBox(centralWidget);
        Motor_ref_checkBox->setObjectName(QString::fromUtf8("Motor_ref_checkBox"));
        Motor_ref_checkBox->setGeometry(QRect(10, 150, 261, 22));
        Motor_ref_checkBox->setChecked(false);
        motor0_ref_value_label = new QLabel(centralWidget);
        motor0_ref_value_label->setObjectName(QString::fromUtf8("motor0_ref_value_label"));
        motor0_ref_value_label->setGeometry(QRect(360, 180, 61, 21));
        motor1_ref_value_label = new QLabel(centralWidget);
        motor1_ref_value_label->setObjectName(QString::fromUtf8("motor1_ref_value_label"));
        motor1_ref_value_label->setGeometry(QRect(360, 210, 61, 21));
        decrease_kp0 = new QPushButton(centralWidget);
        decrease_kp0->setObjectName(QString::fromUtf8("decrease_kp0"));
        decrease_kp0->setGeometry(QRect(250, 360, 31, 27));
        increase_kp0 = new QPushButton(centralWidget);
        increase_kp0->setObjectName(QString::fromUtf8("increase_kp0"));
        increase_kp0->setGeometry(QRect(210, 360, 31, 27));
        decrease_kp2 = new QPushButton(centralWidget);
        decrease_kp2->setObjectName(QString::fromUtf8("decrease_kp2"));
        decrease_kp2->setGeometry(QRect(250, 400, 31, 27));
        increase_kp2 = new QPushButton(centralWidget);
        increase_kp2->setObjectName(QString::fromUtf8("increase_kp2"));
        increase_kp2->setGeometry(QRect(210, 400, 31, 27));
        kp0_value_label = new QLabel(centralWidget);
        kp0_value_label->setObjectName(QString::fromUtf8("kp0_value_label"));
        kp0_value_label->setGeometry(QRect(300, 370, 61, 21));
        kp2_value_label = new QLabel(centralWidget);
        kp2_value_label->setObjectName(QString::fromUtf8("kp2_value_label"));
        kp2_value_label->setGeometry(QRect(300, 410, 61, 21));
        Vibration_gain_label_2 = new QLabel(centralWidget);
        Vibration_gain_label_2->setObjectName(QString::fromUtf8("Vibration_gain_label_2"));
        Vibration_gain_label_2->setGeometry(QRect(10, 370, 191, 20));
        Vibration_gain_label_3 = new QLabel(centralWidget);
        Vibration_gain_label_3->setObjectName(QString::fromUtf8("Vibration_gain_label_3"));
        Vibration_gain_label_3->setGeometry(QRect(10, 410, 191, 20));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "F.Y.D. - Phantom texture rendering application", 0, QApplication::UnicodeUTF8));
        actionCredits->setText(QApplication::translate("MainWindow", "Credits", 0, QApplication::UnicodeUTF8));
        actionCredits->setIconText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCredits->setToolTip(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        StartApp->setText(QApplication::translate("MainWindow", "Start Program", 0, QApplication::UnicodeUTF8));
        StatusLabel->setText(QApplication::translate("MainWindow", "Application status", 0, QApplication::UnicodeUTF8));
        Close->setText(QApplication::translate("MainWindow", "Exit Program", 0, QApplication::UnicodeUTF8));
        Pause_QB->setText(QApplication::translate("MainWindow", "Pause and get QB info", 0, QApplication::UnicodeUTF8));
        ShowImage->setText(QApplication::translate("MainWindow", "Show webcam image", 0, QApplication::UnicodeUTF8));
        IP_label->setText(QApplication::translate("MainWindow", "F.Y.D. connection mode:", 0, QApplication::UnicodeUTF8));
        SavePhantomButton->setText(QApplication::translate("MainWindow", "Save Phantom Log", 0, QApplication::UnicodeUTF8));
        ImageLabel->setText(QApplication::translate("MainWindow", "IMAGE", 0, QApplication::UnicodeUTF8));
        SaveAccelerationsButton->setText(QApplication::translate("MainWindow", "Save Accelerations Log", 0, QApplication::UnicodeUTF8));
        SeeOutput->setText(QApplication::translate("MainWindow", "See Output", 0, QApplication::UnicodeUTF8));
        increase_kvib->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        decrease_kvib->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        Vibration_gain_label->setText(QApplication::translate("MainWindow", "Vibration Gain:", 0, QApplication::UnicodeUTF8));
        Vibration_gain_value_label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        PWM_method_label->setText(QApplication::translate("MainWindow", "Vibration PWM method:", 0, QApplication::UnicodeUTF8));
        PWM_method_combo->clear();
        PWM_method_combo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "DFT321 (DFT 3-to-1)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "SoC (Sum of Components)", 0, QApplication::UnicodeUTF8)
        );
        InfoTextEdit->setPlainText(QApplication::translate("MainWindow", "Application Information", 0, QApplication::UnicodeUTF8));
        XY_SF_label->setText(QApplication::translate("MainWindow", "XY Scale Factor", 0, QApplication::UnicodeUTF8));
        XY_SF_value_label->setText(QApplication::translate("MainWindow", "1 mm FYD -> x mm robot", 0, QApplication::UnicodeUTF8));
        Vibration_checkBox->setText(QApplication::translate("MainWindow", "Vibration enabled", 0, QApplication::UnicodeUTF8));
        Connection_mode_combo->clear();
        Connection_mode_combo->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Ethernet network (on 192.168.0.100)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "FYD Touch Wireless network (on 10.42.0.1)", 0, QApplication::UnicodeUTF8)
        );
        Help->setText(QApplication::translate("MainWindow", "?", 0, QApplication::UnicodeUTF8));
        motor0_ref_label->setText(QApplication::translate("MainWindow", "Motor 1 Reference:", 0, QApplication::UnicodeUTF8));
        motor1_ref_label->setText(QApplication::translate("MainWindow", "Motor 2 Reference:", 0, QApplication::UnicodeUTF8));
        Motor_ref_checkBox->setText(QApplication::translate("MainWindow", "Change motor reference position", 0, QApplication::UnicodeUTF8));
        motor0_ref_value_label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        motor1_ref_value_label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        decrease_kp0->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        increase_kp0->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        decrease_kp2->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        increase_kp2->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        kp0_value_label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        kp2_value_label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        Vibration_gain_label_2->setText(QApplication::translate("MainWindow", "Horizontal movement Gain:", 0, QApplication::UnicodeUTF8));
        Vibration_gain_label_3->setText(QApplication::translate("MainWindow", "Vertical movement Gain:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
