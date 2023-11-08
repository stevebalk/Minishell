< file1.txt grep -l a1 | wc -w > or_out_2.txt
./pipex file1.txt "grep a1" "wc -w" my_out_2.txt
JRES2=$(diff my_out_2.txt or_out_2.txt)
echo "Test 2         >${JRES2}<"