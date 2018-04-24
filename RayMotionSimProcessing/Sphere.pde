class Sphere implements Shape{
  int sphereSize;
  float theta;
  float addVal;
  float yTranslate;



  Sphere() {
    sphereSize = 15;
    theta = 0;
    addVal =0.01;
    yTranslate = 150;
  }

  void update() {

    theta = (theta + addVal) % 180;

    pushMatrix();

    //translate to center of screen
    translate(width/2, height/2, 0);

    //move around the y axis, spin
    rotateY(theta);
    
    // move out some distanc eon the x axis and draw teh box
    translate(yTranslate, 0, 0);

    sphere(sphereSize);

    popMatrix();
  }
}