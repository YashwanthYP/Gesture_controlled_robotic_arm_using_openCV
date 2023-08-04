import cv2
import cvzone.SerialModule
from cvzone.HandTrackingModule import HandDetector

cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1, detectionCon=0.8)
mySerial = cvzone.SerialModule.SerialObject("COM4",9600,1)
while True:
    success,img = cap.read()
    hands,img = detector.findHands(img)



    if hands:
        hand1 = hands[0]
        lmList1 = hand1["lmList"]
        bbox1 = hand1["bbox"]
        centerPoint1 = hand1["center"]
        handType1 = hand1["type"]
        fingers1 = detector.fingersUp(hand1)
        print(fingers1)
        mySerial.sendData(fingers1)

        cv2.imshow("Image",img)
        cv2.waitKey(1)
