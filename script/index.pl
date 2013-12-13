#!/usr/bin/perl
use strict;
use warnings;
     
my %count;
my $file = shift or die "Usage: $0 FILE\n";
open my $fh, '<', $file or die "Could not open '$file' $!";
while (my $line = <$fh>) {
	chomp $line;
	$line = lc($line);
	$line =~ s/[[:punct:]]//g;
	foreach my $str (split /\s+/, $line) {
	
		$count{$str}++;
	}
}
my $file1 = $ARGV[0];
open my $of, ">", $file1;
foreach my $str (sort keys %count) {
	print{$of} $str, "	$count{$str}\n";
}
close $of;
close $file;

