$fa = 5;
bearing_inner_r = 44.6/2;
bearing_height = 7;

shaft_bearing_transition = 2;
shaft_inner_hole_r = 12;

top_bevel = 1;

difference()
{
    union() 
    {
        cylinder(h=3, r = bearing_inner_r + shaft_bearing_transition);
        cylinder(h=bearing_height+3-1, r = bearing_inner_r);
        translate([0,0,3+bearing_height-1]) cylinder(h=1, r1 = bearing_inner_r, r2 = bearing_inner_r-1);
    }

    translate([0,0,-1]) cylinder(h=bearing_height+3+2, r = shaft_inner_hole_r);
    
    for(zr = [ 0 : 45 : 360]) {
        rotate([0,0,zr]) translate([bearing_inner_r-4.5,0,-0.1]) m3_screw(11, 0.5, 32);
    }
    
    translate([0,0,-0.1]) cylinder(h=2, r1 = shaft_inner_hole_r+2 , r2= shaft_inner_hole_r);
}

module m3_screw(length, oversize, fn)
{
    cylinder($fn = fn, h = 3, r = (7 + oversize) / 2);
    cylinder($fn = fn, h = length, r = (3 + oversize) / 2);
}