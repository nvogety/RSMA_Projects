// Written with the p5.js library
// Simulates the Webb - clicking on a point creates a ripple that is sensed by a reciever,
// 	and the reciever will point in the direction it thinks it came from
// Rippling Circle logic adapted from "ripple w/ for loop" by chjno
// drawArrow() from p5 docs

var outerDiam = 0;
var startDrawing = false;
var recieverX = 300;
var recieverY = 500;
var recieverDiam = 75;
var recieverRad = recieverDiam / 2;
var recieveXMin  = recieverX - recieverRad;
var recieveXMax  = recieverX + recieverRad;
var recieveYMin  = recieverY - recieverRad;
var recieveYMax  = recieverY + recieverRad;

function setup() { 
  createCanvas(600, 600);
  strokeWeight(2);
  colorMode(HSB);
  textFont('Helvetica');
} 

function draw() { 
  background(255);
  
  
  strokeWeight(2);
  if(mouseIsPressed){
    startDrawing = true;
    outerDiam = 0;
    xCoord = mouseX
    yCoord = mouseY
  }
  
  if(startDrawing){
    for (var i = 0; i < 5; i++){
          var diam = outerDiam - 30 * i;    
      if (diam > 0){
        var h = map(diam, 0, width, 0, 50);
        var s = map(diam, 0, width, 100, 0);
        stroke(h,s,100);
        noFill();
        ellipse(xCoord, yCoord, diam);
        
        var rad = diam / 2;
        var xInRange = (recieveXMin <= xCoord + rad  && xCoord + rad <= recieveXMax) || (recieveXMin <= xCoord - rad  && xCoord - rad <= recieveXMax);
        var yInRange = (recieveYMin <= yCoord + rad  && yCoord + rad <= recieveXMax) || (recieveYMin <= yCoord - rad  && yCoord - rad <= recieveXMax);
        if(xInRange || yInRange){
          var v0 = createVector(recieverX, recieverY);
          var v1 = createVector(xCoord - recieverX, yCoord - recieverY);
          v1.normalize();
          drawArrow(v0, v1.mult(recieverRad), 'blue');
        }
      }
    }
  }

  stroke(0);
  ellipse(recieverX, recieverY, recieverDiam);
  noFill();
  
  textSize(16);
  strokeWeight(0.5);
  text('The Webb', 10, 30);
  
  textSize(12);
  strokeWeight(0.5);
  text('Reciever', recieverX - (2*recieverRad/3), recieverY+(3*recieverRad/2));
  
  outerDiam = outerDiam + 2;
}

function drawArrow(base, vec, myColor) {
  push();
  stroke(myColor);
  strokeWeight(3);
  fill(myColor);
  translate(base.x, base.y);
  line(0, 0, vec.x, vec.y);
  rotate(vec.heading());
  let arrowSize = 7;
  translate(vec.mag() - arrowSize, 0);
  triangle(0, arrowSize / 2, 0, -arrowSize / 2, arrowSize, 0);
  pop();
}
