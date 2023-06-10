difference() {
    cube([10,30,8]);
    translate([-1,5,4]) rotate([0,90,0])cylinder($fn = 32, h=12, r = 3.5/2);
    
    translate([5,31,4]) rotate([90,0,0])cylinder($fn = 32, h=15, r = 3/2);
}
