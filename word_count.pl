#!/usr/bin/perl   -w
$filename = $ARGV[0];

open(FP,"$filename"); 
my (%word,@word_array);

while (<FP>)
{
	s/,|\.//g;
	@temp_array=split(/\s+/);
	push @word_array,@temp_array;
}

foreach (@word_array)
{
	unless($word{$_}) {
		$word{$_} = 1;
		next;
	}
	$word{$_}++;
}


open(my $outfile, '>', $ARGV[1]);

foreach my $key (sort { lc($a) cmp lc($b) } keys %word) {
	# print $key . "  ";
	# print $word{$key} . "\n";

	print $outfile $key . "  ";
	print $outfile $word{$key} . "\n";

}

close $outfile;

