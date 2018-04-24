class Pole implements Shape {
  
  int x,y,z;
  
  Pole() {
    x = 10;
    y = 200;
    z = 10;
    
  }

  void update() {
    pushMatrix();
    //translate to center of screen
    translate(width/2, height/2 + (.5 * y), 0);
    box(x, y, z);
    popMatrix();
  }
}