$fn = 64;



difference(){
    roundedRect(15, 200, 200);
    
    translate([200/2,-10]) text("dingDing", font = "Ruler Stencil:style=Regular" , size=30, halign="center", valign="top", spacing=0.9);
    
    translate([35,-55]) text("MK-ll", font = "Ruler Stencil:style=Bold" , size=10, halign="left", valign="top", spacing=1);
    
    translate([30,-90]) rotate([0,180,90]) pcbBigHoles();
    translate([150,-85]) pcbSlimHoles();
    
    hull() {
        translate([30,-180]) circle(r=6);
        translate([200-30,-180]) circle(r=6);
    }
    
    translate([10,-100]) circle(r=2.2);
    translate([200-10,-100]) circle(r=2.2);
    
    makeHoles(radius=10, fn=8, [[20,-30],[30,-40]]);
}

module makeHoles(radius=1, fn=8, positions=[[30,-40]])
{
    echo(len(positions));
    for(i=[0:1:len(positions)-1])
    {
        echo(positions[i]);
        translate(positions[i]) circle($fn=fn, r=radius);
    }
}

module roundedRect(radius, width, height)
{
    hull() {
        translate([radius,-radius]) circle(r=radius);
        translate([width-radius,-radius]) circle(r=radius);
        translate([width-radius,-height+radius]) circle(r=radius);
        translate([radius,-height+radius]) circle(r=radius);
    }
}


module pcbBigHoles() {
    circle($fn=8, r=1);
    translate([65,0]) circle($fn=8, r=1);
    translate([65,-85]) circle($fn=8, r=1);
    translate([0,-85]) circle($fn=8, r=1);
}


module pcbSlimHoles() {
    circle($fn=8, r=1);
    translate([16,0]) circle($fn=8, r=1);
    translate([16,-75.5]) circle($fn=8, r=1);
    translate([0,-75.5]) circle($fn=8, r=1);
}