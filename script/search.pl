#!/usr/bin/perl

my $keyword = $ARGV[0];
my %count;
my $file = "indexfile.txt" or die;
open my $fh, '<',$file or die "Could not open '$file' $!";
while (my $line = <$fh>) {
	chomp $line;
	my $file2 = $line;
	
	open my $fh2, '<',$file2 or die "Could not open '$file2' $!";
	while (my $line2 = <$fh2>) {
		chomp $line2;
		my($ID, $values)= split(/\s+/, $line2);
		if( $ID eq $keyword){
			my($aa,$ab) = split(/\//,$file2);
			my $str = $keyword;
			$count{$ab} = $values;
		}
	}
}

my $ofile = "tmp";
open my $of, ">" , $ofile;
foreach my $str (sort {$count{$b} <=> $count{$a}} keys %count)
{
	#printf "$str, $count{$str}\n";
	print{$of} <$str,",$count{$str}>->";
} 
close $of;
close $fh;
