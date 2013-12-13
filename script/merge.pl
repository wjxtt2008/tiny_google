my $file1 = $ARGV[0];
my $file2 = $ARGV[1];

open(first_file,'<', $file1) or die $!;
my @FILE1 = <first_file>;
close(first_file);

open(sec_file,'<', $file2) or die $!;
my @FILE2 = <sec_file>;
close(sec_file);

my %count;

for my $sec_line(@FILE2){
		chomp $sec_line;
                my($ID2, $values2) = split(/\s+/, $sec_line);
		my $str = $ID2;
		$count{$str} = $values2;
}

for my $line(@FILE1){
	chomp $line;
        my($ID, $values) = split(/\s+/, $line);
        for my $sec_line(@FILE2){
		$flag = 0;
		chomp $sec_line;
                my($ID2, $values2) = split(/\s+/, $sec_line);
		
		if($ID lt $ID2){
			$str = $ID;
			$count{$str}=$values;
			$flag =1 ;
			last;
		}
                elsif($ID eq $ID2){
			$total_val = $values+$values2;
			$str = $ID;
			$count{$str}=$total_val;		
			$flag = 1;
			last;
                }
        }
	if($flag ==0 ) {
	$count{$ID} = $values;
	}
}
my $ofile = $ARGV[2];
open my $of, ">", $ofile;
foreach my $str (sort keys %count) {
	print{$of} $str, "	$count{$str}\n";
}

close $of;

