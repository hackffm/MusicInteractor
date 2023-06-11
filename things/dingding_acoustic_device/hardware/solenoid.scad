
translate([-7,0,-16/2]) union()
{    
    difference()
    {
        translate([30/2,0,0]) cube([30,14,16], center = true);
        translate([7,0,0]) cylinder($fn= 8, h=20, r=2.5/2);
        translate([7+17,0,0]) cylinder($fn= 8, h=20, r=2.5/2);
    }

    rotate([0,-90,0]) cylinder($fn= 8, h=8, r=5/2);
    rotate([0,-90,0]) translate([0,0,8]) cylinder($fn= 8, h=8, r=1/2);
}