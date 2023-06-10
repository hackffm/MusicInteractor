$fa = 1;
bearing_height = 7;
bearing_diameter = 58.4;

beargin_608ZZ_diamter = 22; // 8x22x7

beargin_608ZZ_radius = beargin_608ZZ_diamter/2;

bearing_radius = bearing_diameter/2;
bearing_radius_edge = (beargin_608ZZ_diamter/2)-3;
mount_width = 15;
mount_radius = bearing_radius + mount_width ;
mount_screwhole_radius = 3.5/2;

difference() 
{
    cylinder(h = bearing_height + 3, r = mount_radius);
    translate([0,0,3]) cylinder(h = bearing_height+0.01, r = beargin_608ZZ_radius);
    
    for(rz = [0: 45 : 360])
    {
        rotate([0,0,rz]) translate([bearing_radius+(mount_width / 2),0,-0.1]) cylinder($fn = 32, h = 20, r = mount_screwhole_radius );
    }
    
    translate([0,0,-0.1]) cylinder(h = 20, r = bearing_radius_edge);
    
    translate([0,0,bearing_height +  3 - 0.99]) cylinder(h = 1, r1 = beargin_608ZZ_radius, r2 = beargin_608ZZ_radius+1);
}

