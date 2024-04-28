import cv2

# haarcascade frontface default
harcascade = "model/haarcascade_frontalface_default.xml"

# open camera
cap = cv2.VideoCapture(0)

# set the camera Windows
cap.set(3, 640)  # width
cap.set(4, 480)  # height

# load the haarcascade 
facecascade = cv2.CascadeClassifier(harcascade)

while True:
    success, img = cap.read()

    # convert rgb image to grayscale image
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # apply face detection
    faces = facecascade.detectMultiScale(img_gray, 1.1, 4)

    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)

    cv2.imshow("Face", img)

    # Code for close the camera
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
