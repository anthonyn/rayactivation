ArrayList<Shape> shapes;

void setup() {
  size(800, 600, P3D);

  shapes = new ArrayList<Shape>();
  shapes.add(new Pole());
  shapes.add(new Sphere());
}


void draw() {
  background(0);

  lights();

  camera(  width/2, height/2, mouseY, 
    width/2, height/2, 0.0, 
    0.0, 1.0, 0.0);
    
  noStroke();
  for (Shape s : shapes) {
    s.update();
  }
  
  println(mouseY);
}