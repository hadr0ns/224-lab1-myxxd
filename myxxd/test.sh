TEST="myxxd.c"
cat $TEST | ./myxxd > myoutput1.txt;
cat $TEST | ./myxxd -b > myoutput1bits.txt;
cat $TEST | xxd > xxdoutput1.txt;
cat $TEST | xxd -b > xxdoutput1bits.txt;
diff xxdoutput1.txt myoutput1.txt  > diff.txt;
diff xxdoutput1bits.txt myoutput1bits.txt  > diffbits.txt;
echo "Diff:";
cat diff.txt;
echo "Diffbits:";
cat diffbits.txt;
