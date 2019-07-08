from PyQt5.QtCore import QTime, QTimer
from PyQt5.QtWidgets import QApplication, QLCDNumber


class DigitalClock(QLCDNumber):
    def __init__(self, parent=None):
     super(DigitalClock, self).__init__(parent)

     self.setSegmentStyle(QLCDNumber.Filled)

     timer1 = QTimer(self)
     timer1.timeout.connect(self.showTime)
     timer1.start(1000)

     self.showTime()

     self.setWindowTitle("Digital Clock")
     self.resize(350, 60)

    def showTime(self):
     time = QTime.currentTime()
     text = time.toString('hh:mm:ss')
     
     if (time.second() % 1) == 0:
      text = text[:2] + text[2:4]+ text[4: ] 
      
      self.display(text)


if __name__ == '__main__':
    
    import sys

    app = QApplication(sys.argv)
    clock = DigitalClock()
    clock.show()
    sys.exit(app.exec_())
