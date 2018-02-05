#/*HEADER**********************************************************************
#*
#* Copyright 2010 Freescale Semiconductor, Inc.
#*
#* This software is owned or controlled by Freescale Semiconductor.
#* Use of this software is governed by the Freescale MQX RTOS License
#* distributed with this Material.
#* See the MQX_RTOS_LICENSE file distributed for more details.
#*
#* Brief License Summary:
#* This software is provided in source form for you to use free of charge,
#* but it is not open source software. You are allowed to use this software
#* but you cannot redistribute it or derivative works of it in source form.
#* The software may be used only in connection with a product containing
#* a Freescale microprocessor, microcontroller, or digital signal processor.
#* See license agreement file for full license terms including other restrictions.
#*****************************************************************************
#*
#* Comments:
#* This tool processes the prepare.txt file and creates a batch program which 
#* generates the final codesize reports as specifed
#*
#* usage:  prepare.pl > do_all.bat
#*
#*END************************************************************************/

$DEBUG = 0;
$INFILE = shift;
$INFILE = "prepare.txt" if not $INFILE; 

open MAPFILES, $INFILE or die "Can not open \"$INFILE\" input file";

$inrep = 0;
$nl = $DEBUG ? "\n" : "";

while($line = <MAPFILES>)
{
  chomp $line;
  
  # comment line
  next if $line =~ /^\s*\#/;
  
  # report begins here
  if($line =~ /^\s*report\s+\"(.*)\"/)
  {
    print "..\\codesize.pl -o $1 ";
    #print " -K";  # kernel symbols (not working with uv4)
    print " -W";   # debugging warning messages
    print "$nl";
    $inrep = 1;
    next;
  }
  
  # need to be in report to accept next input lines
  next if not $inrep;
  
  # map file entry, parse board, tool etc.
  if($line =~ /app\\(\w+)\.(\w+)\\(\w+)_(\w+)\\/)
  {
    # new line -> process collected mapfiles
    $board = $1;
    $mapfmt = $2;
    $kernel = $3;
    $cscfg = $4;
    
    print " -c $mapfmt -n \"$board\" -n2 \"$kernel kernel\" -n3 \"$cscfg app\" $line $nl";
  }
  else
  {
    # this report is done 
    print "\n\n";
    $inrep = 0;
  }
}

print "\n";
print "PAUSE";

close MAPFILES;
0;
