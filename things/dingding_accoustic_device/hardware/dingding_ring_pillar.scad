// pillar();
module pillar()
{
    difference()
    {
        union()
        {
            square([30,150], center = true);
            square([10,166], center = true);
        }
        
        hull() {
            translate([0,20,0]) circle(1.6);
            translate([0,60,0]) circle(1.6);
        }
        
        rotate([0,0,180]) hull() {
            translate([0,20,0]) circle(1.6);
            translate([0,60,0]) circle(1.6);
        }
    }
}