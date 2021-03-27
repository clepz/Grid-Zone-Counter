from PyQt5 import QtCore, QtGui, QtWidgets
import os

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
        self.saveMapButton = QtWidgets.QPushButton(self.centralwidget)
        self.saveMapButton.setGeometry(QtCore.QRect(1090, 900, 111, 31))
        self.saveMapButton.setObjectName("pushButton")
        self.saveMapButton.clicked.connect(self.saveMap)
        self.widthEditText = QtWidgets.QLineEdit(self.centralwidget)
        self.widthEditText.setGeometry(QtCore.QRect(10, 910, 51, 21))
        self.widthEditText.setObjectName("lineEdit")
        self.heightEditText = QtWidgets.QLineEdit(self.centralwidget)
        self.heightEditText.setGeometry(QtCore.QRect(80, 910, 51, 21))
        self.heightEditText.setObjectName("lineEdit_2")
        self.saveFileNameEditText = QtWidgets.QLineEdit(self.centralwidget)
        self.saveFileNameEditText.setGeometry(QtCore.QRect(950, 900, 121, 31))
        self.saveFileNameEditText.setObjectName("lineEdit_3")
        self.loadFileNameEditText = QtWidgets.QLineEdit(self.centralwidget)
        self.loadFileNameEditText.setGeometry(QtCore.QRect(950, 950, 121, 31))
        self.loadFileNameEditText.setObjectName("lineEdit_4")
        self.widthLabel = QtWidgets.QLabel(self.centralwidget)
        self.widthLabel.setGeometry(QtCore.QRect(10, 890, 57, 15))
        self.widthLabel.setObjectName("label")
        self.heightLabel = QtWidgets.QLabel(self.centralwidget)
        self.heightLabel.setGeometry(QtCore.QRect(80, 890, 57, 15))
        self.heightLabel.setObjectName("label_2")
        self.loadMapButton = QtWidgets.QPushButton(self.centralwidget)
        self.loadMapButton.setGeometry(QtCore.QRect(1090, 950, 111, 31))
        self.loadMapButton.setObjectName("pushButton_2")
        self.loadMapButton.clicked.connect(self.loadMap)
        self.newMapButton = QtWidgets.QPushButton(self.centralwidget)
        self.newMapButton.setGeometry(QtCore.QRect(10, 940, 111, 31))
        self.newMapButton.setObjectName("pushButton_3")
        self.newMapButton.clicked.connect(self.newMap)
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
        self.saveMapButton.setText(_translate("MainWindow", "Save Map"))
        self.widthLabel.setText(_translate("MainWindow", "width"))
        self.heightLabel.setText(_translate("MainWindow", "height"))
        self.loadMapButton.setText(_translate("MainWindow", "Load Map"))
        self.newMapButton.setText(_translate("MainWindow", "New Map"))

    def newMap(self):
        for i in reversed(range(self.gridLayout.count())): 
            self.gridLayout.itemAt(i).widget().setParent(None)
        self.width = int(self.widthEditText.text()) + 2 
        self.height = int(self.heightEditText.text()) + 2
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
        path = os.path.dirname(os.path.abspath(__file__))
        string = ""
        filename = self.saveFileNameEditText.text() if self.saveFileNameEditText.text() != "" else path + "/../maps/map.txt"
        for i in range(self.height):
            for y in range(self.width):
                cell = self.cellList[i*self.width + y]
                string += str(cell.value) + ","
        with open(filename,"w") as f:
            f.write("{},{}\n".format(self.width,self.height))
            f.write(string[:-1])

    def loadMap(self):
        values = None
        filename = self.loadFileNameEditText.text() if self.loadFileNameEditText.text() != "" else "map.txt"
        with open(filename,"r") as f:
            line = f.readline()
            array = line.split(",")
            self.width = int(array[0])
            self.height = int(array[1])
            values = f.readline().split(",")

        if values is not None:
            self.newMapFromTxt(values)

