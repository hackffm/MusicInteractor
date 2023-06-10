bars = 24;
bar_width = 20;

bar_pillar_slot_dist = 5;

bearing_hole_radius = 53/2;

outer_radius = 160;


bearing_diameter = 58.4;
bearing_radius = bearing_diameter/2;
mount_width = 15;
mount_screwhole_radius = 3.5/2;



difference()
{

    union()
    {
        difference()
        {
            circle($fn=360, r=outer_radius);
            circle($fn=360, r=bearing_hole_radius);
            // translate([0,0,-1]) cylinder($fn=360, h=22, r=150);
        }
        
    }

    for(i = [1 : bars])
    {
        rotate([0,0, (360/bars)*i]) translate([outer_radius - bar_pillar_slot_dist - 10,0,0]) blockSlot();
    }
    
    rotate([0,0,0]) for(i = [1 : 6])
    {
        rotate([0,0,(360/6)*i]) translate([(outer_radius - bearing_hole_radius/2)/2+bearing_hole_radius,0,0]) circle($fn = 32, r=4);
    }
    
    // screw holes
    
    for(rz = [0: 45 : 360])
    {
        rotate([0,0,rz]) translate([bearing_radius+(mount_width / 2),0,0]) circle( r = mount_screwhole_radius );
    }
}





module blockSlot() {
    translate([5,2+5,0]) square([10,4], center=true);
    translate([5,-(2+5),0]) square([10,4], center=true);
}


