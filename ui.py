# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mapcreator.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class CellWidget(QtWidgets.QWidget):
    def __init__(self, value):
        super(CellWidget,self).__init__(parent=None)
        if type(value) is str:
            value = int(value)
        self.value = value
        if (self.value == -1):
            self.setStyleSheet("background-color: rgb(0, 0, 0);")
        else:
            self.setStyleSheet("background-color: rgb(255, 255, 255);")
    def mouseReleaseEvent(self,event):
        self.value = -1 if self.value == 0 else 0
        if (self.value == -1):
            self.setStyleSheet("background-color: rgb(0, 0, 0);")
        else:
            self.setStyleSheet("background-color: rgb(255, 255, 255);")

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1211, 1032)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(3, 3, 1211, 871))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(1090, 900, 111, 31))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.saveMap)
        self.lineEdit = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit.setGeometry(QtCore.QRect(10, 910, 51, 21))
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(self.centralwidget)
        self.lineEdit_2.setGeometry(QtCore.QRect(80, 910, 51, 21))
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(10, 890, 57, 15))
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(self.centralwidget)
        self.label_2.setGeometry(QtCore.QRect(80, 890, 57, 15))
        self.label_2.setObjectName("label_2")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(1090, 950, 111, 31))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.loadMap)
        self.pushButton_3 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_3.setGeometry(QtCore.QRect(10, 940, 111, 31))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_3.clicked.connect(self.newMap)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1211, 20))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.width = 0
        self.height = 0

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "Save Map"))
        self.label.setText(_translate("MainWindow", "width"))
        self.label_2.setText(_translate("MainWindow", "height"))
        self.pushButton_2.setText(_translate("MainWindow", "Load Map"))
        self.pushButton_3.setText(_translate("MainWindow", "New Map"))

    def newMap(self):
        for i in reversed(range(self.gridLayout.count())): 
            self.gridLayout.itemAt(i).widget().setParent(None)
        self.width = int(self.lineEdit.text()) + 1 
        self.height = int(self.lineEdit_2.text()) + 1
        self.cellList = []
        for i in range(self.height):
            for y in range(self.width):
                cellWidget = None
                if i == 0 or i == self.height -1 or y == 0 or y == self.width -1:
                    cellWidget = CellWidget(-1)
                else:
                    cellWidget = CellWidget(0)
                cellWidget.setAttribute(QtCore.Qt.WA_StyledBackground, True)
                cellWidget.autoFillBackground = True
                cellWidget.setGeometry(QtCore.QRect(720, 20, 80, 80))
                self.gridLayout.addWidget(cellWidget,i,y)
                self.cellList.append(cellWidget)
        self.gridLayout.setHorizontalSpacing(5)
        self.gridLayout.setVerticalSpacing(5)

    def newMapFromTxt(self, values):
        for i in reversed(range(self.gridLayout.count())): 
            self.gridLayout.itemAt(i).widget().setParent(None)
        self.cellList = []
        for i in range(self.height):
            for y in range(self.width):
                cellWidget = CellWidget(values[i*self.width + y])
                cellWidget.setAttribute(QtCore.Qt.WA_StyledBackground, True)
                cellWidget.autoFillBackground = True
                cellWidget.setGeometry(QtCore.QRect(720, 20, 80, 80))
                self.gridLayout.addWidget(cellWidget,i,y)
                self.cellList.append(cellWidget)
        self.gridLayout.setHorizontalSpacing(5)
        self.gridLayout.setVerticalSpacing(5)

    def saveMap(self):
        string = ""
        for i in range(self.height):
            for y in range(self.width):
                cell = self.cellList[i*self.width + y]
                string += str(cell.value) + ","
        with open("map.txt","w") as f:
            f.write("{},{}\n".format(self.width,self.height))
            f.write(string[:-1])

    def loadMap(self):
        values = None
        with open("map.txt","r") as f:
            line = f.readline()
            array = line.split(",")
            self.width = int(array[0])
            self.height = int(array[1])
            values = f.readline().split(",")

        if values is not None:
            self.newMapFromTxt(values)

