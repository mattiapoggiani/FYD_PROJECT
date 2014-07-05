#include "../mainwindow.h"
#include "globals.h"
#include <QApplication>

extern int phantom_init(int, const char*, double);
extern int phantom_close();
extern bool gui_flag;

int main(int argc, char *argv[]) {
    double z0;
    unsigned int id;

    QApplication a(argc, argv);
    MainWindow w;

    if (!strcmp(argv[1], "-no_gui")){
        gui_flag = false;

        if (argv[2] && !strcmp(argv[2], "-z0") && argv[3]){
            z0 = atof(argv[3]);
            id = 4;
        }
        else {
            z0 = 0.0;
            id = 2;
        }

        // Parse program arguments
        if (argv[id]){
            if (!strcmp(argv[id], "-eth"))
                phantom_init(0, "", z0);
            else {
                if (!strcmp(argv[id], "-wifi"))
                    phantom_init(1, "", z0);
                else {
                    if (!strcmp(argv[id], "-ip") && argv[id+1])
                        phantom_init(2, argv[id+1], z0);
                    else {
                        cout << "Wrong arguments" << endl;
                        exit(1);
                    }
                }
            }
        }
        else {
            cout << "Usage: sudo ./FYD_PROJECT -no_gui [-z0 value] -eth|-wifi|-{ip address}" << endl;
            exit(1);
        }

        int c;

        cout << "F.Y.D. - Phantom texture rendering application" << endl << endl;
        cout << "Press 1 to decrease vibration gain" << endl;
        cout << "Press 2 to increase vibration gain" << endl;
        cout << "Press 3 to switch vibration method to DFT321" << endl;
        cout << "Press 4 to switch vibration method to SoC" << endl;
        cout << "Press 5 to obtain info on QB board and pause the program" << endl;
        cout << "Press 6 to restart the paused program" << endl;
#ifndef KUKA
        cout << "Press 7 to begin to send image" << endl;
        cout << "Press 8 to stop to send image" << endl;
#endif
        cout << "Press A to set new motor reference" << endl;
        cout << "Press 9 or ESC key to quit" << endl;

        while (!_kbhit() && c != 0x1B){	// Close program if ESC key is pressed
            c = getch();

            // This part of code is executed only when a key is pressed
            switch (c){
                case '1':  cmd = 1;
                           cout << endl << "Vibration gain decreased" << endl;
                           break;
                case '2':  cmd = 2;
                           cout << endl << "Vibration gain increased" << endl;
                           break;
                case '3':  cmd = 3;
                           cout << endl << "Vibration method switched to DFT321" << endl;
                           break;
                case '4':  cmd = 4;
                           cout << endl << "Vibration method switched to SoC" << endl;
                           break;
                case '5':  cmd = 5;
                           cout << endl << "Program paused. Press 6 to to restart" << endl;
                           break;
                case '6':  cmd = 6;
                           break;
                case '7':  cmd = 7;
                           cout << endl << "Start sending image" << endl;
                           break;
                case '8':  cmd = 8;
                           cout << endl << "Stop sending image" << endl;
                           break;
                case '9': case 0x1B:
                           cmd = 9;
                           break;
                case 'A': case 'a': {
                            int ar = 0;
//                          cout << "Motor 1 reference: ";
//                          scanf("%i", &ar);
//                          cout << "AR: " << ar << endl;
//                          cout << "Motor 2 reference: ";
//                          scanf("%hi\n", &ref[1]);
//                          cmd = 10;
                            cout << "Function not enabled " << endl;
                           break;
                }
                default:
                           break;
            }
            if (c == 0x1B || c == '9')
                break;
            c = 0;
        }
        return phantom_close();
    }
    else {
#ifndef KUKA
      gui_flag = true;
      QApplication a(argc, argv);
      MainWindow w;
      w.show();
      return a.exec();
#else
      cout << "GUI not available when using KUKA robot" << endl;
      cout << "Please specify '-no_gui' option before network connection mode" << endl;
      return 1;
#endif
   }
}

