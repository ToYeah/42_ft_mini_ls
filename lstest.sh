make re
touch {5..10}
touch {1..4}
touch {1..10}
sleep 1
ls * | xargs -I{} ln -s {} link.{}
touch .{1..10}
touch {11..500}
sleep 1
touch link.{1..5}
chmod 777 {30..35}

for i in {41..45}
do
	echo "abcd $i" | xargs -I{} mv $i {}
done

touch -t 194204242420 {50..55}
touch -t 204204242420 {60..65}
touch -t 999912312359 {70..75}
touch -t 190001010000 {80..85}

./ft_mini_ls > ../ft_out
\ls -1tr > ../ls_out
diff ../ls_out ../ft_out > result.txt
mv ../ls_out ../ft_out .
#rm link* {1..40} {46..500} .{1..10} "abcd "{41..45}
cat result.txt