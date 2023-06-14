solenoid_count = 24;
solenoid_count_total = 24;

ring_outer_radius = 120;
bar_top_dist_to_ring_outer = 23;

solenoid_tip_to_first_mount_hole = 16;

solenoid_mount_holes_dist = 25;

solenoid_swing_dist = 8;

solenoid_solenoid_spacing = 3;

solenoid_holder_ring = ring_outer_radius+bar_top_dist_to_ring_outer+solenoid_solenoid_spacing;

holder_widht = 50;

difference() 
{
    union()
    {
        circle($fa = 1, r=solenoid_holder_ring+holder_widht);
    
        rotate([0,0,((360/24)/2)*0]) for(i=[0:45:360])
        {
            rotate([0,0,i]) translate([solenoid_holder_ring+holder_widht,0,0]) circle($fn=32, r=16);
        }
    }
    circle($fa = 1, r=solenoid_holder_ring);
    
    for(i=[1:24])
    {
        rotate([0,0,(360/solenoid_count_total)*i]) translate([155,0,0]) solenoid_pcb_hole();
    }
    
    rotate([0,0,((360/24)/2)*3]) for(i=[0:45:360])
    {
        rotate([0,0,i]) translate([170,0,0]) pillarMounting();
    }
    
    rotate([0,0,((360/24)/2)*0]) for(i=[0:45:360])
    {
        rotate([0,0,i]) translate([solenoid_holder_ring+holder_widht,0,0]) circle($fn=32, r=4);
    }
}

module pillarMounting()
{
    translate([-15,0,0]) circle(r=3/2);
    translate([15,0,0]) circle(r=3/2);
    square([10,3], center = true);
}

module solenoid_pcb_hole()
{
    translate([0,-5,0]) circle($fn =16, r = 0.5);
    translate([0,5,0]) circle($fn =16, r = 0.5);
}



for(i=[1:solenoid_count_total])
{   
    // rotate([0,0,(360/solenoid_count_total)*i]) translate([163,0,0]) rotate([180,0,0]) solenoid();
}

module solenoid()
{
    include <solenoid.scad>
}
