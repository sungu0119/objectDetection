import sys
from PyQt5.QtWidgets import QApplication, QWidget, QCheckBox, QLabel, QLineEdit
from PyQt5.QtCore import Qt


class MyApp(QWidget):

    def __init__(self):
     super().__init__()

     self.initUI()
    

    def initUI(self):
#check box
     self.cb1 = QCheckBox('apple ', self)
     self.cb1.move(20, 20)
	
     self.cb2 = QCheckBox('banana ', self)
     self.cb2.move(20, 40)
    
     self.cb3 = QCheckBox('orange ', self)
     self.cb3.move(20, 60)
# cb.toggle()
     self.cb1.stateChanged.connect(self.changeLedit)
     self.cb2.stateChanged.connect(self.changeLedit)
     self.cb3.stateChanged.connect(self.changeLedit)
     self.setGeometry(300, 300, 300, 200)

     

#lineEdit
     self.qle = QLineEdit(self)
     self.qle.move(60, 100)
     self.show()

    def changeLedit(self, state):
     text = ''

     if self.cb1.isChecked() == True:
      text += self.cb1.text()
     else:
      text.lstrip(self.cb1.text()) 

     if self.cb2.isChecked() == True:
      text += self.cb2.text()
     else:
      text.lstrip(self.cb2.text()) 

     if self.cb3.isChecked() == True:
      text += self.cb3.text()
     else:
      text.lstrip(self.cb3.text()) 

     self.qle.setText(text)
     self.qle.adjustSize()

if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = MyApp()
    sys.exit(app.exec_())
