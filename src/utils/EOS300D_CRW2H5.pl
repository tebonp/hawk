#!/usr/bin/perl 

use File::Basename;

$dir = dirname($ARGV[0]);
chdir($dir);
print "Chaging dir to $dir\n";
$crw_file = basename($ARGV[0]);
#$crw_file = ($ARGV[0]);
$crw_file =~ m/(.*)\.cr[w2]/i;
$base = $1;
$tif = "$base".".tiff";
$ppm = "$base".".pgm";
$raw_h5 = "Raw_"."$base".".h5";
$red_h5 = "Red_"."$base".".h5";
$red_png = "Red_"."$base".".png";
$green_h5 = "Green_"."$base".".h5";
$green_png = "Green_"."$base".".png";
mkdir("$base");
chdir("$base");
print("dcraw -D -T -4../$crw_file...");
system("dcraw -D -T -4 ../$crw_file");
system("mv ../$tif .");
print("done\n");
#print("convert $ppm $tif...");
#system("convert $ppm $tif");
#print("done\n");
print("tiff2h5 -i $tif -o $raw_h5...");
system("tiff2h5 -l 1 -p 1 -d 1 -i $tif -o $raw_h5");
print("done\n");
#print("separate_channel $raw_h5 R $red_h5...");
#system("separate_channel $raw_h5 R $red_h5");
#print("done\n");
print("separate_channel $raw_h5 G $green_h5...");
system("separate_channel $raw_h5 G $green_h5");
print("done\n");
#print("autocorrelate $red_h5..."); 
#system("autocorrelate $red_h5"); 
#print("done\n");
#print("autocorrelate $green_h5..."); 
#system("autocorrelate $green_h5"); 
print("done\n");
