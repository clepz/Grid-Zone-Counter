from ui import Ui_MainWindow
from PyQt5 import QtCore, QtGui, QtWidgets
import sys


if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    window = QtWidgets.QMainWindow()
    creator = Ui_MainWindow()
    creator.setupUi(window)
    window.show()
    app.exec_()

    