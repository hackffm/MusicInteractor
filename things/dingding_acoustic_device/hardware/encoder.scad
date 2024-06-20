$fa = 0.5;
outer = 120;
inner = 100;

encoderRing(outer,inner,48*6);

encoderRing(outer-20,inner-10,48*1);

circleSegment(outer-20, inner-10, 360/(48));

module encoderRing(outer,inner,count) {
    segmentStepAngle = 360 / count;
    segmentAngle = segmentStepAngle/2;
    echo(segmentStepAngle);
    echo(segmentAngle);
    for(phi=[0:segmentStepAngle:360]) {
        rotate([0,0,phi]) circleSegment(outer,inner,segmentAngle);
    }
}

module circleSegment(outer, inner, segmentAngel) {
    intersection() {
        cake(segmentAngel,0.01,outer+10);
        difference() {
            circle(outer);
            circle(inner);
        }
    }
}



module cake(angel,angel_steps,radius) {
    p0 = [ for(phi=[0:angel_steps:angel]) [sin(phi)*radius,cos(phi)*radius] ];
    p_final = concat([[0,0]],p0);
    polygon(p_final);
}