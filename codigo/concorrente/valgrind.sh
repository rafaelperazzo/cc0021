#!/bin/bash
rm -f report.log
echo "threads;m;n;L1_total;L1_r;L1_w;L2_total;L2_r;L2_w;LLC_total;LLC_r;LLC_w" >> report.log
valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 1 8000000 8
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "1;8000000;8;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 1 8000 8000
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "1;8000;8000;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 1 8 8000000
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "1;8;8000000;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 2 8000000 8
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "2;8000000;8;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 2 8000 8000
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "2;8000;8000;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 2 8 8000000
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "2;8;8000000;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 4 8000000 8
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "4;8000000;8;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 4 8000 8000
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "4;8000;8000;$linha1;$linha2;$linha3" >> report.log

valgrind --log-file=valgrind.log --tool=cachegrind --cache-sim=yes ./omp_mat_vect 4 8 8000000
linha1=$(cat valgrind.log | sed -n 16p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha2=$(cat valgrind.log | sed -n 17p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
linha3=$(cat valgrind.log | sed -n 22p |sed 's/,//g' |  awk -F ' +' '{print $4,$6,$9}' | sed 's/ /;/g')
echo "4;8;8000000;$linha1;$linha2;$linha3" >> report.log

rm valgrind.log
