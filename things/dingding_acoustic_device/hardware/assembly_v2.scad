include <dingding_ring_pillar.scad>

include <bar.scad>

translate([0,0,150/2]) ring();

translate([0,0,-150/2]) ring();

translate([0,0,(150/2)-10]) bearingAssembly();

translate([0,0,-((150/2)-10)]) rotate([0,180,0]) bearingAssembly();

bar_pillar_slot_dist = 5;

outer_radius = 160;

for(i=[1:24])
{
    rotate([0,0,(360/24)*i]) translate([outer_radius - bar_pillar_slot_dist - 5,0,0]) pillarGroup();
    
    // bar sizes
    // min 78mm
    // max 155
    // width 25mm
    rotate([0,0,(360/24)*i]) translate([outer_radius + 10,0,0]) bar(78+(3.2*i));
}

module ring()
{
    include <dingding_ring_v2.scad>
}

module pillarGroup()
{
    translate([0,5,0]) rotate([90,0,0]) pillar();
    translate([0,-5,0]) rotate([90,0,0]) pillar();
}

module bearingAssembly()
{
    include <dd_shaft_bearing_housing_v2.scad>;
    
    // include <dd_shaft_bearing_clamp.scad>;
    
    
    translate([0,0,10]) bearingClamp();
}

module bearingClamp()
{
    // include <dd_shaft_bearing_clamp_outer.scad>
}
