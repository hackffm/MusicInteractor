solenoid_count = 24;

ring_outer_radius = 120;
bar_top_dist_to_ring_outer = 23;

solenoid_tip_to_first_mount_hole = 16;

solenoid_mount_holes_dist = 35;

solenoid_swing_dist = 8;

solenoid_solenoid_spacing = 5;

solenoid_holder_ring = ring_outer_radius+bar_top_dist_to_ring_outer+solenoid_solenoid_spacing;

holder_widht = 55;

difference() 
{
    circle($fa = 1, r=solenoid_holder_ring+holder_widht);
    circle($fa = 1, r=solenoid_holder_ring);
    
    for(i=[1:24])
    {
        rotate([0,0,(360/24)*i]) translate([solenoid_holder_ring+5,0,0]) solenoid_mount_hole_slot(solenoid_mount_holes_dist);
    }
}

module solenoid_mount_hole_slot(slot_length)
{
    hull() 
    {
        circle($fn =16, r = 2.5/2);
        translate([slot_length,0]) circle($fn =16, r = 2.5/2);
    }
}