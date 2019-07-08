import sys
import re
from PyQt5.QtWidgets import QApplication, QWidget, QCheckBox, QLabel, QLineEdit
from PyQt5.QtCore import Qt


class MyApp(QWidget):

    def __init__(self):
     super().__init__()
     self.text = ''
     self.initUI()

    def initUI(self):
#check box
     self.cb1 = QCheckBox('apple ', self)
     self.cb1.move(20, 20)
	
     self.cb2 = QCheckBox('banana ', self)
     self.cb2.move(20, 40)
    
     self.cb3 = QCheckBox('orange ', self)
     self.cb3.move(20, 60)

     self.cb1.stateChanged.connect(self.changeLedit1)
     self.cb2.stateChanged.connect(self.changeLedit2)
     self.cb3.stateChanged.connect(self.changeLedit3)
     self.setGeometry(300, 300, 300, 200)

#lineEdit
     self.qle = QLineEdit(self)
     self.qle.move(60, 100)
     self.show()
    
    def changeLedit1(self, state):
     if self.cb1.isChecked() == True:
      self.text += self.cb1.text()
     else :
      self.text = re.sub(self.cb1.text(),'', self.text)
     self.Ledit()

    def changeLedit2(self, state):
     if self.cb2.isChecked() == True:
      self.text += self.cb2.text()
     else : 
      self.text = re.sub(self.cb2.text(),'', self.text)
     self.Ledit()

    def changeLedit3(self, state):
     if self.cb3.isChecked() == True:
      self.text += self.cb3.text()
     else :
      self.text = re.sub(self.cb3.text(),'', self.text)
     self.Ledit()

    def Ledit(self) :
     self.qle.setText(self.text)
     self.qle.adjustSize()

if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())
